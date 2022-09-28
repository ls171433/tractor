#include "data/endian.hpp"

#include <gtest/gtest.h>

using namespace tractor;

// test_data
namespace
{
    TEST(test_data, general)
    {
        EXPECT_EQ(char_bit, 8);
    }
} // namespace

// test_endian
namespace
{
    TEST(test_endian, general)
    {
        EXPECT_TRUE(is_endian_little());
    }
} // namespace
