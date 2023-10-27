#pragma once

// for std::enable_if
// for std::false_type
// for std::integral_constant
// for std::true_type
#include <type_traits>

// using tint8
// using tint16
// using tint32
// using tint64
// using tuint8
// using tuint16
// using tuint32
// using tuint64
// using tfloat
// using tdouble
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

// using tbyte
// using tsize
// using tssize
namespace tractor
{
    using tbyte = tuint8;
    using tsize = tuint64;
    using tssize = tint64;
} // namespace tractor

// template struct is_basic_signed
// template struct is_basic_unsigned
// template struct is_basic_float
// template struct is_basic_integral
// template struct is_basic
// template constexpr is_basic_signed_v
// template constexpr is_basic_unsigned_v
// template constexpr is_basic_float_v
// template constexpr is_basic_integral_v
// template constexpr is_basic_v
// template struct enable_if_basic_signed
// template struct enable_if_basic_unsigned
// template struct enable_if_basic_float
// template struct enable_if_basic_integral
// template struct enable_if_basic
// template using enable_if_basic_signed_t
// template using enable_if_basic_unsigned_t
// template using enable_if_basic_float_t
// template using enable_if_basic_integral_t
// template using enable_if_basic_t
namespace tractor
{
    template <class type>
    struct is_basic_signed : public std::false_type
    {
    };

    template <>
    struct is_basic_signed<tint8> : public std::true_type
    {
    };

    template <>
    struct is_basic_signed<tint16> : public std::true_type
    {
    };

    template <>
    struct is_basic_signed<tint32> : public std::true_type
    {
    };

    template <>
    struct is_basic_signed<tint64> : public std::true_type
    {
    };

    template <class type>
    struct is_basic_unsigned : public std::false_type
    {
    };

    template <>
    struct is_basic_unsigned<tuint8> : public std::true_type
    {
    };

    template <>
    struct is_basic_unsigned<tuint16> : public std::true_type
    {
    };

    template <>
    struct is_basic_unsigned<tuint32> : public std::true_type
    {
    };

    template <>
    struct is_basic_unsigned<tuint64> : public std::true_type
    {
    };

    template <class type>
    struct is_basic_float : public std::false_type
    {
    };

    template <>
    struct is_basic_float<tfloat> : public std::true_type
    {
    };

    template <>
    struct is_basic_float<tdouble> : public std::true_type
    {
    };

    template <class type>
    struct is_basic_integral : public std::integral_constant<bool, is_basic_signed<type>::value || is_basic_unsigned<type>::value>
    {
    };

    template <class type>
    struct is_basic : public std::integral_constant<bool, is_basic_integral<type>::value || is_basic_float<type>::value>
    {
    };

    template <class type>
    constexpr bool is_basic_signed_v = is_basic_signed<type>::value;

    template <class type>
    constexpr bool is_basic_unsigned_v = is_basic_unsigned<type>::value;

    template <class type>
    constexpr bool is_basic_integral_v = is_basic_integral<type>::value;

    template <class type>
    constexpr bool is_basic_float_v = is_basic_float<type>::value;

    template <class type>
    constexpr bool is_basic_v = is_basic<type>::value;

    template <class type>
    struct enable_if_basic_signed : public std::enable_if<is_basic_signed_v<type>>
    {
    };

    template <class type>
    struct enable_if_basic_unsigned : public std::enable_if<is_basic_unsigned_v<type>>
    {
    };

    template <class type>
    struct enable_if_basic_integral : public std::enable_if<is_basic_integral_v<type>>
    {
    };

    template <class type>
    struct enable_if_basic_float : public std::enable_if<is_basic_float_v<type>>
    {
    };

    template <class type>
    struct enable_if_basic : public std::enable_if<is_basic_v<type>>
    {
    };

    template <class type>
    using enable_if_basic_signed_t = typename enable_if_basic_signed<type>::type;

    template <class type>
    using enable_if_basic_unsigned_t = typename enable_if_basic_unsigned<type>::type;

    template <class type>
    using enable_if_basic_integral_t = typename enable_if_basic_integral<type>::type;

    template <class type>
    using enable_if_basic_float_t = typename enable_if_basic_float<type>::type;

    template <class type>
    using enable_if_basic_t = typename enable_if_basic<type>::type;
} // namespace tractor
