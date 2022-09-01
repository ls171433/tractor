#pragma once

#include "general/compiler.hpp"
#include "data/data.hpp"

// type endian
namespace tractor
{
    enum class endian
    {
        little,
        big,
#if is_msvc_v
        native = little,
#elif is_gcc_v || is_clang_v
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        native = little,
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        native = big,
#else
        native,
#endif
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
