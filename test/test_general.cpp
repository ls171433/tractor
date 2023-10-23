#include "general/compiler.hpp"
#include "general/os.hpp"

#include <gtest/gtest.h>

using namespace tractor;

// test_compiler
namespace
{
    TEST(test_compiler, macro)
    {
        int count = 0;

#if defined(TRACTOR_COMPILER_MSVC)
        ++count;
#endif
#if defined(TRACTOR_COMPILER_GCC)
        ++count;
#endif
#if defined(TRACTOR_COMPILER_CLANG)
        ++count;
#endif

        EXPECT_EQ(count, 1);
    }

    TEST(test_os, macro)
    {
        int count = 0;

#if defined(TRACTOR_OS_WINDOWS)
        ++count;
#endif
#if defined(TRACTOR_OS_LINUX)
        ++count;
#endif
#if defined(TRACTOR_OS_MACOS)
        ++count;
#endif
#if defined(TRACTOR_OS_ANDROID)
        ++count;
#endif
#if defined(TRACTOR_OS_IOS)
        ++count;
#endif

        EXPECT_EQ(count, 1);
    }
} // namespace
