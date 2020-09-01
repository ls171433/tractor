#if !defined TRACTOR_TEST_TEST_HPP
#define TRACTOR_TEST_TEST_HPP



#include <list>
#include <memory>

#include <iostream>



struct test_module;
using test_module_ptr = test_module *;

struct test_module
{
public:
    test_module()
    {
        m_position = s_test_module_count++;
        s_test_module_list[m_position] = this;
    }

    test_module(const test_module&) = delete;

    test_module(test_module&&) = delete;

    virtual ~test_module()
    {
        s_test_module_list[m_position] = nullptr;
    }

    test_module& operator=(const test_module&) = delete;

    test_module& operator=(test_module&&) = delete;

    virtual void test()
    {
    }

private:
    int m_position;

public:
    static constexpr const int test_module_max = 100;
    static test_module_ptr s_test_module_list[test_module_max];
    static int s_test_module_count;
};



#endif
