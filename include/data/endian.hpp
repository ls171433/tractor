#pragma once

#include "data/data.hpp"
#include "general/compiler.hpp"
#include "type/types.hpp"

#undef TRACTOR_ENDIAN_LITTLE
#undef TRACTOR_ENDIAN_BIG
#undef TRACTOR_ENDIAN_PDP

#if defined TRACTOR_COMPILER_MSVC
#define TRACTOR_ENDIAN_LITTLE 1
#elif defined TRACTOR_COMPILER_GCC || defined TRACTOR_COMPILER_CLANG
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define TRACTOR_ENDIAN_LITTLE 1
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define TRACTOR_ENDIAN_BIG 1
#endif
#endif

// type endian
namespace tractor
{
    enum class endian
    {
        little,
        big,
        pdp,
#if TRACTOR_ENDIAN_LITTLE
        native = little,
#elif TRACTOR_ENDIAN_BIG
        native = big,
#elif TRACTOR_ENDIAN_PDP
        native = pdp,
#else
        native,
#endif
    };

    constexpr bool is_endian_little_v = endian::native == endian::little;
    constexpr bool is_endian_big_v = endian::native == endian::big;
    constexpr bool is_endian_pdp_v = endian::native == endian::pdp;

    constexpr bool is_endian_little() { return is_endian_little_v; }
    constexpr bool is_endian_big() { return is_endian_big_v; }
    constexpr bool is_endian_pdp() { return is_endian_pdp_v; }
} // namespace tractor

namespace tractor
{
    template <class arithmetic_type, class enable = enable_if_basic_integral<arithmetic_type>>
    data to_endian(const arithmetic_type &arithmetic_value, endian current_endian)
    {
        data arithmetic_data = arithmetic_value;

        if (current_endian != endian::native)
        {
            arithmetic_data.reverse_inplace();
        }

        return arithmetic_data;
    }

    template <class arithmetic_type, class enable = enable_if_basic_integral<arithmetic_type>>
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
