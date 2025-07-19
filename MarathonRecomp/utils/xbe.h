#ifndef XBE_H
#define XBE_H
#include <bit>
#include <type_traits>
#include <cstdint>
#include <cstring>
#include <climits>
#include <utility>

#include <utils/ex_memory.h>
#include <kernel/memory.h>


// Endianness tags
struct big_endian_tag {};
struct little_endian_tag {};
struct native_endian_tag {};

// Global configuration for pointer adjustments


// Byte-swap implementation
namespace detail {
    template <typename T>
    constexpr T byteswap(T value) noexcept {
        if constexpr (sizeof(T) == 1) {
            return value;
        }
        else if constexpr (std::is_same_v<T, double>) {
            return std::bit_cast<double>(__builtin_bswap64(std::bit_cast<uint64_t>(value)));
        }
        else if constexpr (std::is_same_v<T, float>) {
            return std::bit_cast<float>(__builtin_bswap32(std::bit_cast<uint32_t>(value)));
        }
        else if constexpr (sizeof(T) == 2) {
            return static_cast<T>(__builtin_bswap16(static_cast<uint16_t>(value)));
        }
        else if constexpr (sizeof(T) == 4) {
            return static_cast<T>(__builtin_bswap32(static_cast<uint32_t>(value)));
        }
        else if constexpr (sizeof(T) == 8) {
            return static_cast<T>(__builtin_bswap64(static_cast<uint64_t>(value)));
        } 
        else {
            // Generic byte reversal for unusual sizes
            T result;
            auto* src = reinterpret_cast<const uint8_t*>(&value);
            auto* dst = reinterpret_cast<uint8_t*>(&result);
            for (size_t i = 0; i < sizeof(T); i++) {
                dst[i] = src[sizeof(T) - 1 - i];
            }
            return result;
        }
    }

    // Type traits
    template <typename T>
    using is_swappable = std::bool_constant<
        std::is_arithmetic_v<T> ||
        std::is_enum_v<T> ||
        std::is_pointer_v<T>
    >;

    // Endian conversion
    template <typename T, typename EndianTag>
    constexpr T maybe_swap(T value, EndianTag) noexcept {
        if constexpr (std::is_same_v<EndianTag, big_endian_tag>) {
            if constexpr (std::endian::native == std::endian::little) {
                return byteswap(value);
            }
            else {
                return value;
            }
        }
        else if constexpr (std::is_same_v<EndianTag, little_endian_tag>) {
            if constexpr (std::endian::native == std::endian::big) {
                return byteswap(value);
            }
            else {
                return value;
            }
        }
        else { // native_endian_tag
            return value;
        }
    }

    // Pointer adjustment
    template <typename Ptr, typename Storage>
    constexpr Ptr adjust_pointer_from_storage(Storage stored) noexcept {
        if constexpr (sizeof(Storage) == 4 && sizeof(Ptr) == 8) {
            // 32-bit to 64-bit conversion
            uintptr_t addr = static_cast<uintptr_t>(stored);
            return reinterpret_cast<Ptr>(addr + (uintptr_t)g_memory.base);
        }
        else if constexpr (sizeof(Storage) == 8 && sizeof(Ptr) == 4) {
            // 64-bit to 32-bit conversion
            uintptr_t addr = static_cast<uintptr_t>(stored);
            return reinterpret_cast<Ptr>(addr - (uintptr_t)g_memory.base);
        }
        else {
            // Same pointer size
            return reinterpret_cast<Ptr>(stored);
        }
    }

    template <typename Ptr, typename Storage>
    constexpr Storage adjust_pointer_to_storage(Ptr ptr) noexcept {
        if constexpr (sizeof(Storage) == 4 && sizeof(Ptr) == 8) {
            // 64-bit to 32-bit conversion
            uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
            return static_cast<Storage>(addr - (uintptr_t)g_memory.base);
        }
        else if constexpr (sizeof(Storage) == 8 && sizeof(Ptr) == 4) {
            // 32-bit to 64-bit conversion
            uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
            return static_cast<Storage>(addr + (uintptr_t)g_memory.base);
        }
        else {
            // Same pointer size
            return reinterpret_cast<Storage>(ptr);
        }
    }
}

// Main xbe class template


template <typename T,
    typename EndianTag = big_endian_tag,
    typename StorageType = T>
class xbe {
    static_assert(detail::is_swappable<T>::value,
        "xbe only supports arithmetic, enum, or pointer types");

    StorageType stored_value;

public:
    using value_type = T;
    using endian_tag = EndianTag;
    using storage_type = StorageType;

    // Constructors
    constexpr xbe() noexcept = default;

    explicit constexpr xbe(T value) noexcept
        : stored_value(convert_to_storage(value)) {
    }

    // Assignment
    constexpr xbe& operator=(T value) noexcept {
        stored_value = convert_to_storage(value);
        return *this;
    }

    // Conversion to native value
    constexpr operator T() const noexcept {
        return convert_to_native();
    }

    // Explicit value access
    constexpr T value() const noexcept {
        return convert_to_native();
    }

    // Raw storage access
    constexpr StorageType raw() const noexcept {
        return stored_value;
    }

    // Create from raw storage
    static constexpr xbe from_raw(StorageType raw) noexcept {
        xbe result;
        result.stored_value = raw;
        return result;
    }

    // Pointer-like access
    template <typename U = T>
    constexpr auto operator->() const noexcept ->
        std::enable_if_t<std::is_pointer_v<U>, T>
    {
        return convert_to_native();
    }

    template <typename U = T>
    constexpr auto operator*() const noexcept ->
        std::enable_if_t<std::is_pointer_v<U>,
        std::add_lvalue_reference_t<std::remove_pointer_t<T>>>
    {
        return *convert_to_native();
    }

private:
    // Conversion logic
    constexpr StorageType convert_to_storage(T value) const noexcept {
        if constexpr (std::is_pointer_v<T>) {
            // Convert pointer to storage type with address adjustment
            auto adjusted = detail::adjust_pointer_to_storage<T, StorageType>(value);
            // Apply endian conversion to the storage representation
            return detail::maybe_swap(adjusted, EndianTag{});
        }
        else {
            // For non-pointer types, directly convert
            return detail::maybe_swap(static_cast<StorageType>(value), EndianTag{});
        }
    }

    constexpr T convert_to_native() const noexcept {
        if constexpr (std::is_pointer_v<T>) {
            // Reverse endian conversion first
            auto deswapped = detail::maybe_swap(stored_value, EndianTag{});
            // Then adjust pointer representation
            return detail::adjust_pointer_from_storage<T>(deswapped);
        }
        else {
            // For non-pointer types
            return static_cast<T>(detail::maybe_swap(stored_value, EndianTag{}));
        }
    }
};

// Common type aliases
template <typename T> using xbe_le = xbe<T, little_endian_tag>;
template <typename T> using xbe_be = xbe<T, big_endian_tag>;
template <typename T> using xbe_ne = xbe<T, native_endian_tag>;

// Pointer specializations
template <typename T> using xbe_ptr32 = xbe<T*, big_endian_tag, uint32_t>;
template <typename T> using xbe_ptr64 = xbe<T*, big_endian_tag, uint64_t>;
template <typename T> using xbe_cptr32 = xbe<const T*, big_endian_tag, uint32_t>;

// Common integer types
using be8 = xbe<uint8_t>;
using be16 = xbe<uint16_t>;
using be32 = xbe<uint32_t>;
using be64 = xbe<uint64_t>;
using le8 = xbe_le<uint8_t>;
using le16 = xbe_le<uint16_t>;
using le32 = xbe_le<uint32_t>;
using le64 = xbe_le<uint64_t>;


//example # 1 (from little endian)
//xbe<xbe<uint32_t>*, little_endian_tag, uint32_t> tag = xbe<xbe<uint32_t>*, little_endian_tag, uint32_t>::from_raw(ctx.r4.u32 + 0x18);
//auto v = (uint32_t)*tag;

//example # 2 (from big endian, method 1)
//auto _1 = detail::byteswap(ctx.r4.u32 + 0x18);
//xbe<xbe<uint32_t>*, big_endian_tag, uint32_t> tag2 = xbe<xbe<uint32_t>*, big_endian_tag, uint32_t>::from_raw(_1);
//auto v = (uint32_t)*tag;


// Macro for pointer size abstraction
#define sxbe(T) std::conditional_t<sizeof(void*) == 4, xbe_ptr32<T>, xbe_ptr64<T>>


#define get_ptr(T) xbe<xbe<uint32_t>*, little_endian_tag, uint32_t>::from_raw(T)
#endif
