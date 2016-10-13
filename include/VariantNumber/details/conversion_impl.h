#ifndef VARIANT_IMPL_H
#define VARIANT_IMPL_H

#include <type_traits>
#include <limits>
#include <iostream>
#include "VariantNumber/typeid.h"
#include "VariantNumber/details/exceptions.h"

namespace VariantNumber
{

namespace details{

template <typename T>
using Invoke = typename T::type;


template <typename BoolCondition>
using EnableIf = Invoke<std::enable_if<BoolCondition::value> >;


template <typename T>
struct is_integer : std::integral_constant<bool, std::is_integral<T>::value
        && !std::is_same<T, bool>::value
        && !std::is_same<T, char>::value>
{};

template <typename From, typename To>
struct is_safe_integer_conversion
        : std::integral_constant<bool, is_integer<From>::value
        && is_integer<To>::value
        && sizeof(From) <= sizeof(To)
&& std::is_signed<From>::value == std::is_signed<To>::value>
{};

template <typename From, typename To>
struct float_conversion
        : std::integral_constant<bool, std::is_floating_point<From>::value
        && std::is_floating_point<To>::value >
{};

template <typename From, typename To>
struct unsigned_to_smaller_conversion
        : std::integral_constant<bool, is_integer<From>::value
        && is_integer<To>::value
        && (sizeof(From) > sizeof(To))
&& !std::is_signed<From>::value
&& !std::is_signed<To>::value >
{};

template <typename From, typename To>
struct signed_to_smaller_conversion
        : std::integral_constant<bool, is_integer<From>::value
        && is_integer<To>::value
        && (sizeof(From) > sizeof(To))
&& std::is_signed<From>::value
&& std::is_signed<To>::value >
{};

//---------------------------
template <typename From, typename To>
struct signed_to_smaller_unsigned_conversion
        : std::integral_constant<bool, is_integer<From>::value
        && is_integer<To>::value
        && sizeof(From) >= sizeof(To)
&& std::is_signed<From>::value
&& !std::is_signed<To>::value >
{};

template <typename From, typename To>
struct signed_to_larger_unsigned_conversion
        : std::integral_constant<bool, is_integer<From>::value
        && is_integer<To>::value
        && sizeof(From) < sizeof(To)
&& std::is_signed<From>::value
&& !std::is_signed<To>::value >
{};

template <typename From, typename To>
struct unsigned_to_smaller_signed_conversion
        : std::integral_constant<bool, is_integer<From>::value
        && is_integer<To>::value
        && (sizeof(From) >= sizeof(To))
&& !std::is_signed<From>::value
&& std::is_signed<To>::value >
{};

template <typename From, typename To>
struct unsigned_to_larger_signed_conversion
        : std::integral_constant<bool, is_integer<From>::value
        && is_integer<To>::value
        && sizeof(From) < sizeof(To)
&& !std::is_signed<From>::value
&& std::is_signed<To>::value >
{};

template <typename From, typename To>
struct floating_to_signed_conversion
        : std::integral_constant<bool, std::is_floating_point<From>::value
        && is_integer<To>::value
        && std::is_signed<To>::value >
{};

template <typename From, typename To>
struct floating_to_unsigned_conversion
        : std::integral_constant<bool, std::is_floating_point<From>::value
        && is_integer<To>::value
        && !std::is_signed<To>::value >
{};

template <typename From, typename To>
struct integer_to_floating_conversion
        : std::integral_constant<bool, is_integer<From>::value
        && std::is_floating_point<To>::value >
{};

template <typename From, typename To>
FORCE_INLINE void checkUpperLimit(const From& from)
{
    if ((sizeof(To) < sizeof(From)) &&
        (from > static_cast<From>(std::numeric_limits<To>::max()))) {
        throw RangeException("Value too large.");
    }
    else if (static_cast<To>(from) > std::numeric_limits<To>::max()) {
        throw RangeException("Value too large.");
    }
}

template <typename From, typename To>
FORCE_INLINE void checkUpperLimitFloat(const From& from)
{
    if (from > std::numeric_limits<To>::max())
        throw RangeException("Value too large.");
}

template <typename From, typename To>
FORCE_INLINE void checkLowerLimitFloat(const From& from)
{
    if (from < -std::numeric_limits<To>::max())
        throw RangeException("Value too small.");
}

template <typename From, typename To>
FORCE_INLINE void checkLowerLimit(const From& from)
{
    if (from < std::numeric_limits<To>::min())
        throw RangeException("Value too small.");
}

template <typename From, typename To>
FORCE_INLINE void checkTruncation(const From& from)
{
    if( from != static_cast<From>(static_cast<To>( from)))
        throw RangeException("Floating point truncated");
}


//----------------------- Implementation ----------------------------------------------


template<typename SRC,typename DST,
         typename details::EnableIf< details::is_safe_integer_conversion<SRC, DST>>* = nullptr >
FORCE_INLINE void convert_impl( const SRC& from, DST& target )
{
    //std::cout << "is_safe_integer_conversion" << std::endl;
    target = static_cast<DST>( from);
}

template<typename SRC,typename DST,
         typename details::EnableIf< details::float_conversion<SRC, DST>>* = nullptr >
FORCE_INLINE void convert_impl( const SRC& from, DST& target )
{
    //std::cout << "float_conversion" << std::endl;
    checkTruncation<SRC,DST>(from);
    target = static_cast<DST>( from);
}


template<typename SRC,typename DST,
         typename details::EnableIf< details::unsigned_to_smaller_conversion<SRC, DST>>* = nullptr  >
FORCE_INLINE void convert_impl( const SRC& from, DST& target )
{
    //std::cout << "unsigned_to_smaller_conversion" << std::endl;

    checkUpperLimit<SRC,DST>(from);
    target = static_cast<DST>( from);
}

template<typename SRC,typename DST,
         typename details::EnableIf< details::signed_to_smaller_conversion<SRC, DST>>* = nullptr  >
FORCE_INLINE void convert_impl( const SRC& from, DST& target )
{
    //std::cout << "signed_to_smaller_conversion" << std::endl;
    checkLowerLimit<SRC,DST>(from);
    checkUpperLimit<SRC,DST>(from);
    target = static_cast<DST>( from);
}


template<typename SRC,typename DST,
         typename details::EnableIf< details::signed_to_smaller_unsigned_conversion<SRC, DST>>* = nullptr  >
FORCE_INLINE void convert_impl( const SRC& from, DST& target )
{
    //std::cout << "signed_to_smaller_unsigned_conversion" << std::endl;
    if (from < 0 )
        throw RangeException("Value is negative and can't be converted to signed");

    checkUpperLimit<SRC,DST>(from);

    target = static_cast<DST>( from);
}


template<typename SRC,typename DST,
         typename details::EnableIf< details::signed_to_larger_unsigned_conversion<SRC, DST>>* = nullptr   >
FORCE_INLINE void convert_impl( const SRC& from, DST& target )
{
    //std::cout << "signed_to_larger_unsigned_conversion" << std::endl;

    if ( from < 0 )
        throw RangeException("Value is negative and can't be converted to signed");

    target = static_cast<DST>( from);
}

template<typename SRC,typename DST,
         typename details::EnableIf< details::unsigned_to_larger_signed_conversion<SRC, DST>>* = nullptr   >
FORCE_INLINE void convert_impl( const SRC& from, DST& target )
{
    //std::cout << "unsigned_to_larger_signed_conversion" << std::endl;
    target = static_cast<DST>( from);
}

template<typename SRC,typename DST,
         typename details::EnableIf< details::unsigned_to_smaller_signed_conversion<SRC, DST>>* = nullptr   >
FORCE_INLINE void convert_impl( const SRC& from, DST& target )
{
    //std::cout << "unsigned_to_smaller_signed_conversion" << std::endl;

    checkUpperLimit<SRC,DST>(from);
    target = static_cast<DST>( from);
}

template<typename SRC,typename DST,
         typename details::EnableIf< details::floating_to_signed_conversion<SRC, DST>>* = nullptr   >
FORCE_INLINE void convert_impl( const SRC& from, DST& target )
{
    //std::cout << "floating_to_signed_conversion" << std::endl;

    checkLowerLimitFloat<SRC,DST>(from);
    checkLowerLimitFloat<SRC,DST>(from);

    if( from != static_cast<SRC>(static_cast<DST>( from)))
        throw RangeException("Floating point truncated");

    target = static_cast<DST>( from);
}

template<typename SRC,typename DST,
         typename details::EnableIf< details::floating_to_unsigned_conversion<SRC, DST>>* = nullptr   >
FORCE_INLINE void convert_impl( const SRC& from, DST& target )
{
    //std::cout << "floating_to_unsigned_conversion" << std::endl;
    if ( from < 0 )
        throw RangeException("Value is negative and can't be converted to signed");

    checkLowerLimitFloat<SRC,DST>(from);

    if( from != static_cast<SRC>(static_cast<DST>( from)))
        throw RangeException("Floating point truncated");

    target = static_cast<DST>( from);
}

template<typename SRC,typename DST,
         typename details::EnableIf< details::integer_to_floating_conversion<SRC, DST>>* = nullptr >
FORCE_INLINE void convert_impl( const SRC& from, DST& target )
{
    //std::cout << "floating_to_unsigned_conversion" << std::endl;

    checkTruncation<SRC,DST>(from);
    target = static_cast<DST>( from);
}

} //end namespace details

} //end namespace

#endif // VARIANT_H

