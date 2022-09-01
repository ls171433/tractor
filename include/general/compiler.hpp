#pragma once

namespace tractor
{
    enum class compiler
    {
        msvc,
        gcc,
        clang,
#if defined _MSC_VER
        native = msvc,
#elif defined __GNUC__ && !defined __clang__
        native = gcc,
#elif defined __GNUC__ && defined __clang__
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
