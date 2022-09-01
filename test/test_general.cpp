#include "general/compiler.hpp"

#include <gtest/gtest.h>

using namespace tractor;

// test_compiler
namespace
{
    TEST(test_compiler, general)
    {
        EXPECT_TRUE(is_msvc() || is_gcc() || is_clang());
    }
} // namespace
