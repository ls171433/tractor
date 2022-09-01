#pragma once

#include "type/basic_types.hpp"

#include <utility>
#include <vector>

#include <climits>
#include <cstring>

// struct data
namespace tractor
{
    constexpr size char_bit = CHAR_BIT;

    struct data final
    {
    public:
        data() = default;
        data(const data &) = default;
        data(data &&) = default;

        template <class arithmetic_type, class enable = typename std::enable_if<std::is_arithmetic<arithmetic_type>::value>::type>
        data(const arithmetic_type &value)
        {
            *this = value;
        }

        ~data() = default;

        data &operator=(const data &) = default;
        data &operator=(data &&) = default;

        template <class arithmetic_type, class enable = typename std::enable_if<std::is_arithmetic<arithmetic_type>::value>::type>
        data &operator=(const arithmetic_type &value)
        {
            const byte *value_raw_data = &value;
            m_internal_data.resize(sizeof(arithmetic_type));

            for (size i = 0; i < m_internal_data.size(); ++i)
            {
                m_internal_data[i] = value_raw_data[i];
            }

            return *this;
        }

        data reverse() const
        {
            data new_data;
            new_data.m_internal_data.resize(m_internal_data.size());

            for (size i = 0; i < m_internal_data.size(); ++i)
            {
                new_data.m_internal_data[i] = m_internal_data[m_internal_data.size() - 1 - i];
            }

            return new_data;
        }

        void reverse_inplace()
        {
            for (size i = 0; i * 2 < m_internal_data.size(); ++i)
            {
                std::swap(m_internal_data[i], m_internal_data[m_internal_data.size() - 1 - i]);
            }
        }

    public:
        std::vector<byte> m_internal_data;
    };
} // namespace tractor
