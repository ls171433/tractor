#pragma once

#define TRACTOR_IS_MSVC 0
#define TRACTOR_IS_GCC 0
#define TRACTOR_IS_CLANG 0

#if defined _MSC_VER
#undef TRACTOR_IS_MSVC
#define TRACTOR_IS_MSVC 1
#elif defined __GNUC__ && !defined __clang__
#undef TRACTOR_IS_GCC
#define TRACTOR_IS_GCC 1
#elif defined __GNUC__ && defined __clang__
#undef TRACTOR_IS_CLANG
#define TRACTOR_IS_CLANG 1
#endif

namespace tractor
{
    enum class compiler
    {
        msvc,
        gcc,
        clang,
#if TRACTOR_IS_MSVC
        native = msvc,
#elif TRACTOR_IS_GCC
        native = gcc,
#elif TRACTOR_IS_CLANG
        native = clang,
#else
        native,
#endif
    };

    constexpr bool is_msvc_v = compiler::native == compiler::msvc;
    constexpr bool is_gcc_v = compiler::native == compiler::gcc;
    constexpr bool is_clang_v = compiler::native == compiler::clang;

    constexpr bool is_msvc() { return is_msvc_v; }
    constexpr bool is_gcc() { return is_gcc_v; }
    constexpr bool is_clang() { return is_clang_v; }
} // namespace tractor
