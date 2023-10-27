#pragma once

#include "type/types.hpp"

// for std::swap
#include <utility>
// for std::vector
#include <vector>

// struct data
namespace tractor
{
    constexpr tsize char_bit = CHAR_BIT;

    struct data final
    {
    public:
        data() = default;
        data(const data &) = default;
        data(data &&) = default;

        template <class arithmetic_type, class enable = enable_if_basic_t<arithmetic_type>>
        data(const arithmetic_type &value)
        {
            *this = value;
        }

        ~data() = default;

        data &operator=(const data &) = default;
        data &operator=(data &&) = default;

        template <class arithmetic_type, class enable = enable_if_basic_t<arithmetic_type>>
        data &operator=(const arithmetic_type &value)
        {
            const tbyte *value_raw_data = &value;
            m_internal_data.resize(sizeof(arithmetic_type));

            for (tsize i = 0; i < m_internal_data.size(); ++i)
            {
                m_internal_data[i] = value_raw_data[i];
            }

            return *this;
        }

        data reverse() const
        {
            data new_data;
            new_data.m_internal_data.resize(m_internal_data.size());

            for (tsize i = 0; i < m_internal_data.size(); ++i)
            {
                new_data.m_internal_data[i] = m_internal_data[m_internal_data.size() - 1 - i];
            }

            return new_data;
        }

        void reverse_inplace()
        {
            for (tsize i = 0; i * 2 < m_internal_data.size(); ++i)
            {
                std::swap(m_internal_data[i], m_internal_data[m_internal_data.size() - 1 - i]);
            }
        }

    public:
        std::vector<tbyte> m_internal_data;
    };
} // namespace tractor
