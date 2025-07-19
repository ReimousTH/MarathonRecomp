#ifndef VECTOR06
#define VECTOR06
#include <utils/xbe.h>
//Fake std::string BXT


template <typename T>
struct vector06 {
    xbe<uint32_t> proxy;  // Some proxy value (usage unclear from your code)
    xbe_ptr32<T> MyFirst; // Points to first element (big-endian 32-bit)
    xbe_ptr32<T> MyLast;  // Points to one past last element
    xbe_ptr32<T> MyEnd;   // Points to one past allocated storage

    // Helper functions for pointer operations
    static T* to_native(xbe_ptr32<T> ptr) {
        return ptr.value();  // Automatic conversion to native pointer
    }

    static xbe_ptr32<T> from_native(T* ptr) {
        return xbe_ptr32<T>(ptr);  // Construct from native pointer
    }

    // Default constructor
    vector06() : proxy(0), MyFirst(nullptr), MyLast(nullptr), MyEnd(nullptr) {}

    // Destructor
    ~vector06() {
        clear();
        if (to_native(MyFirst)) {
            g_userHeap.Free(to_native(MyFirst));
        }
    }

    // Size and capacity
    size_t size() const { return to_native(MyLast) - to_native(MyFirst); }
    size_t capacity() const { return to_native(MyEnd) - to_native(MyFirst); }
    bool empty() const { return MyFirst == MyLast; }

    // Push back with proper pointer handling
    void push_back(const T& value) {
        if (to_native(MyLast) == to_native(MyEnd)) {
            reserve(capacity() ? capacity() * 2 : 4);
        }
        new (to_native(MyLast)) T(value);  // Placement new
        MyLast = from_native(to_native(MyLast) + 1);
    }

    // Reserve with proper memory management
    void reserve(size_t new_capacity) {
        if (new_capacity <= capacity()) return;

        T* new_first = static_cast<T*>(g_userHeap.Alloc(new_capacity * sizeof(T)));
        T* new_last = new_first;

        try {
            for (T* p = to_native(MyFirst); p != to_native(MyLast); ++p, ++new_last) {
                new (new_last) T(*p);  // Copy construct in new location
            }
        }
        catch (...) {
            // Cleanup if exception occurs during copy
            while (new_last != new_first) (--new_last)->~T();
            g_userHeap.Free(new_first);
            throw;
        }

        // Destroy old elements and free old memory
        clear();
        if (to_native(MyFirst)) {
            g_userHeap.Free(to_native(MyFirst));
        }

        // Update pointers
        MyFirst = from_native(new_first);
        MyLast = from_native(new_last);
        MyEnd = from_native(new_first + new_capacity);
    }

    // Element access
    T& operator[](size_t index) {
        return to_native(MyFirst)[index];
    }

    const T& operator[](size_t index) const {
        return to_native(MyFirst)[index];
    }

    // Iterators
    T* begin() { return to_native(MyFirst); }
    const T* begin() const { return to_native(MyFirst); }
    T* end() { return to_native(MyLast); }
    const T* end() const { return to_native(MyLast); }

    // Clear elements
    void clear() {
        for (T* p = to_native(MyFirst); p != to_native(MyLast); ++p) {
            p->~T();
        }
        MyLast = MyFirst;
    }
};

#endif
