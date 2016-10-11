#ifndef VARIANT_NUMBER_LIMITS_H
#define VARIANT_NUMBER_LIMITS_H

#include <limits>
#include <type_traits>
#include "VariantNumber/details/exceptions.h"

namespace VariantNumber
{


template <typename SRC, typename DST> void checkUpperLimit(const SRC& from)
{
    if ((sizeof(DST) < sizeof(SRC)) && (from > static_cast<SRC>(std::numeric_limits<DST>::max())))
    {
        throw RangeException("Value too large.");
    }
    else if (from > std::numeric_limits<DST>::max())
    {
        throw RangeException("Value too large.");
    }
}

template <typename SRC, typename DST> void checkUpperLimitFloat(const SRC& from)
{
    if (from > std::numeric_limits<DST>::max())
        throw RangeException("Value too large.");
}

template <typename SRC, typename DST> void checkLowerLimitFloat(const SRC& from)
{
    if (from < -static_cast<SRC>(std::numeric_limits<DST>::max()) )
        throw RangeException("Value too small.");
}

template <typename SRC, typename DST> void checkLowerLimit(const SRC& from )
{
    if (from < std::numeric_limits<DST>::min())
        throw RangeException("Value too small.");
}

template <typename SRC, typename DST> DST convertToSmaller(const SRC& from)

{
    static_assert (std::numeric_limits<SRC>::is_specialized, "source type is not a number");
    static_assert (std::numeric_limits<DST>::is_specialized, "destination  type is not a number");
    static_assert (std::numeric_limits<SRC>::is_signed,      "source type must be signed");
    static_assert (std::numeric_limits<DST>::is_signed,      "destination type must be signed");

    if (std::numeric_limits<SRC>::is_integer)
    {
        checkUpperLimit<SRC,DST>(from);
        checkLowerLimit<SRC,DST>(from);
    }
    else
    {
        checkUpperLimitFloat<SRC,DST>(from);
        checkLowerLimitFloat<SRC,DST>(from);
    }
    return static_cast<DST>(from);
}


template <typename SRC, typename DST>
DST convertToSmallerUnsigned(const SRC& from)
{
    static_assert ( std::numeric_limits<SRC>::is_specialized, "source type is not a number");
    static_assert ( std::numeric_limits<DST>::is_specialized, "destination  type is not a number");
    static_assert (!std::numeric_limits<SRC>::is_signed,      "source type must be unsigned");
    static_assert (!std::numeric_limits<DST>::is_signed,      "destination type must be unsigned");

    checkUpperLimit<SRC,DST>(from);
    return static_cast<DST>(from);
}



template <typename SRC, typename DST>
DST convertSignedToUnsigned(const SRC& from)
{
    static_assert ( std::numeric_limits<SRC>::is_specialized, "source type is not a number");
    static_assert ( std::numeric_limits<DST>::is_specialized, "destination  type is not a number");
    static_assert ( std::numeric_limits<SRC>::is_signed,      "source type must be signed");
    static_assert (!std::numeric_limits<DST>::is_signed,      "destination type must be unsigned");

    if (from < 0)
        throw RangeException("Value too small.");

    checkUpperLimit<SRC,DST>(from);
    return static_cast<DST>(from);
}


template <typename SRC, typename DST> DST convertSignedFloatToUnsigned(const SRC& from)
{
    static_assert ( std::numeric_limits<SRC>::is_specialized, "source type is not a number");
    static_assert (!std::numeric_limits<SRC>::is_integer,     "source type must be floating point");
    static_assert ( std::numeric_limits<DST>::is_integer,     "destination type must be integer");
    static_assert (!std::numeric_limits<DST>::is_signed,      "destination type must be unsigned");

    if (from < 0)
        throw RangeException("Value too small.");

    checkUpperLimitFloat<SRC,DST>(from);
    return static_cast<DST>(from);
}


template <typename SRC, typename DST> DST convertUnsignedToSigned(const SRC& from)
{
    static_assert  (std::numeric_limits<SRC>::is_specialized, "source type is not a number");
    static_assert ( std::numeric_limits<DST>::is_specialized, "destination  type is not a number");
    static_assert (!std::numeric_limits<SRC>::is_signed,     "source type must be unsigned");
    static_assert ( std::numeric_limits<DST>::is_signed,      "destination type must be signed");

    checkUpperLimit<SRC,DST>(from);
    return static_cast<DST>(from);
}

} //end namespace

#endif
