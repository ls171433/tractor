#include "exception/exception.hpp"

#include <gtest/gtest.h>

#include <exception>
#include <string>
#include <utility>

using namespace tractor;

// test_text_exception
namespace
{
    class test_text_exception : public testing::Test
    {
    protected:
        const tchar *m_text = "gbhjkgbdjs";
        std::string m_text_string = m_text;
        text_exception m_exception = text_exception(m_text);
    };

    TEST_F(test_text_exception, basic)
    {
        ASSERT_NE(m_exception.what(), nullptr);
        EXPECT_EQ(m_exception.what(), m_exception.what());
        EXPECT_STREQ(m_exception.what(), m_text);
    };

    TEST_F(test_text_exception, contruct_void)
    {
        text_exception current_exception;

        ASSERT_NE(current_exception.what(), nullptr);
        EXPECT_EQ(current_exception.what(), current_exception.what());
    };

    TEST_F(test_text_exception, contruct_copy)
    {
        text_exception current_exception(m_exception);

        ASSERT_NE(current_exception.what(), nullptr);
        EXPECT_EQ(current_exception.what(), current_exception.what());
        EXPECT_STREQ(current_exception.what(), m_text);
    };

    TEST_F(test_text_exception, contruct_move)
    {
        text_exception current_exception(std::move(m_exception));

        ASSERT_NE(current_exception.what(), nullptr);
        EXPECT_EQ(current_exception.what(), current_exception.what());
        EXPECT_STREQ(current_exception.what(), m_text);
    };

    TEST_F(test_text_exception, contruct_string)
    {
        text_exception current_exception(m_text_string);

        ASSERT_NE(current_exception.what(), nullptr);
        EXPECT_EQ(current_exception.what(), current_exception.what());
        EXPECT_STREQ(current_exception.what(), m_text);
    };

    TEST_F(test_text_exception, contruct_move_string)
    {
        text_exception current_exception(std::move(m_text_string));

        ASSERT_NE(current_exception.what(), nullptr);
        EXPECT_EQ(current_exception.what(), current_exception.what());
        EXPECT_STREQ(current_exception.what(), m_text);
    };

    TEST_F(test_text_exception, contruct_exception)
    {
        const std::exception &m_exception_reference = m_exception;
        text_exception current_exception(m_exception_reference);

        ASSERT_NE(current_exception.what(), nullptr);
        EXPECT_EQ(current_exception.what(), current_exception.what());
        EXPECT_STREQ(current_exception.what(), m_text);
    };

    TEST_F(test_text_exception, assign_copy)
    {
        text_exception current_exception;
        current_exception = m_exception;

        ASSERT_NE(current_exception.what(), nullptr);
        EXPECT_EQ(current_exception.what(), current_exception.what());
        EXPECT_STREQ(current_exception.what(), m_text);
    };

    TEST_F(test_text_exception, assign_move)
    {
        text_exception current_exception;
        current_exception = std::move(m_exception);

        ASSERT_NE(current_exception.what(), nullptr);
        EXPECT_EQ(current_exception.what(), current_exception.what());
        EXPECT_STREQ(current_exception.what(), m_text);
    };
} // namespace

// test_int_code_exception
namespace
{
    class test_int_code_exception : public testing::Test
    {
    protected:
        int m_code = 10086;
        const int_code_exception m_exception = int_code_exception(m_code);
    };

    TEST_F(test_int_code_exception, basic)
    {
        ASSERT_NE(m_exception.what(), nullptr);
        EXPECT_EQ(m_exception.what(), m_exception.what());
        EXPECT_STREQ(m_exception.what(), std::to_string(m_code).c_str());
    };

    TEST_F(test_int_code_exception, contruct_void)
    {
        int_code_exception current_exception;

        ASSERT_NE(current_exception.what(), nullptr);
        EXPECT_EQ(current_exception.what(), current_exception.what());
    };

    TEST_F(test_int_code_exception, contruct_copy)
    {
        int_code_exception current_exception(m_exception);

        ASSERT_NE(current_exception.what(), nullptr);
        EXPECT_EQ(current_exception.what(), current_exception.what());
        EXPECT_STREQ(current_exception.what(), std::to_string(m_code).c_str());
    };

    TEST_F(test_int_code_exception, contruct_move)
    {
        int_code_exception current_exception(std::move(m_exception));

        ASSERT_NE(current_exception.what(), nullptr);
        EXPECT_EQ(current_exception.what(), current_exception.what());
        EXPECT_STREQ(current_exception.what(), std::to_string(m_code).c_str());
    };

    TEST_F(test_int_code_exception, contruct_int)
    {
        int_code_exception current_exception(m_code);

        ASSERT_NE(current_exception.what(), nullptr);
        EXPECT_EQ(current_exception.what(), current_exception.what());
        EXPECT_STREQ(current_exception.what(), std::to_string(m_code).c_str());
    };

    TEST_F(test_int_code_exception, contruct_move_int)
    {
        int_code_exception current_exception(std::move(m_code));

        ASSERT_NE(current_exception.what(), nullptr);
        EXPECT_EQ(current_exception.what(), current_exception.what());
        EXPECT_STREQ(current_exception.what(), std::to_string(m_code).c_str());
    };

    TEST_F(test_int_code_exception, assign_copy)
    {
        int_code_exception current_exception;
        current_exception = m_exception;

        ASSERT_NE(current_exception.what(), nullptr);
        EXPECT_EQ(current_exception.what(), current_exception.what());
        EXPECT_STREQ(current_exception.what(), std::to_string(m_code).c_str());
    };

    TEST_F(test_int_code_exception, assign_move)
    {
        int_code_exception current_exception;
        current_exception = std::move(m_exception);

        ASSERT_NE(current_exception.what(), nullptr);
        EXPECT_EQ(current_exception.what(), current_exception.what());
        EXPECT_STREQ(current_exception.what(), std::to_string(m_code).c_str());
    };
} // namespace

// test_errno_code_exception
namespace
{
    class test_errno_code_exception : public testing::Test
    {
    protected:
        int m_code = E2BIG;
        const errno_code_exception m_exception = errno_code_exception(m_code);
    };

    TEST_F(test_errno_code_exception, basic)
    {
        ASSERT_NE(m_exception.what(), nullptr);
        EXPECT_EQ(m_exception.what(), m_exception.what());
        EXPECT_STREQ(m_exception.what(), strerror(m_code));
    };

    TEST_F(test_errno_code_exception, contruct_void)
    {
        errno_code_exception current_exception;

        ASSERT_NE(current_exception.what(), nullptr);
        EXPECT_EQ(current_exception.what(), current_exception.what());
    };

    TEST_F(test_errno_code_exception, contruct_copy)
    {
        errno_code_exception current_exception(m_exception);

        ASSERT_NE(current_exception.what(), nullptr);
        EXPECT_EQ(current_exception.what(), current_exception.what());
        EXPECT_STREQ(current_exception.what(), strerror(m_code));
    };

    TEST_F(test_errno_code_exception, contruct_move)
    {
        errno_code_exception current_exception(std::move(m_exception));

        ASSERT_NE(current_exception.what(), nullptr);
        EXPECT_EQ(current_exception.what(), current_exception.what());
        EXPECT_STREQ(current_exception.what(), strerror(m_code));
    };

    TEST_F(test_errno_code_exception, contruct_int)
    {
        errno_code_exception current_exception(m_code);

        ASSERT_NE(current_exception.what(), nullptr);
        EXPECT_EQ(current_exception.what(), current_exception.what());
        EXPECT_STREQ(current_exception.what(), strerror(m_code));
    };

    TEST_F(test_errno_code_exception, contruct_move_int)
    {
        errno_code_exception current_exception(std::move(m_code));

        ASSERT_NE(current_exception.what(), nullptr);
        EXPECT_EQ(current_exception.what(), current_exception.what());
        EXPECT_STREQ(current_exception.what(), strerror(m_code));
    };

    TEST_F(test_errno_code_exception, assign_copy)
    {
        errno_code_exception current_exception;
        current_exception = m_exception;

        ASSERT_NE(current_exception.what(), nullptr);
        EXPECT_EQ(current_exception.what(), current_exception.what());
        EXPECT_STREQ(current_exception.what(), strerror(m_code));
    };

    TEST_F(test_errno_code_exception, assign_move)
    {
        errno_code_exception current_exception;
        current_exception = std::move(m_exception);

        ASSERT_NE(current_exception.what(), nullptr);
        EXPECT_EQ(current_exception.what(), current_exception.what());
        EXPECT_STREQ(current_exception.what(), strerror(m_code));
    };
} // namespace
