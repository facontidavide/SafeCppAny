
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


#ifndef VARIANT_NUMBER_VISITORS_H
#define VARIANT_NUMBER_VISITORS_H


#include <stdio.h>
#include <stdint.h>
#include "VariantNumber/details/check_limits.h"


namespace VariantNumber
{


template <typename Derived, typename T> class basic_visitor
{
public:

    T operator()(int8_t & i)   const
    {
        return Derived()(i);
    }
    T operator()(int16_t & i)  const
    {
        return Derived()(i);
    }
    T operator()(int32_t & i)  const
    {
        return Derived()(i);
    }

    T operator()(uint8_t & i)  const
    {
        return Derived()(i);
    }
    T operator()(uint16_t & i) const
    {
        return Derived()(i);
    }
    T operator()(uint32_t & i) const
    {
        return Derived()(i);
    }

    T operator()(float & i)    const
    {
        return Derived()(i);
    }

#ifdef USE_64BITS
    T operator()(int64_t & i)  const
    {
        return static_cast<Derived*>(this)->operator()(i);
    }
    T operator()(uint64_t & i) const
    {
        return static_cast<Derived*>(this)->operator()(i);
    }
    T operator()(double & i)   const
    {
        return static_cast<Derived*>(this)->operator()(i);
    }
#endif

};


//----------------------------------------------------------------------------------------


class convert_to_int8: public basic_visitor<convert_to_int8,int8_t>
{
public:

    int8_t operator()(int8_t & i)   const
    {
        return i;
    }
    int8_t operator()(int16_t & i)  const
    {
        return convertToSmaller<int16_t, int8_t>( i );
    }
    int8_t operator()(int32_t & i)  const
    {
        return convertToSmaller<int32_t, int8_t>( i );
    }

    int8_t operator()(uint8_t & i)  const
    {
        return convertUnsignedToSigned<uint8_t,  int8_t>( i );
    }
    int8_t operator()(uint16_t & i) const
    {
        return convertUnsignedToSigned<uint16_t, int8_t>( i );
    }
    int8_t operator()(uint32_t & i) const
    {
        return convertUnsignedToSigned<uint32_t, int8_t>( i );
    }

    int8_t operator()(float & i)    const
    {
        return convertToSmaller<float,int8_t>( i );
    }

#ifdef USE_64BITS
    int8_t operator()(int64_t & i)  const
    {
        return convertToSmaller<int64_t, int8_t>( i );
    }
    int8_t operator()(uint64_t & i) const
    {
        return convertUnsignedToSigned<uint64_t, int8_t>( i );
    }
    int8_t operator()(double & i)   const
    {
        return convertToSmaller<double,int8_t>( i );
    }
#endif

};

class convert_to_int16: public basic_visitor<convert_to_int16,int16_t>
{
public:

    int16_t operator()(int8_t & i)   const
    {
        return i;
    }
    int16_t operator()(int16_t & i)  const
    {
        return i;
    }
    int16_t operator()(int32_t & i)  const
    {
        return convertToSmaller<int32_t,int16_t>( i );
    }

    int16_t operator()(uint8_t & i)  const
    {
        return convertUnsignedToSigned<uint8_t,  int16_t>( i );
    }
    int16_t operator()(uint16_t & i) const
    {
        return convertUnsignedToSigned<uint16_t, int16_t>( i );
    }
    int16_t operator()(uint32_t & i) const
    {
        return convertUnsignedToSigned<uint32_t, int16_t>( i );
    }

    int16_t operator()(float & i)    const
    {
        return convertToSmaller<float,int16_t>( i );
    }

#ifdef USE_64BITS
    int16_t operator()(int64_t & i)  const
    {
        return convertToSmaller<int64_t, int16_t>( i );
    }
    int16_t operator()(uint64_t & i) const
    {
        return convertUnsignedToSigned<uint64_t, int16_t>( i );
    }
    int16_t operator()(double & i)   const
    {
        return convertToSmaller<double, int16_t>( i );
    }
#endif

};

class convert_to_int32: public basic_visitor<convert_to_int32,int32_t>
{
public:

    int32_t operator()(int8_t & i)   const
    {
        return i;
    }
    int32_t operator()(int16_t & i)  const
    {
        return i;
    }
    int32_t operator()(int32_t & i)  const
    {
        return i;
    }

    int32_t operator()(uint8_t & i)  const
    {
        return convertUnsignedToSigned<uint8_t,  int32_t>( i );
    }
    int32_t operator()(uint16_t & i) const
    {
        return convertUnsignedToSigned<uint16_t, int32_t>( i );
    }
    int32_t operator()(uint32_t & i) const
    {
        return convertUnsignedToSigned<uint32_t, int32_t>( i );
    }

    int32_t operator()(float & i)    const
    {
        return convertToSmaller<float, int32_t>( i );
    }

#ifdef USE_64BITS
    int32_t operator()(int64_t & i)  const
    {
        return convertToSmaller<int64_t, int32_t>( i );
    }
    int32_t operator()(uint64_t & i) const
    {
        return convertUnsignedToSigned<uint64_t, int32_t>( i );
    }
    int32_t operator()(double & i)   const
    {
        return convertToSmaller<double, int32_t>( i );
    }
#endif
};

//-------------------------------------------------------------------
class convert_to_uint8: public basic_visitor<convert_to_uint8,uint8_t>
{
public:

    uint8_t operator()(int8_t & i)   const
    {
        return convertSignedToUnsigned<int8_t,  uint8_t>( i );
    }
    uint8_t operator()(int16_t & i)  const
    {
        return convertSignedToUnsigned<int16_t, uint8_t>( i );
    }
    uint8_t operator()(int32_t & i)  const
    {
        return convertSignedToUnsigned<int32_t, uint8_t>( i );
    }

    uint8_t operator()(uint8_t & i)  const
    {
        return i;
    }
    uint8_t operator()(uint16_t & i) const
    {
        return convertToSmallerUnsigned<uint16_t, uint8_t>( i );
    }
    uint8_t operator()(uint32_t & i) const
    {
        return convertToSmallerUnsigned<uint32_t, uint8_t>( i );
    }

    uint8_t operator()(float & i)    const
    {
        return convertSignedFloatToUnsigned<float, uint8_t>( i );
    }

#ifdef USE_64BITS
    uint8_t operator()(int64_t & i)  const
    {
        return convertSignedToUnsigned<int64_t, uint8_t>( i );
    }
    uint8_t operator()(uint64_t & i) const
    {
        return convertToSmallerUnsigned<uint64_t, uint8_t>( i );
    }
    uint8_t operator()(double & i)   const
    {
        return convertSignedFloatToUnsigned<double, uint8_t>( i );
    }
#endif

};

class convert_to_uint16: public basic_visitor<convert_to_uint16,uint16_t>
{
public:

    uint16_t operator()(int8_t & i)   const
    {
        return convertSignedToUnsigned<int8_t,  uint16_t>( i );
    }
    uint16_t operator()(int16_t & i)  const
    {
        return convertSignedToUnsigned<int16_t, uint16_t>( i );
    }
    uint16_t operator()(int32_t & i)  const
    {
        return convertSignedToUnsigned<int32_t, uint16_t>( i );
    }

    uint16_t operator()(uint8_t & i)  const
    {
        return i;
    }
    uint16_t operator()(uint16_t & i) const
    {
        return i;
    }
    uint16_t operator()(uint32_t & i) const
    {
        return convertToSmallerUnsigned<uint32_t, uint16_t>( i );
    }

    uint16_t operator()(float & i)    const
    {
        return convertSignedFloatToUnsigned<float, uint16_t>( i );
    }

#ifdef USE_64BITS
    uint16_t operator()(int64_t & i)  const
    {
        return convertSignedToUnsigned<int64_t, uint16_t>( i );
    }
    uint16_t operator()(uint64_t & i) const
    {
        return convertToSmallerUnsigned<uint64_t, uint16_t>( i );
    }
    uint16_t operator()(double & i)   const
    {
        return convertSignedFloatToUnsigned<double, uint16_t>( i );
    }
#endif

};

class convert_to_uint32: public basic_visitor<convert_to_uint32,uint32_t>
{
public:

    uint32_t operator()(int8_t & i)   const
    {
        return convertSignedToUnsigned<int8_t,  uint32_t>( i );
    }
    uint32_t operator()(int16_t & i)  const
    {
        return convertSignedToUnsigned<int16_t, uint32_t>( i );
    }
    uint32_t operator()(int32_t & i)  const
    {
        return convertSignedToUnsigned<int32_t, uint32_t>( i );
    }

    uint32_t operator()(uint8_t & i)  const
    {
        return i;
    }
    uint32_t operator()(uint16_t & i) const
    {
        return i;
    }
    uint32_t operator()(uint32_t & i) const
    {
        return i;
    }

    uint32_t operator()(float & i)    const
    {
        return convertSignedFloatToUnsigned<float, uint32_t>( i );
    }

#ifdef USE_64BITS
    uint32_t operator()(int64_t & i)  const
    {
        return convertSignedToUnsigned<int64_t, uint32_t>( i );
    }
    uint32_t operator()(uint64_t & i) const
    {
        return convertToSmallerUnsigned<uint64_t, uint32_t>( i );
    }
    uint32_t operator()(double & i)   const
    {
        return convertSignedFloatToUnsigned<double, uint32_t>( i );
    }
#endif

};

#ifdef USE_64BITS

class convert_int64_t: public basic_visitor<convert_int64_t,int64_t>
{
public:

    int64_t operator()(int8_t & i)   const
    {
        return i;
    }
    int64_t operator()(int16_t & i)  const
    {
        return i;
    }
    int64_t operator()(int32_t & i)  const
    {
        return i;
    }

    int64_t operator()(uint8_t & i)  const
    {
        return convertUnsignedToSigned<uint8_t,  int64_t>( i );
    }
    int64_t operator()(uint16_t & i) const
    {
        return convertUnsignedToSigned<uint16_t, int64_t>( i );
    }
    int64_t operator()(uint32_t & i) const
    {
        return convertUnsignedToSigned<uint32_t, int64_t>( i );
    }

    int64_t operator()(float & i)    const
    {
        return convertToSmaller<float, int64_t>( i );
    }

#ifdef USE_64BITS
    int64_t operator()(int64_t & i)  const
    {
        return i;
    }
    int64_t operator()(uint64_t & i) const
    {
        return convertUnsignedToSigned<uint64_t, int64_t>( i );
    }
    int64_t operator()(double & i)   const
    {
        return convertToSmaller<double, int64_t>( i );
    }
#endif
};


class convert_uint64_t: public basic_visitor<convert_uint64_t,uint64_t>
{
public:

    uint64_t operator()(int8_t & i)   const
    {
        return convertSignedToUnsigned<int8_t,  uint64_t>( i );
    }
    uint64_t operator()(int16_t & i)  const
    {
        return convertSignedToUnsigned<int16_t, uint64_t>( i );
    }
    uint64_t operator()(int32_t & i)  const
    {
        return convertSignedToUnsigned<int32_t, uint64_t>( i );
    }

    uint64_t operator()(uint8_t & i)  const
    {
        return i;
    }
    uint64_t operator()(uint16_t & i) const
    {
        return i;
    }
    uint64_t operator()(uint32_t & i) const
    {
        return i;
    }

    uint64_t operator()(float & i)    const
    {
        return convertSignedFloatToUnsigned<float, uint64_t>( i );
    }

    uint64_t operator()(int64_t & i)  const
    {
        return convertSignedToUnsigned<int64_t, uint64_t>( i );
    }
    uint64_t operator()(uint64_t & i) const
    {
        return i;
    }
    uint64_t operator()(double & i)   const
    {
        return convertSignedFloatToUnsigned<double, uint64_t>( i );
    }
};

#endif

//-------------------------------------------------------------------

class convert_to_float: public basic_visitor<convert_to_float,float>
{
public:

    float operator()(int8_t & i)   const
    {
        return static_cast<float>(i);
    }
    float operator()(int16_t & i)  const
    {
        return static_cast<float>(i);
    }
    float operator()(int32_t & i)  const
    {
        return static_cast<float>(i);
    }

    float operator()(uint8_t & i)  const
    {
        return static_cast<float>(i);
    }
    float operator()(uint16_t & i) const
    {
        return static_cast<float>(i);
    }
    float operator()(uint32_t & i) const
    {
        return static_cast<float>(i);
    }

    float operator()(float & i)    const
    {
        return i;
    }

#ifdef USE_64BITS
    float operator()(int64_t & i)  const
    {
        return static_cast<float>(i);
    }
    float operator()(uint64_t & i) const
    {
        return static_cast<float>(i);
    }
    float operator()(double & i)   const
    {
        return static_cast<float>(i);
    }
#endif
};

#ifdef USE_64BITS

class convert_double: public basic_visitor<convert_double,double>
{
public:

    double operator()(int8_t & i)   const
    {
        return static_cast<double>(i);
    }
    double operator()(int16_t & i)  const
    {
        return static_cast<double>(i);
    }
    double operator()(int32_t & i)  const
    {
        return static_cast<double>(i);
    }

    double operator()(uint8_t & i)  const
    {
        return static_cast<double>(i);
    }
    double operator()(uint16_t & i) const
    {
        return static_cast<double>(i);
    }
    double operator()(uint32_t & i) const
    {
        return static_cast<double>(i);
    }

    double operator()(float & i)    const
    {
        return i;
    }

    double operator()(int64_t & i)  const
    {
        return static_cast<double>(i);
    }
    double operator()(uint64_t & i) const
    {
        return static_cast<double>(i);
    }
    double operator()(double & i)   const
    {
        return static_cast<double>(i);
    }
};

#endif

class to_string_visitor: public basic_visitor<to_string_visitor,std::string>
{
private:
    template <typename T> std::string format( const char* fmt, T& value) const
    {
        char buffer[64];
        sprintf(buffer, fmt, value);
        return std::string(buffer);
    }

public:

    std::string operator()(int8_t & i)    const
    {
        return format("%d", i);
    }
    std::string operator()(int16_t & i)   const
    {
        return format("%d", i);
    }
    std::string operator()(int32_t & i)   const
    {
        return format("%ld", i);
    }

    std::string operator()(uint8_t & i)   const
    {
        return format("%u", i);
    }
    std::string operator()(uint16_t & i)  const
    {
        return format("%u", i);
    }
    std::string operator()(uint32_t & i)  const
    {
        return format("%lu", i);
    }

    std::string operator()(float & i)     const
    {
        return format("%f", i);
    }

#ifdef USE_64BITS
    std::string operator()(int64_t & i)    const
    {
        return format("%ld", i);
    }
    std::string operator()(uint64_t & i)   const
    {
        return format("%lu", i);
    }
    std::string operator()(double & i)     const
    {
        return format("%f", i);
    }

#endif
};

class are_equals: public basic_visitor<are_equals,bool>
{
public:

    template <typename T, typename U>
    bool operator()( const T & lhs, const U & rhs ) const
    {
        return lhs == rhs ;
    }
};

} //end namespace

#endif // VISITORS

