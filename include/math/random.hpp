#pragma once

#include "type/type_utilities.hpp"
#include "type/types.hpp"

// for std::mt19937
// for std::random_device
// for std::uniform_int_distribution
#include <random>

namespace tractor
{
    std::mt19937 &get_random_engine()
    {
        static std::random_device s_random_device;
        static std::mt19937 s_mt19937(s_random_device());
        return s_mt19937;
    }

    template <class int_type_template, class enable = enable_if_basic_integral_t<int_type_template>>
    class basic_integral_random final
    {
    public:
        using int_type = int_type_template;

    public:
        basic_integral_random() : basic_integral_random(min_value<int_type>, max_value<int_type>) {}

        basic_integral_random(int_type min, int_type max) : m_distribution(min, max) {}

        ~basic_integral_random() {}

        int_type get()
        {
            m_last = m_distribution(get_random_engine());
            return m_last;
        }

        int_type last() { return m_last; }

    private:
        std::uniform_int_distribution<int_type> m_distribution;
        int_type m_last;
    };
}; // namespace tractor
