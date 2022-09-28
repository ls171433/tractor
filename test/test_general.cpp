#include "general/compiler.hpp"
#include "general/os.hpp"

#include <gtest/gtest.h>

using namespace tractor;

// test_compiler
namespace
{
    TEST(test_compiler, macro)
    {
#if !defined TRACTOR_COMPILER_MSVC && !defined TRACTOR_COMPILER_GCC && !defined TRACTOR_COMPILER_CLANG
        FAIL();
#elif defined TRACTOR_COMPILER_MSVC && !defined TRACTOR_COMPILER_GCC && !defined TRACTOR_COMPILER_CLANG
#elif !defined TRACTOR_COMPILER_MSVC && defined TRACTOR_COMPILER_GCC && !defined TRACTOR_COMPILER_CLANG
#elif !defined TRACTOR_COMPILER_MSVC && !defined TRACTOR_COMPILER_GCC && defined TRACTOR_COMPILER_CLANG
#else
        FAIL();
#endif
    }

    TEST(test_os, macro)
    {
#if !defined TRACTOR_OS_WINDOWS && !defined TRACTOR_OS_LINUX && !defined TRACTOR_OS_MACOS && !defined TRACTOR_OS_ANDROID && !defined TRACTOR_OS_IOS
        FAIL();
#elif defined TRACTOR_OS_WINDOWS && !defined TRACTOR_OS_LINUX && !defined TRACTOR_OS_MACOS && !defined TRACTOR_OS_ANDROID && !defined TRACTOR_OS_IOS
#elif !defined TRACTOR_OS_WINDOWS && defined TRACTOR_OS_LINUX && !defined TRACTOR_OS_MACOS && !defined TRACTOR_OS_ANDROID && !defined TRACTOR_OS_IOS
#elif !defined TRACTOR_OS_WINDOWS && !defined TRACTOR_OS_LINUX && defined TRACTOR_OS_MACOS && !defined TRACTOR_OS_ANDROID && !defined TRACTOR_OS_IOS
#elif !defined TRACTOR_OS_WINDOWS && !defined TRACTOR_OS_LINUX && !defined TRACTOR_OS_MACOS && defined TRACTOR_OS_ANDROID && !defined TRACTOR_OS_IOS
#elif !defined TRACTOR_OS_WINDOWS && !defined TRACTOR_OS_LINUX && !defined TRACTOR_OS_MACOS && !defined TRACTOR_OS_ANDROID && defined TRACTOR_OS_IOS
#else
        FAIL();
#endif
    }
} // namespace
