#pragma once

#include "type/types.hpp"
#include "type/type_utilities.hpp"

// for std::mt19937
// for std::random_device
// for std::uniform_int_distribution
#include <random>

namespace tractor
{
    template <class int_type_template, class enable = enable_if_basic_integral_t<int_type_template>>
    class int_random_base final
    {
    public:
        using int_type = int_type_template;

    public:
        int_random_base() : int_random_base(min_value<int_type>, max_value<int_type>) {}

        int_random_base(int_type min, int_type max) : m_engine(std::random_device()()), m_distribution(min, max) {}

        ~int_random_base() {}

        int_type get()
        {
            m_last = m_distribution(m_engine);
            return m_last;
        }

        int_type last() { return m_last; }

    private:
        std::mt19937 m_engine;
        std::uniform_int_distribution<int_type> m_distribution;
        int_type m_last;
    };

    using int_random = int_random_base<int>;
}; // namespace tractor
