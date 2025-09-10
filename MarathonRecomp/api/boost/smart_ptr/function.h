#pragma once

#include <type_traits>
#include <utility>
#include <memory>
#include <cassert>

namespace boost
{
    namespace detail
    {
        template<typename R, typename... Args>
        class function_base
        {
        public:
            virtual ~function_base() = default;
            virtual R operator()(Args... args) = 0;
            virtual function_base* clone() const = 0;
        };

        template<typename Functor, typename R, typename... Args>
        class function_impl : public function_base<R, Args...>
        {
        public:
            explicit function_impl(const Functor& functor) : functor_(functor) {}
            explicit function_impl(Functor&& functor) : functor_(std::move(functor)) {}

            R operator()(Args... args) override
            {
                return functor_(std::forward<Args>(args)...);
            }

            function_base<R, Args...>* clone() const override
            {
                return new function_impl<Functor, R, Args...>(functor_);
            }

        private:
            Functor functor_;
        };

        // Specialization for void return type
        template<typename Functor, typename... Args>
        class function_impl<Functor, void, Args...> : public function_base<void, Args...>
        {
        public:
            explicit function_impl(const Functor& functor) : functor_(functor) {}
            explicit function_impl(Functor&& functor) : functor_(std::move(functor)) {}

            void operator()(Args... args) override
            {
                functor_(std::forward<Args>(args)...);
            }

            function_base<void, Args...>* clone() const override
            {
                return new function_impl<Functor, void, Args...>(functor_);
            }

        private:
            Functor functor_;
        };
    }

    template<typename Signature>
    class function;

    template<typename R, typename... Args>
    class function<R(Args...)>
    {
    private:
        using base_type = detail::function_base<R, Args...>;
        xpointer<base_type> impl_;

    public:
        function() noexcept : impl_(nullptr) {}

        function(std::nullptr_t) noexcept : impl_(nullptr) {}

        function(const function& other) : impl_(other.impl_ ? other.impl_->clone() : nullptr) {}

        function(function&& other) noexcept : impl_(std::move(other.impl_)) {}

        template<typename Functor>
        function(Functor f,
            typename std::enable_if<
            !std::is_same<typename std::decay<Functor>::type, function>::value &&
            !std::is_same<typename std::decay<Functor>::type, std::nullptr_t>::value
            >::type* = nullptr)
            : impl_(new detail::function_impl<typename std::decay<Functor>::type, R, Args...>(std::forward<Functor>(f)))
        {
        }

        ~function() = default;

        function& operator=(const function& other)
        {
            if (this != &other)
            {
                if (other.impl_)
                {
                    impl_.reset(other.impl_->clone());
                }
                else
                {
                    impl_.reset();
                }
            }
            return *this;
        }

        function& operator=(function&& other) noexcept
        {
            impl_ = std::move(other.impl_);
            return *this;
        }

        function& operator=(std::nullptr_t)
        {
            impl_.reset();
            return *this;
        }

        template<typename Functor>
        function& operator=(Functor&& f)
        {
            function(std::forward<Functor>(f)).swap(*this);
            return *this;
        }

        template<typename Functor>
        function& operator=(std::reference_wrapper<Functor> f)
        {
            function(f).swap(*this);
            return *this;
        }

        void swap(function& other) noexcept
        {
            std::swap(impl_, other.impl_);
        }

        explicit operator bool() const noexcept
        {
            return impl_ != nullptr;
        }

        R operator()(Args... args) const
        {
            if (!impl_)
            {
                // Throw or handle bad function call
                throw std::bad_function_call();
            }
            return (*impl_)(std::forward<Args>(args)...);
        }

        // For void return type specialization
        void operator()(Args... args) const
        {
            if (!impl_)
            {
                throw std::bad_function_call();
            }
            (*impl_)(std::forward<Args>(args)...);
        }
    };

    // Swap function
    template<typename R, typename... Args>
    void swap(function<R(Args...)>& f1, function<R(Args...)>& f2) noexcept
    {
        f1.swap(f2);
    }

    // Comparison operators
    template<typename R, typename... Args>
    bool operator==(const function<R(Args...)>& f, std::nullptr_t) noexcept
    {
        return !f;
    }

    template<typename R, typename... Args>
    bool operator==(std::nullptr_t, const function<R(Args...)>& f) noexcept
    {
        return !f;
    }

    template<typename R, typename... Args>
    bool operator!=(const function<R(Args...)>& f, std::nullptr_t) noexcept
    {
        return static_cast<bool>(f);
    }

    template<typename R, typename... Args>
    bool operator!=(std::nullptr_t, const function<R(Args...)>& f) noexcept
    {
        return static_cast<bool>(f);
    }
}
