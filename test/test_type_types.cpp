#include "type/types.hpp"

#include <gtest/gtest.h>

#include <type_traits>

using namespace tractor;

// test_type.basic_types
// test_type.other_types
namespace
{
    template <class type, tsize size>
    void test_signed_integer_types()
    {
        EXPECT_TRUE(std::is_signed_v<type>);
        EXPECT_TRUE(std::is_integral_v<type>);
        EXPECT_TRUE(is_basic_v<type>);
        EXPECT_TRUE(is_basic_integral_v<type>);
        EXPECT_TRUE(is_basic_signed_v<type>);
        EXPECT_EQ(sizeof(type), size);
    }

    template <class type, tsize size>
    void test_unsigned_integer_types()
    {
        EXPECT_TRUE(std::is_unsigned_v<type>);
        EXPECT_TRUE(std::is_integral_v<type>);
        EXPECT_TRUE(is_basic_v<type>);
        EXPECT_TRUE(is_basic_integral_v<type>);
        EXPECT_TRUE(is_basic_unsigned_v<type>);
        EXPECT_EQ(sizeof(type), size);
    }

    template <class type, tsize size>
    void test_floating_point_types()
    {
        EXPECT_TRUE(std::is_floating_point_v<type>);
        EXPECT_TRUE(is_basic_v<type>);
        EXPECT_TRUE(is_basic_float_v<type>);
        EXPECT_EQ(sizeof(type), size);
    }

    TEST(test_type, basic_types)
    {
        test_signed_integer_types<tint8, 1>();
        test_signed_integer_types<tint16, 2>();
        test_signed_integer_types<tint32, 4>();
        test_signed_integer_types<tint64, 8>();

        test_unsigned_integer_types<tuint8, 1>();
        test_unsigned_integer_types<tuint16, 2>();
        test_unsigned_integer_types<tuint32, 4>();
        test_unsigned_integer_types<tuint64, 8>();

        test_floating_point_types<tfloat, 4>();
        test_floating_point_types<tdouble, 8>();
    }

    TEST(test_type, other_types)
    {
        test_unsigned_integer_types<tbyte, 1>();
        test_unsigned_integer_types<tsize, sizeof(void *)>();
        test_signed_integer_types<tssize, sizeof(void *)>();
    }
} // namespace
