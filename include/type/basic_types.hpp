#pragma once

// for CHAR_BIT
#include <climits>
// for std::size_t
#include <cstddef>

// function max
namespace tractor
{
    template <class type_template>
    constexpr type_template max() noexcept { return 0; }
    template <>
    constexpr char max<char>() noexcept { return CHAR_MAX; }
    template <>
    constexpr signed char max<signed char>() noexcept { return SCHAR_MAX; }
    template <>
    constexpr unsigned char max<unsigned char>() noexcept { return UCHAR_MAX; }
    template <>
    constexpr short max<short>() noexcept { return SHRT_MAX; }
    template <>
    constexpr unsigned short max<unsigned short>() noexcept { return USHRT_MAX; }
    template <>
    constexpr int max<int>() noexcept { return INT_MAX; }
    template <>
    constexpr unsigned int max<unsigned int>() noexcept { return UINT_MAX; }
    template <>
    constexpr long max<long>() noexcept { return LONG_MAX; }
    template <>
    constexpr unsigned long max<unsigned long>() noexcept { return ULONG_MAX; }
    template <>
    constexpr long long max<long long>() noexcept { return LONG_LONG_MAX; }
    template <>
    constexpr unsigned long long max<unsigned long long>() noexcept { return ULONG_LONG_MAX; }

    template <class type_template>
    constexpr type_template min() { return 0; }
} // namespace tractor

// type size_t
namespace tractor
{
    using size = std::size_t;
} // namespace tractor

// type byte
namespace tractor
{
    using byte = unsigned char;
    constexpr size byte_bit = CHAR_BIT;
    constexpr byte byte_min = static_cast<byte>(0);
    constexpr byte byte_max = static_cast<byte>(-1);
} // namespace tractor
