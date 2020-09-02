#include "exception/exception.hpp"

#include "test.hpp"

#include <iostream>

using namespace std;
using namespace tractor;



struct test_exception : test_module
{
    virtual void test() override
    {
        int_code_exception e1{10086};
        cout << e1.what() << endl;

        auto e2 = e1;
        cout << e2.what() << endl;

        errno_code_exception e3{E2BIG};
        cout << e3.what() << endl;

        auto e4 = e3;
        cout << e4.what() << endl;
    }
};

test_exception g_test_exception;
