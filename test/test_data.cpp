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

    template <class T>
    struct test_data_typed : public testing::Test
    {
    };

    using test_data_types = testing::Types<char, signed char, short, int, long, long long, unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long, float, double, long double>;
    TYPED_TEST_SUITE(test_data_typed, test_data_types);

    TYPED_TEST(test_data_typed, general)
    {
        using type_t = gtest_TypeParam_;

        type_t t0 = static_cast<type_t>(10272226631476820582u);
        data t1 = t0;
        type_t t2 = t1;
        EXPECT_EQ(t0, t2);
    }
} // namespace

// test_endian
namespace
{
    TEST(test_endian, general)
    {
        EXPECT_TRUE(is_little_endian());
    }
} // namespace
