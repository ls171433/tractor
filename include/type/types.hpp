#pragma once

#include <type_traits>

// type tint8
// type tint16
// type tint32
// type tint64
// type tuint8
// type tuint16
// type tuint32
// type tuint64
// type tfloat
// type tdouble
namespace tractor
{
    using tint8 = signed char;
    using tint16 = short;
    using tint32 = int;
    using tint64 = long long;

    using tuint8 = unsigned char;
    using tuint16 = unsigned short;
    using tuint32 = unsigned int;
    using tuint64 = unsigned long long;

    using tfloat = float;
    using tdouble = double;
} // namespace tractor

// type tbyte
// type tsize
// type tssize
namespace tractor
{
    using tbyte = tuint8;
    using tsize = tuint64;
    using tssize = tint64;
} // namespace tractor

// struct is_basic_type
// constexpr is_basic_type_value
namespace tractor
{
    template <class type>
    struct is_basic_type : public std::false_type
    {
    };

    template <>
    struct is_basic_type<tint8> : public std::true_type
    {
    };

    template <>
    struct is_basic_type<tint16> : public std::true_type
    {
    };

    template <>
    struct is_basic_type<tint32> : public std::true_type
    {
    };

    template <>
    struct is_basic_type<tint64> : public std::true_type
    {
    };

    template <>
    struct is_basic_type<tuint8> : public std::true_type
    {
    };

    template <>
    struct is_basic_type<tuint16> : public std::true_type
    {
    };

    template <>
    struct is_basic_type<tuint32> : public std::true_type
    {
    };

    template <>
    struct is_basic_type<tuint64> : public std::true_type
    {
    };

    template <>
    struct is_basic_type<tfloat> : public std::true_type
    {
    };

    template <>
    struct is_basic_type<tdouble> : public std::true_type
    {
    };

    template <class type>
    constexpr bool is_basic_type_value = is_basic_type<type>::value;
} // namespace tractor
