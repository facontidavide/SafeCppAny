#ifndef VARIANT_NUMBER_LIMITS_H
#define VARIANT_NUMBER_LIMITS_H

#include <limits>
#include <boost/static_assert.hpp>
#include "VariantNumber/details/exceptions.h"

namespace VariantNumber
{


#define CAT_(a, b) a ## b
#define CAT(a, b) CAT_(a, b)
#define VARNUMBER_STATIC_ASSERT(cond) typedef int CAT(AsSeRt, __LINE__)[(cond) ? 1 : -1]


#define JOIN(lhs, rhs)    JOIN_1(lhs, rhs)
#define JOIN_1(lhs, rhs)  JOIN_2(lhs, rhs)
#define JOIN_2(lhs, rhs)  lhs##rhs

#define STATIC_ASSERT(expression, message)\
  struct JOIN(__static_assertion_at_line_, __LINE__)\
  {\
    impl::StaticAssertion<static_cast<bool>((expression))> JOIN(JOIN(JOIN(STATIC_ASSERTION_FAILED_AT_LINE_, __LINE__), _), message);\
  };\
  typedef impl::StaticAssertionTest<sizeof(JOIN(__static_assertion_at_line_, __LINE__))> JOIN(__static_assertion_test_at_line_, __LINE__)

namespace impl
{

template <bool>
struct StaticAssertion;

template <>
struct StaticAssertion<true>
{
}; // StaticAssertion<true>

template<int i>
struct StaticAssertionTest
{
}; // StaticAssertionTest<int>

} // namespace impl


template <typename F, typename T> void checkUpperLimit(const F& from)
{
    if ((sizeof(T) < sizeof(F)) && (from > static_cast<F>(std::numeric_limits<T>::max())))
    {
        throw RangeException("Value too large.");
    }
    else if (from > std::numeric_limits<T>::max())
    {
        throw RangeException("Value too large.");
    }
}

template <typename F, typename T> void checkUpperLimitFloat(const F& from)
{
    if (from > std::numeric_limits<T>::max())
        throw RangeException("Value too large.");
}

template <typename F, typename T> void checkLowerLimitFloat(const F& from)
{
    if (from < -static_cast<F>(std::numeric_limits<T>::max()) )
        throw RangeException("Value too small.");
}

template <typename F, typename T> void checkLowerLimit(const F& from )
{
    if (from < std::numeric_limits<T>::min())
        throw RangeException("Value too small.");
}

template <typename F, typename T>T convertToSmaller(const F& from)

{
    STATIC_ASSERT (std::numeric_limits<F>::is_specialized, _SOURCE_NOT_A_NUMBER);
    STATIC_ASSERT (std::numeric_limits<T>::is_specialized, _DESTINATION_NOT_A_NUMBER);
    STATIC_ASSERT (std::numeric_limits<F>::is_signed,      _SOURCE_MUST_BE_SIGNED);
    STATIC_ASSERT (std::numeric_limits<T>::is_signed,      _DESTINATION_MUST_BE_SIGNED);

    if (std::numeric_limits<F>::is_integer)
    {
        checkUpperLimit<F,T>(from);
        checkLowerLimit<F,T>(from);
    }
    else
    {
        checkUpperLimitFloat<F,T>(from);
        checkLowerLimitFloat<F,T>(from);
    }
    return static_cast<T>(from);
}


template <typename F, typename T>
T convertToSmallerUnsigned(const F& from)
{
    STATIC_ASSERT (std::numeric_limits<F>::is_specialized, _SOURCE_NOT_A_NUMBER);
    STATIC_ASSERT (std::numeric_limits<T>::is_specialized, _DESTINATION_NOT_A_NUMBER);
    STATIC_ASSERT (!std::numeric_limits<F>::is_signed,     _SOURCE_MUST_BE_UNSIGNED);
    STATIC_ASSERT (!std::numeric_limits<T>::is_signed,     _DESTINATION_MUST_BE_UNSIGNED);

    checkUpperLimit<F,T>(from);
    return static_cast<T>(from);
}



template <typename F, typename T>
T convertSignedToUnsigned(const F& from)
{
    STATIC_ASSERT (std::numeric_limits<F>::is_specialized, _SOURCE_NOT_A_NUMBER);
    STATIC_ASSERT (std::numeric_limits<T>::is_specialized, _DESTINATION_NOT_A_NUMBER);
    STATIC_ASSERT (std::numeric_limits<F>::is_signed,      _SOURCE_MUST_BE_SIGNED);
    STATIC_ASSERT (!std::numeric_limits<T>::is_signed,     _DESTINATION_MUST_BE_UNSIGNED);

    if (from < 0)
        throw RangeException("Value too small.");

    checkUpperLimit<F,T>(from);
    return static_cast<T>(from);
}


template <typename F, typename T> T convertSignedFloatToUnsigned(const F& from)
{
    STATIC_ASSERT (std::numeric_limits<F>::is_specialized, _SOURCE_NOT_A_NUMBER);
    STATIC_ASSERT (!std::numeric_limits<F>::is_integer,    _SOURCE_MUST_BE_FLOATINGPOINT);
    STATIC_ASSERT (std::numeric_limits<T>::is_integer,     _DESTINATION_NOT_AN_INTEGER);
    STATIC_ASSERT (!std::numeric_limits<T>::is_signed,     _DESTINATION_MUST_BE_UNSIGNED);

    if (from < 0)
        throw RangeException("Value too small.");

    checkUpperLimitFloat<F,T>(from);
    return static_cast<T>(from);
}


template <typename F, typename T> T convertUnsignedToSigned(const F& from)
{
    STATIC_ASSERT (std::numeric_limits<F>::is_specialized, _SOURCE_NOT_A_NUMBER);
    STATIC_ASSERT (std::numeric_limits<T>::is_specialized, _DESTINATION_NOT_A_NUMBER);
    STATIC_ASSERT (!std::numeric_limits<F>::is_signed,     _SOURCE_MUST_BE_UNSIGNED);
    STATIC_ASSERT (std::numeric_limits<T>::is_signed,      _DESTINATION_MUST_BE_SIGNED);

    checkUpperLimit<F,T>(from);
    return static_cast<T>(from);
}

} //end namespace

#endif
