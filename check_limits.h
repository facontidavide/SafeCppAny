
//    Copyright (c) <2015>, <Davide Faconti> All rights reserved.

//    Redistribution and use in source and binary forms, with or without
//    modification, are permitted provided that the following conditions are met:
//        * Redistributions of source code must retain the above copyright
//          notice, this list of conditions and the following disclaimer.
//        * Redistributions in binary form must reproduce the above copyright
//          notice, this list of conditions and the following disclaimer in the
//          documentation and/or other materials provided with the distribution.
//        * Neither the name of the <organization> nor the
//          names of its contributors may be used to endorse or promote products
//          derived from this software without specific prior written permission.

//    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//    DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
//    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


#ifndef SAFE_VARIANT_NUMBER_LIMITS_H
#define SAFE_VARIANT_NUMBER_LIMITS_H

#include <limits>
#include <exception>
#include <string>
#include <boost/static_assert.hpp>

class RangeException: public std::exception
{
public:

    explicit RangeException(const char* message): msg_(message)  {}
    explicit RangeException(const std::string& message):  msg_(message)  {}
    virtual ~RangeException() throw (){}
    virtual const char* what() const throw (){ return msg_.c_str(); }

protected:
    std::string msg_;
};



template <typename F, typename T>
void checkUpperLimit(const F& from)
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

template <typename F, typename T>
void checkUpperLimitFloat(const F& from)
{
    if (from > std::numeric_limits<T>::max())
        throw RangeException("Value too large.");
}

template <typename F, typename T>
void checkLowerLimitFloat(const F& from)
{
    if (from < -static_cast<F>(std::numeric_limits<T>::max()) )
        throw RangeException("Value too small.");
}

template <typename F, typename T>
void checkLowerLimit(const F& from )
{
    if (from < std::numeric_limits<T>::min())
        throw RangeException("Value too small.");
}

template <typename F, typename T>
T convertToSmaller(const F& from)
/// This function is meant to convert signed numeric values from
/// larger to smaller type. It checks the upper and lower bound and
/// if from value is within limits of type T (i.e. check calls do not throw),
/// it is converted.
{
    BOOST_STATIC_ASSERT (std::numeric_limits<F>::is_specialized);
    BOOST_STATIC_ASSERT (std::numeric_limits<T>::is_specialized);
    BOOST_STATIC_ASSERT (std::numeric_limits<F>::is_signed);
    BOOST_STATIC_ASSERT (std::numeric_limits<T>::is_signed);

    if (std::numeric_limits<F>::is_integer)
    {
        checkUpperLimit<F,T>(from);
        checkLowerLimit<F,T>(from);
    }
    else{
        checkUpperLimitFloat<F,T>(from);
        checkLowerLimitFloat<F,T>(from);
    }
    return static_cast<T>(from);
}


template <typename F, typename T>
T convertToSmallerUnsigned(const F& from)
{
    BOOST_STATIC_ASSERT (std::numeric_limits<F>::is_specialized);
    BOOST_STATIC_ASSERT (std::numeric_limits<T>::is_specialized);
    BOOST_STATIC_ASSERT (!std::numeric_limits<F>::is_signed);
    BOOST_STATIC_ASSERT (!std::numeric_limits<T>::is_signed);

    checkUpperLimit<F,T>(from);
    return static_cast<T>(from);
}



template <typename F, typename T>
T convertSignedToUnsigned(const F& from)
{
    BOOST_STATIC_ASSERT (std::numeric_limits<F>::is_specialized);
    BOOST_STATIC_ASSERT (std::numeric_limits<T>::is_specialized);
    BOOST_STATIC_ASSERT (std::numeric_limits<F>::is_signed);
    BOOST_STATIC_ASSERT (!std::numeric_limits<T>::is_signed);

    if (from < 0)
        throw RangeException("Value too small.");

    checkUpperLimit<F,T>(from);
    return static_cast<T>(from);
}


template <typename F, typename T>
T convertSignedFloatToUnsigned(const F& from)
{
    BOOST_STATIC_ASSERT (std::numeric_limits<T>::is_specialized);
    BOOST_STATIC_ASSERT (!std::numeric_limits<F>::is_integer);
    BOOST_STATIC_ASSERT (std::numeric_limits<T>::is_integer);
    BOOST_STATIC_ASSERT (!std::numeric_limits<T>::is_signed);

    if (from < 0)
        throw RangeException("Value too small.");

    checkUpperLimitFloat<F,T>(from);
    return static_cast<T>(from);
}


template <typename F, typename T>
T convertUnsignedToSigned(const F& from)
{
    BOOST_STATIC_ASSERT (std::numeric_limits<F>::is_specialized);
    BOOST_STATIC_ASSERT (std::numeric_limits<T>::is_specialized);
    BOOST_STATIC_ASSERT (!std::numeric_limits<F>::is_signed);
    BOOST_STATIC_ASSERT (std::numeric_limits<T>::is_signed);

    checkUpperLimit<F,T>(from);
    return static_cast<T>(from);
}

#endif // LIMITS_H

