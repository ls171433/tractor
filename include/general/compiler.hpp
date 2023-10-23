#pragma once

#undef TRACTOR_COMPILER_MSVC
#undef TRACTOR_COMPILER_GCC
#undef TRACTOR_COMPILER_CLANG

#if defined _MSC_VER
#define TRACTOR_COMPILER_MSVC 1
#elif defined __GNUC__ && !defined __clang__
#define TRACTOR_COMPILER_GCC 1
#elif defined __GNUC__ && defined __clang__
#define TRACTOR_COMPILER_CLANG 1
#endif

namespace tractor
{
    enum class compiler
    {
        msvc,
        gcc,
        clang,
#if defined TRACTOR_COMPILER_MSVC
        native = msvc,
#elif defined TRACTOR_COMPILER_GCC
        native = gcc,
#elif defined TRACTOR_COMPILER_CLANG
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

    constexpr bool is_compiler(compiler c) { return c == compiler::native; }
} // namespace tractor
