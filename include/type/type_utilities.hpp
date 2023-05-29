#pragma once

#include "types.hpp"

#include <type_traits>

// constexpr max_value
// constexpr min_value
namespace tractor
{
    namespace max_min_value_helper
    {
        template <class type>
        struct min_value_helper : public std::integral_constant<type, std::is_signed_v<type> ? static_cast<type>(static_cast<type>(1) << (sizeof(type) * 8 - 1)) : static_cast<type>(0)>
        {
            static_assert(is_basic_type_value<type>);
            static_assert(std::is_integral_v<type>);
        };

        template <class type>
        struct max_value_helper : public std::integral_constant<type, static_cast<type>(~min_value_helper<type>::value)>
        {
            static_assert(is_basic_type_value<type>);
            static_assert(std::is_integral_v<type>);
        };
    } // namespace max_min_value_helper

    template <class type>
    constexpr type max_value = max_min_value_helper::max_value_helper<type>::value;

    template <class type>
    constexpr type min_value = max_min_value_helper::min_value_helper<type>::value;
} // namespace tractor
