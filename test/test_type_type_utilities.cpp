#include "type/type_utilities.hpp"

#include <gtest/gtest.h>

#include <type_traits>

using namespace tractor;

// test_type.max_min
namespace
{
    template<class type>
    void test_max_min()
    {
        EXPECT_GE(max_value<type>, min_value<type>);

        EXPECT_GE(max_value<type>, static_cast<type>(max_value<type> + 1));
        EXPECT_GE(max_value<type>, static_cast<type>(max_value<type> - 1));
        EXPECT_GE(max_value<type>, static_cast<type>(min_value<type> + 1));
        EXPECT_GE(max_value<type>, static_cast<type>(min_value<type> - 1));

        EXPECT_LE(min_value<type>, static_cast<type>(max_value<type> + 1));
        EXPECT_LE(min_value<type>, static_cast<type>(max_value<type> - 1));
        EXPECT_LE(min_value<type>, static_cast<type>(min_value<type> + 1));
        EXPECT_LE(min_value<type>, static_cast<type>(min_value<type> - 1));
    }

    TEST(test_type, max_min)
    {
        test_max_min<tint8>();
        test_max_min<tint16>();
        test_max_min<tint32>();
        test_max_min<tint64>();
        test_max_min<tuint8>();
        test_max_min<tuint16>();
        test_max_min<tuint32>();
        test_max_min<tuint64>();
    }
} // namespace
