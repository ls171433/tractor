#if !defined TRACTOR_TEST_TEST_HPP
#define TRACTOR_TEST_TEST_HPP



#include <string>

#include <cstdio>



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



extern int g_succeed;
extern int g_failed;

inline void test_condition(const char *file, int line, bool condition)
{
    if (condition)
    {
        std::printf("%s:%d test condition succeed\n", file, line);
        ++g_succeed;
    }
    else
    {
        std::printf("%s:%d TEST CONDITION FAILED\n", file, line);
        ++g_failed;
    }
    std::fflush(stdout);
}

inline void test_trace(const char *file, int line, const char *name, int value)
{
    std::printf("%s:%d %s = %d\n", file, line, name, value);
    std::fflush(stdout);
}

inline void test_trace(const char *file, int line, const char *name, const char *value)
{
    std::printf("%s:%d %s = %s\n", file, line, name, value);
    std::fflush(stdout);
}

inline void test_trace(const char *file, int line, const char *name, const std::string& value)
{
    std::printf("%s:%d %s = %s\n", file, line, name, value.c_str());
    std::fflush(stdout);
}

#define TEST_CONDITION(condition) test_condition(__FILE__, __LINE__, (condition))
#define TEST_TRACE(value) test_trace(__FILE__, __LINE__, #value, value)



#endif
