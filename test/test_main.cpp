#include "test.hpp"

#include <exception>

#include <cstdio>

test_module_ptr test_module::s_test_module_list[test_module_max];
int test_module::s_test_module_count = 0;

int g_succeed = 0;
int g_failed = 0;

int main()
{
    for (test_module_ptr current_test_module_ptr : test_module::s_test_module_list)
    {
        if (current_test_module_ptr)
        {
            try
            {
                current_test_module_ptr->test();
            }
            catch (std::exception &e)
            {
                std::printf("caught an exception: %s\n", e.what());
                std::fflush(stdout);
                return -1;
            }
        }
    }

    std::printf("total succeed: %d, failed: %d\n", g_succeed, g_failed);
    std::fflush(stdout);
}
