#include "string/fast_string.hpp"

#include "test.hpp"

#include <iostream>

using namespace std;
using namespace tractor;

struct test_fast_string : test_module
{
    using my_string = stack_string<127>;
    using cp_string = std::string;

    virtual void test() override
    {
        constexpr const char *basic_str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const my_string my_0(basic_str);
        const cp_string cp_0(basic_str);

        {
            my_string my;
            my_string my2(my, 1);
        }

        {
            my_string my;
            cp_string cp;
            TEST_CONDITION(is_string_value_same(my, cp));
        }

        {
            my_string my(100, 'a');
            cp_string cp(100, 'a');
            TEST_CONDITION(is_string_value_same(my, cp));
        }

        {
            my_string my(basic_str);
            cp_string cp(basic_str);
            TEST_CONDITION(is_string_value_same(my, cp));
        }

        {
            my_string my(my_0, 13, 26);
            cp_string cp(cp_0, 13, 26);
            TEST_CONDITION(is_string_value_same(my, cp));
        }

        {
            my_string my(my_0, 39, 26);
            cp_string cp(cp_0, 39, 26);
            TEST_CONDITION(is_string_value_same(my, cp));
        }

        {
            my_string my(my_0, 26);
            cp_string cp(cp_0, 26);
            TEST_CONDITION(is_string_value_same(my, cp));
        }

        {
            my_string my(basic_str, 13);
            cp_string cp(basic_str, 13);
            TEST_CONDITION(is_string_value_same(my, cp));
        }

        {
            my_string my(basic_str);
            cp_string cp(basic_str);
            TEST_CONDITION(is_string_value_same(my, cp));
        }

        {
            my_string my(cp_0.begin(), cp_0.end());
            cp_string cp(cp_0.begin(), cp_0.end());
            TEST_CONDITION(is_string_value_same(my, cp));
        }

        {
            my_string my{'a', 'b', 'd'};
            cp_string cp{'a', 'b', 'd'};
            TEST_CONDITION(is_string_value_same(my, cp));
        }
    }

    template <class string_type_1_template, class string_type_2_template>
    static bool is_string_value_same(const string_type_1_template &s1, const string_type_2_template &s2)
    {
        return (s1.size() == s2.size() &&
                string(s1.begin(), s1.end()) == string(s2.begin(), s2.end()) &&
                string(s1.c_str()) == string(s2.c_str()));
    }
};

static test_fast_string s_test;
