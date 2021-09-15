#include "string/fast_string.hpp"

#include <gtest/gtest.h>

#include <string>

using namespace tractor;

namespace
{
    using my_string = stack_string<127>;
    using cp_string = std::string;

    class test_fast_string : public testing::Test
    {
    protected:
        static constexpr const char *m_string = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const my_string m_my = m_string;
        const cp_string m_cp = m_string;

        template <class string_type_1_template, class string_type_2_template>
        static bool is_string_value_same(const string_type_1_template &s1, const string_type_2_template &s2)
        {
            return (s1.size() == s2.size() &&
                    std::string(s1.begin(), s1.end()) == std::string(s2.begin(), s2.end()) &&
                    std::string(s1.c_str()) == std::string(s2.c_str()));
        }
    };

    TEST_F(test_fast_string, basic)
    {
        ASSERT_NE(m_my.c_str(), nullptr);
        ASSERT_NE(m_cp.c_str(), nullptr);
        EXPECT_TRUE(is_string_value_same(m_my, m_cp));
    }

    TEST_F(test_fast_string, construct_void)
    {
        my_string my;
        cp_string cp;
        ASSERT_NE(my.c_str(), nullptr);
        ASSERT_NE(cp.c_str(), nullptr);
        EXPECT_TRUE(is_string_value_same(my, cp));
    }

    TEST_F(test_fast_string, construct_int_char)
    {
        my_string my(100, 'a');
        cp_string cp(100, 'a');
        ASSERT_NE(my.c_str(), nullptr);
        ASSERT_NE(cp.c_str(), nullptr);
        EXPECT_TRUE(is_string_value_same(my, cp));
    }

    TEST_F(test_fast_string, construct_const_char_ptr)
    {
        my_string my(m_string);
        cp_string cp(m_string);
        ASSERT_NE(my.c_str(), nullptr);
        ASSERT_NE(cp.c_str(), nullptr);
        EXPECT_TRUE(is_string_value_same(my, cp));
    }

    TEST_F(test_fast_string, construct_string_int_int_1)
    {
        my_string my(m_my, 13, 26);
        cp_string cp(m_cp, 13, 26);
        ASSERT_NE(my.c_str(), nullptr);
        ASSERT_NE(cp.c_str(), nullptr);
        EXPECT_TRUE(is_string_value_same(my, cp));
    }

    TEST_F(test_fast_string, construct_string_int_int_2)
    {
        my_string my(m_my, 39, 26);
        cp_string cp(m_cp, 39, 26);
        ASSERT_NE(my.c_str(), nullptr);
        ASSERT_NE(cp.c_str(), nullptr);
        EXPECT_TRUE(is_string_value_same(my, cp));
    }

    TEST_F(test_fast_string, construct_string_int)
    {
        my_string my(m_my, 26);
        cp_string cp(m_cp, 26);
        ASSERT_NE(my.c_str(), nullptr);
        ASSERT_NE(cp.c_str(), nullptr);
        EXPECT_TRUE(is_string_value_same(my, cp));
    }

    TEST_F(test_fast_string, construct_const_char_ptr_int)
    {
        my_string my(m_string, 13);
        cp_string cp(m_string, 13);
        ASSERT_NE(my.c_str(), nullptr);
        ASSERT_NE(cp.c_str(), nullptr);
        EXPECT_TRUE(is_string_value_same(my, cp));
    }

    TEST_F(test_fast_string, construct_it_it)
    {
        my_string my(m_cp.begin(), m_cp.end());
        cp_string cp(m_cp.begin(), m_cp.end());
        ASSERT_NE(my.c_str(), nullptr);
        ASSERT_NE(cp.c_str(), nullptr);
        EXPECT_TRUE(is_string_value_same(my, cp));
    }

    TEST_F(test_fast_string, construct_ilist)
    {
        my_string my{'a', 'b', 'd'};
        cp_string cp{'a', 'b', 'd'};
        ASSERT_NE(my.c_str(), nullptr);
        ASSERT_NE(cp.c_str(), nullptr);
        EXPECT_TRUE(is_string_value_same(my, cp));
    }
} // namespace
