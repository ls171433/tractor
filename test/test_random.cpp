#include "math/random.hpp"

#include "type/types.hpp"

#include <gtest/gtest.h>

using namespace tractor;

namespace
{
    class test_random : public testing::Test
    {
    };

    TEST_F(test_random, rate)
    {
        int_random_base<tuint64> my_int_random_1;
        int_random_base<tuint64> my_int_random_2;

        EXPECT_NE(my_int_random_1.get(), my_int_random_2.get());

        std::cout << my_int_random_1.last() << std::endl;
        std::cout << my_int_random_2.last() << std::endl;
    }
} // namespace
