namespace boost
{
    namespace detail
    {
        class function_base
        {
        protected:
            struct vftable_t
            {
                be<uint32_t> destroy;
                be<uint32_t> invoke;
            };

            xpointer<vftable_t> vftable_;
            be<uint32_t> use_count_;

        public:
            function_base() : use_count_(1) {}
            virtual ~function_base() = default;

            void add_ref()
            {
                use_count_ = use_count_ + 1;
            }

            void release()
            {
                use_count_ = use_count_ - 1;
                if (use_count_ == 0)
                {
                    GuestToHostFunction<void>(vftable_->destroy, this);
                }
            }
        };

        template<typename R, typename... Args>
        class function_impl_base : public function_base {};

        template<typename Functor, typename R, typename... Args>
        class function_impl : public function_impl_base<R, Args...>
        {
            Functor f_;

            static void destroy_impl(function_base* self)
            {
                delete static_cast<function_impl*>(self);
            }

            static R invoke_impl(function_base* self, Args... args)
            {
                auto* p = static_cast<function_impl*>(self);
                return p->f_(std::forward<Args>(args)...);
            }

            static const typename function_base::vftable_t vtable;

        public:
            explicit function_impl(Functor f) : f_(std::move(f))
            {
                this->vftable_ = &vtable;
            }
        };

        template<typename Functor, typename R, typename... Args>
        const typename function_base::vftable_t
            function_impl<Functor, R, Args...>::vtable = {
                ByteSwap(static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&destroy_impl))),
                ByteSwap(static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&invoke_impl)))
        };
    }

    template<typename T>
    class function;

    template<typename R, typename... Args>
    class function<R(Args...)>
    {
        xpointer<detail::function_impl_base<R, Args...>> impl_;

        void release()
        {
            if (impl_)
            {
                impl_->release();
                impl_ = nullptr;
            }
        }

    public:
        function() noexcept : impl_(nullptr) {}

        function(std::nullptr_t) noexcept : impl_(nullptr) {}

        ~function() { release(); }

        function(const function& other) : impl_(other.impl_)
        {
            if (impl_) impl_->add_ref();
        }

        function(function&& other) noexcept : impl_(other.impl_)
        {
            other.impl_ = nullptr;
        }

        template<typename Functor>
        function(Functor f)
        {
            using impl_type = detail::function_impl<Functor, R, Args...>;
            impl_ = new impl_type(std::move(f));
        }

        function& operator=(const function& other)
        {
            if (this != &other)
            {
                release();
                impl_ = other.impl_;
                if (impl_) impl_->add_ref();
            }
            return *this;
        }

        function& operator=(function&& other) noexcept
        {
            if (this != &other)
            {
                release();
                impl_ = other.impl_;
                other.impl_ = nullptr;
            }
            return *this;
        }

        function& operator=(std::nullptr_t)
        {
            release();
            return *this;
        }

        explicit operator bool() const noexcept
        {
            return impl_ != nullptr;
        }

        R operator()(Args... args) const
        {
            if (!impl_)
            {
                assert(false && "boost::function called when empty");
                std::abort();
            }
            return GuestToHostFunction<R>(impl_->vftable_->invoke, impl_.get(), std::forward<Args>(args)...);
        }

        void swap(function& other) noexcept
        {
            std::swap(impl_, other.impl_);
        }
    };

    template<typename R, typename... Args>
    void swap(function<R(Args...)>& lhs, function<R(Args...)>& rhs)
    {
        lhs.swap(rhs);
    }
}
