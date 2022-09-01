#pragma once

#include "general/compiler.hpp"
#include "data/data.hpp"

#define TRACTOR_IS_LITTLE_ENDIAN 0
#define TRACTOR_IS_BIG_ENDIAN 0

#if TRACTOR_IS_MSVC
#undef TRACTOR_IS_LITTLE_ENDIAN
#define TRACTOR_IS_LITTLE_ENDIAN 1
#elif TRACTOR_IS_GCC || TRACTOR_IS_CLANG
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#undef TRACTOR_IS_LITTLE_ENDIAN
#define TRACTOR_IS_LITTLE_ENDIAN 1
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#undef TRACTOR_IS_BIG_ENDIAN
#define TRACTOR_IS_BIG_ENDIAN 1
#endif
#endif

// type endian
namespace tractor
{
    enum class endian
    {
        little,
        big,
#if TRACTOR_IS_LITTLE_ENDIAN
        native = little,
#elif TRACTOR_IS_BIG_ENDIAN
        native = big,
#else
        native,
#endif
    };

    constexpr bool is_little_endian_v = endian::native == endian::little;
    constexpr bool is_big_endian_v = endian::native == endian::big;

    constexpr bool is_little_endian() { return is_little_endian_v; }
    constexpr bool is_big_endian() { return is_big_endian_v; }
} // namespace tractor

namespace tractor
{
    template <class arithmetic_type, class enable = typename std::enable_if<std::is_arithmetic<arithmetic_type>::value>::type>
    data to_endian(const arithmetic_type &arithmetic_value, endian current_endian)
    {
        data arithmetic_data = arithmetic_value;

        if (current_endian != endian::native)
        {
            arithmetic_data.reverse_inplace();
        }

        return arithmetic_data;
    }

    template <class arithmetic_type, class enable = typename std::enable_if<std::is_arithmetic<arithmetic_type>::value>::type>
    arithmetic_type from_endian(const data &arithmetic_data, endian current_endian)
    {
        if (current_endian == endian::native)
        {
            arithmetic_data;
        }
        else
        {
            arithmetic_data.reverse();
        }
    }
} // namespace tractor
