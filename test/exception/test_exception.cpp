#include "exception/exception.hpp"

#include "test.hpp"

#include <iostream>

using namespace std;
using namespace tractor;

struct test_exception : test_module
{
    virtual void test() override
    {
        test_text_exception();
        test_int_code_exception();
        test_errno_code_exception();
    }

    void test_text_exception()
    {
        const char *text = "gbhjkgbdjs";
        TEST_TRACE(text);

        text_exception e0{text};
        {
            TEST_CONDITION(string{e0.what()} == string{text});
        }

        {
            text_exception e0_temp{e0};
            text_exception e{e0_temp};
            TEST_CONDITION(string{e.what()} == string{text});
        }

        {
            text_exception e0_temp{e0};
            text_exception e{std::move(e0_temp)};
            TEST_CONDITION(string{e.what()} == string{text});
        }

        {
            string text_str_temp{text};
            text_exception e{text_str_temp};
            TEST_CONDITION(string{e.what()} == string{text});
        }

        {
            string text_str_temp{text};
            text_exception e{std::move(text_str_temp)};
            TEST_CONDITION(string{e.what()} == string{text});
        }

        {
            exception &e0_ref{e0};
            text_exception e{e0_ref};
            TEST_CONDITION(string{e.what()} == string{text});
        }

        {
            text_exception e0_temp{e0};
            text_exception e{};
            e = e0_temp;
            TEST_CONDITION(string{e.what()} == string{text});
        }

        {
            text_exception e0_temp{e0};
            text_exception e{};
            e = std::move(e0_temp);
            TEST_CONDITION(string{e.what()} == string{text});
        }
    }

    void test_int_code_exception()
    {
        int code = 10086;
        TEST_TRACE(code);

        const int_code_exception e0{code};
        {
            TEST_CONDITION(string{e0.what()} == to_string(code));
        }

        {
            int_code_exception e0_temp{e0};
            int_code_exception e{e0_temp};
            TEST_CONDITION(string{e.what()} == to_string(code));
        }

        {
            int_code_exception e0_temp{e0};
            int_code_exception e{std::move(e0_temp)};
            TEST_CONDITION(string{e.what()} == to_string(code));
        }

        {
            int code_temp = code;
            int_code_exception e{code_temp};
            TEST_CONDITION(string{e.what()} == to_string(code));
        }

        {
            int code_temp = code;
            int_code_exception e{std::move(code_temp)};
            TEST_CONDITION(string{e.what()} == to_string(code));
        }

        {
            int_code_exception e0_temp{e0};
            int_code_exception e{};
            e = e0;
            TEST_CONDITION(string{e.what()} == to_string(code));
        }

        {
            int_code_exception e0_temp{e0};
            int_code_exception e{};
            e = std::move(e0);
            TEST_CONDITION(string{e.what()} == to_string(code));
        }
    }

    void test_errno_code_exception()
    {
        int code = E2BIG;
        TEST_TRACE(code);
        TEST_TRACE(strerror(code));

        const errno_code_exception e0{code};

        {
            errno_code_exception e0_temp{e0};
            errno_code_exception e{e0_temp};
            TEST_CONDITION(string{e.what()} == e0.what());
        }

        {
            errno_code_exception e0_temp{e0};
            errno_code_exception e{std::move(e0_temp)};
            TEST_CONDITION(string{e.what()} == e0.what());
        }

        {
            int code_temp = code;
            errno_code_exception e{code_temp};
            TEST_CONDITION(string{e.what()} == e0.what());
        }

        {
            int code_temp = code;
            errno_code_exception e{std::move(code_temp)};
            TEST_CONDITION(string{e.what()} == e0.what());
        }

        {
            errno_code_exception e0_temp{e0};
            errno_code_exception e{};
            e = e0;
            TEST_CONDITION(string{e.what()} == e0.what());
        }

        {
            errno_code_exception e0_temp{e0};
            errno_code_exception e{};
            e = std::move(e0);
            TEST_CONDITION(string{e.what()} == e0.what());
        }
    }
};

static test_exception s_test;
