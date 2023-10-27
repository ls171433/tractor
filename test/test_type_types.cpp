#include "type/types.hpp"

#include <gtest/gtest.h>

#include <type_traits>

using namespace tractor;

// test_type.basic_types
// test_type.other_types
// test_type.fundamental_types
namespace
{
    template <class type, tsize size>
    void test_sizeof()
    {
        EXPECT_EQ(sizeof(type), size);
    }

    template <class type>
    void test_integer_types()
    {
        EXPECT_TRUE(std::is_arithmetic_v<type>);
        EXPECT_TRUE(std::is_integral_v<type>);
        EXPECT_FALSE(std::is_floating_point_v<type>);

        EXPECT_TRUE(is_basic_v<type>);
        EXPECT_TRUE(is_basic_integral_v<type>);
        EXPECT_FALSE(is_basic_float_v<type>);
    }

    template <class type>
    void test_signed_integer_types()
    {
        test_integer_types<type>();

        EXPECT_TRUE(std::is_signed_v<type>);
        EXPECT_FALSE(std::is_unsigned_v<type>);

        EXPECT_TRUE(is_basic_signed_v<type>);
        EXPECT_FALSE(is_basic_unsigned_v<type>);
    }

    template <class type>
    void test_unsigned_integer_types()
    {
        test_integer_types<type>();

        EXPECT_FALSE(std::is_signed_v<type>);
        EXPECT_TRUE(std::is_unsigned_v<type>);

        EXPECT_FALSE(is_basic_signed_v<type>);
        EXPECT_TRUE(is_basic_unsigned_v<type>);
    }

    template <class type>
    void test_char_integer_types()
    {
        test_integer_types<type>();

        EXPECT_FALSE(is_basic_signed_v<type>);
        EXPECT_FALSE(is_basic_unsigned_v<type>);
    }

    template <class type>
    void test_floating_point_types()
    {
        EXPECT_TRUE(std::is_arithmetic_v<type>);
        EXPECT_FALSE(std::is_integral_v<type>);
        EXPECT_TRUE(std::is_floating_point_v<type>);

        EXPECT_TRUE(is_basic_v<type>);
        EXPECT_FALSE(is_basic_integral_v<type>);
        EXPECT_TRUE(is_basic_float_v<type>);
    }

    TEST(test_type, basic_types)
    {
        test_signed_integer_types<tint8>();
        test_sizeof<tint8, 1>();
        test_signed_integer_types<tint16>();
        test_sizeof<tint16, 2>();
        test_signed_integer_types<tint32>();
        test_sizeof<tint32, 4>();
        test_signed_integer_types<tint64>();
        test_sizeof<tint64, 8>();

        test_unsigned_integer_types<tuint8>();
        test_sizeof<tuint8, 1>();
        test_unsigned_integer_types<tuint16>();
        test_sizeof<tuint16, 2>();
        test_unsigned_integer_types<tuint32>();
        test_sizeof<tuint32, 4>();
        test_unsigned_integer_types<tuint64>();
        test_sizeof<tuint64, 8>();

        test_floating_point_types<tfloat>();
        test_sizeof<tfloat, 4>();
        test_floating_point_types<tdouble>();
        test_sizeof<tdouble, 8>();
    }

    TEST(test_type, other_types)
    {
        test_char_integer_types<tchar>();
        test_sizeof<tchar, 1>();

        test_unsigned_integer_types<tbyte>();
        test_sizeof<tbyte, 1>();
        test_unsigned_integer_types<tsize>();
        test_sizeof<tsize, sizeof(void*)>();
        test_signed_integer_types<tssize>();
        test_sizeof<tssize, sizeof(void*)>();
    }

    TEST(test_type, fundamental_types)
    {
        test_signed_integer_types<int>();
        test_unsigned_integer_types<unsigned int>();

        test_char_integer_types<char>();
        test_sizeof<char, 1>();
        EXPECT_TRUE((std::is_same_v<tchar, char>));

        test_floating_point_types<float>();
        test_floating_point_types<double>();
    }
} // namespace
