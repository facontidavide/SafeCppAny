
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

//    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUDSTRS "AS IS" AND
//    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED DST, THE IMPLIED
//    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//    DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
//    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//    (INCLUDING, BUT NOT LIMITED DST, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR DSTRT
//    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


#ifndef VARIANT_NUMBER_VISIDSTRS_H
#define VARIANT_NUMBER_VISIDSTRS_H


#include <stdio.h>
#include <stdint.h>
#include "VariantNumber/details/check_limits.h"


namespace VariantNumber
{


template <typename Derived, typename T> class basic_visitor
{
public:

    T operator()(const int8_t & i)   const
    {
        return Derived()(i);
    }
    T operator()(const int16_t & i)  const
    {
        return Derived()(i);
    }
    T operator()(const int32_t & i)  const
    {
        return Derived()(i);
    }

    T operator()(const uint8_t & i)  const
    {
        return Derived()(i);
    }
    T operator()(const uint16_t & i) const
    {
        return Derived()(i);
    }
    T operator()(const uint32_t & i) const
    {
        return Derived()(i);
    }

    T operator()(const float & i)    const
    {
        return Derived()(i);
    }

    T operator()(const int64_t & i)  const
    {
        return Derived()(i);
    }

    T operator()(const uint64_t & i) const
    {
        return Derived()(i);
    }

    T operator()(const double & i)   const
    {
        return Derived()(i);
    }

};


//----------------------------------------------------------------------------------------


class convert_to_int8: public basic_visitor<convert_to_int8, int8_t>
{
public:

    int8_t operator()(const int8_t & i)   const
    {
        return i;
    }
    int8_t operator()(const int16_t & i)  const
    {
        return convertToSmaller<int16_t, int8_t>( i );
    }
    int8_t operator()(const int32_t & i)  const
    {
        return convertToSmaller<int32_t, int8_t>( i );
    }

    int8_t operator()(const uint8_t & i)  const
    {
        return convertUnsignedToSigned<uint8_t,  int8_t>( i );
    }
    int8_t operator()(const uint16_t & i) const
    {
        return convertUnsignedToSigned<uint16_t, int8_t>( i );
    }
    int8_t operator()(const uint32_t & i) const
    {
        return convertUnsignedToSigned<uint32_t, int8_t>( i );
    }

    int8_t operator()(const float & i)    const
    {
        return convertToSmaller<float,int8_t>( i );
    }


    int8_t operator()(const int64_t & i)  const
    {
        return convertToSmaller<int64_t, int8_t>( i );
    }
    int8_t operator()(const uint64_t & i) const
    {
        return convertUnsignedToSigned<uint64_t, int8_t>( i );
    }
    int8_t operator()(const double & i)   const
    {
        return convertToSmaller<double,int8_t>( i );
    }

};

class convert_to_int16: public basic_visitor<convert_to_int16,int16_t>
{
public:

    int16_t operator()(const int8_t & i)   const
    {
        return i;
    }
    int16_t operator()(const int16_t & i)  const
    {
        return i;
    }
    int16_t operator()(const int32_t & i)  const
    {
        return convertToSmaller<int32_t,int16_t>( i );
    }

    int16_t operator()(const uint8_t & i)  const
    {
        return convertUnsignedToSigned<uint8_t,  int16_t>( i );
    }
    int16_t operator()(const uint16_t & i) const
    {
        return convertUnsignedToSigned<uint16_t, int16_t>( i );
    }
    int16_t operator()(const uint32_t & i) const
    {
        return convertUnsignedToSigned<uint32_t, int16_t>( i );
    }

    int16_t operator()(const float & i)    const
    {
        return convertToSmaller<float,int16_t>( i );
    }

    int16_t operator()(const int64_t & i)  const
    {
        return convertToSmaller<int64_t, int16_t>( i );
    }

    int16_t operator()(const uint64_t & i) const
    {
        return convertUnsignedToSigned<uint64_t, int16_t>( i );
    }

    int16_t operator()(const double & i)   const
    {
        return convertToSmaller<double, int16_t>( i );
    }


};

class convert_to_int32: public basic_visitor<convert_to_int32,int32_t>
{
public:

    int32_t operator()(const int8_t & i)   const
    {
        return i;
    }

    int32_t operator()(const int16_t & i)  const
    {
        return i;
    }

    int32_t operator()(const int32_t & i)  const
    {
        return i;
    }

    int32_t operator()(const uint8_t & i)  const
    {
        return convertUnsignedToSigned<uint8_t,  int32_t>( i );
    }

    int32_t operator()(const uint16_t & i) const
    {
        return convertUnsignedToSigned<uint16_t, int32_t>( i );
    }

    int32_t operator()(const uint32_t & i) const
    {
        return convertUnsignedToSigned<uint32_t, int32_t>( i );
    }

    int32_t operator()(const float & i)    const
    {
        return convertToSmaller<float, int32_t>( i );
    }

    int32_t operator()(const int64_t & i)  const
    {
        return convertToSmaller<int64_t, int32_t>( i );
    }

    int32_t operator()(const uint64_t & i) const
    {
        return convertUnsignedToSigned<uint64_t, int32_t>( i );
    }

    int32_t operator()(const double & i)   const
    {
        return convertToSmaller<double, int32_t>( i );
    }

};

//-------------------------------------------------------------------
class convert_to_uint8: public basic_visitor<convert_to_uint8,uint8_t>
{
public:

    uint8_t operator()(const int8_t & i)   const
    {
        return convertSignedToUnsigned<int8_t,  uint8_t>( i );
    }
    uint8_t operator()(const int16_t & i)  const
    {
        return convertSignedToUnsigned<int16_t, uint8_t>( i );
    }
    uint8_t operator()(const int32_t & i)  const
    {
        return convertSignedToUnsigned<int32_t, uint8_t>( i );
    }

    uint8_t operator()(const uint8_t & i)  const
    {
        return i;
    }
    uint8_t operator()(const uint16_t & i) const
    {
        return convertToSmallerUnsigned<uint16_t, uint8_t>( i );
    }
    uint8_t operator()(const uint32_t & i) const
    {
        return convertToSmallerUnsigned<uint32_t, uint8_t>( i );
    }

    uint8_t operator()(const float & i)    const
    {
        return convertSignedFloatToUnsigned<float, uint8_t>( i );
    }

    uint8_t operator()(const int64_t & i)  const
    {
        return convertSignedToUnsigned<int64_t, uint8_t>( i );
    }
    uint8_t operator()(const uint64_t & i) const
    {
        return convertToSmallerUnsigned<uint64_t, uint8_t>( i );
    }
    uint8_t operator()(const double & i)   const
    {
        return convertSignedFloatToUnsigned<double, uint8_t>( i );
    }

};

class convert_to_uint16: public basic_visitor<convert_to_uint16,uint16_t>
{
public:

    uint16_t operator()(const int8_t & i)   const
    {
        return convertSignedToUnsigned<int8_t,  uint16_t>( i );
    }
    uint16_t operator()(const int16_t & i)  const
    {
        return convertSignedToUnsigned<int16_t, uint16_t>( i );
    }
    uint16_t operator()(const int32_t & i)  const
    {
        return convertSignedToUnsigned<int32_t, uint16_t>( i );
    }

    uint16_t operator()(const uint8_t & i)  const
    {
        return i;
    }
    uint16_t operator()(const uint16_t & i) const
    {
        return i;
    }
    uint16_t operator()(const uint32_t & i) const
    {
        return convertToSmallerUnsigned<uint32_t, uint16_t>( i );
    }

    uint16_t operator()(const float & i)    const
    {
        return convertSignedFloatToUnsigned<float, uint16_t>( i );
    }

    uint16_t operator()(const int64_t & i)  const
    {
        return convertSignedToUnsigned<int64_t, uint16_t>( i );
    }
    uint16_t operator()(const uint64_t & i) const
    {
        return convertToSmallerUnsigned<uint64_t, uint16_t>( i );
    }
    uint16_t operator()(const double & i)   const
    {
        return convertSignedFloatToUnsigned<double, uint16_t>( i );
    }

};

class convert_to_uint32: public basic_visitor<convert_to_uint32,uint32_t>
{
public:

    uint32_t operator()(const int8_t & i)   const
    {
        return convertSignedToUnsigned<int8_t,  uint32_t>( i );
    }
    uint32_t operator()(const int16_t & i)  const
    {
        return convertSignedToUnsigned<int16_t, uint32_t>( i );
    }
    uint32_t operator()(const int32_t & i)  const
    {
        return convertSignedToUnsigned<int32_t, uint32_t>( i );
    }

    uint32_t operator()(const uint8_t & i)  const
    {
        return i;
    }
    uint32_t operator()(const uint16_t & i) const
    {
        return i;
    }
    uint32_t operator()(const uint32_t & i) const
    {
        return i;
    }

    uint32_t operator()(const float & i)    const
    {
        return convertSignedFloatToUnsigned<float, uint32_t>( i );
    }

    uint32_t operator()(const int64_t & i)  const
    {
        return convertSignedToUnsigned<int64_t, uint32_t>( i );
    }
    uint32_t operator()(const uint64_t & i) const
    {
        return convertToSmallerUnsigned<uint64_t, uint32_t>( i );
    }
    uint32_t operator()(const double & i)   const
    {
        return convertSignedFloatToUnsigned<double, uint32_t>( i );
    }


};


class convert_int64_t: public basic_visitor<convert_int64_t,int64_t>
{
public:

    int64_t operator()(const int8_t & i)   const
    {
        return i;
    }
    int64_t operator()(const int16_t & i)  const
    {
        return i;
    }
    int64_t operator()(const int32_t & i)  const
    {
        return i;
    }

    int64_t operator()(const uint8_t & i)  const
    {
        return convertUnsignedToSigned<uint8_t,  int64_t>( i );
    }
    int64_t operator()(const uint16_t & i) const
    {
        return convertUnsignedToSigned<uint16_t, int64_t>( i );
    }
    int64_t operator()(const uint32_t & i) const
    {
        return convertUnsignedToSigned<uint32_t, int64_t>( i );
    }

    int64_t operator()(const float & i)    const
    {
        return convertToSmaller<float, int64_t>( i );
    }


    int64_t operator()(const int64_t & i)  const
    {
        return i;
    }
    int64_t operator()(const uint64_t & i) const
    {
        return convertUnsignedToSigned<uint64_t, int64_t>( i );
    }
    int64_t operator()(const double & i)   const
    {
        return convertToSmaller<double, int64_t>( i );
    }

};


class convert_uint64_t: public basic_visitor<convert_uint64_t,uint64_t>
{
public:

    uint64_t operator()(const int8_t & i)   const
    {
        return convertSignedToUnsigned<int8_t,  uint64_t>( i );
    }
    uint64_t operator()(const int16_t & i)  const
    {
        return convertSignedToUnsigned<int16_t, uint64_t>( i );
    }
    uint64_t operator()(const int32_t & i)  const
    {
        return convertSignedToUnsigned<int32_t, uint64_t>( i );
    }

    uint64_t operator()(const uint8_t & i)  const
    {
        return i;
    }
    uint64_t operator()(const uint16_t & i) const
    {
        return i;
    }
    uint64_t operator()(const uint32_t & i) const
    {
        return i;
    }

    uint64_t operator()(const float & i)    const
    {
        return convertSignedFloatToUnsigned<float, uint64_t>( i );
    }

    uint64_t operator()(const int64_t & i)  const
    {
        return convertSignedToUnsigned<int64_t, uint64_t>( i );
    }
    uint64_t operator()(const uint64_t & i) const
    {
        return i;
    }
    uint64_t operator()(const double & i)   const
    {
        return convertSignedFloatToUnsigned<double, uint64_t>( i );
    }
};



//-------------------------------------------------------------------

class convert_to_float: public basic_visitor<convert_to_float,float>
{
public:

    float operator()(const int8_t & i)   const
    {
        return static_cast<float>(i);
    }
    float operator()(const int16_t & i)  const
    {
        return static_cast<float>(i);
    }
    float operator()(const int32_t & i)  const
    {
        return static_cast<float>(i);
    }

    float operator()(const uint8_t & i)  const
    {
        return static_cast<float>(i);
    }
    float operator()(const uint16_t & i) const
    {
        return static_cast<float>(i);
    }
    float operator()(const uint32_t & i) const
    {
        return static_cast<float>(i);
    }

    float operator()(const float & i)    const
    {
        return i;
    }

    float operator()(const int64_t & i)  const
    {
        return static_cast<float>(i);
    }
    float operator()(const uint64_t & i) const
    {
        return static_cast<float>(i);
    }
    float operator()(const double & i)   const
    {
        return static_cast<float>(i);
    }

};


class convert_double: public basic_visitor<convert_double,double>
{
public:

    double operator()(const int8_t & i)   const
    {
        return static_cast<double>(i);
    }
    double operator()(const int16_t & i)  const
    {
        return static_cast<double>(i);
    }
    double operator()(const int32_t & i)  const
    {
        return static_cast<double>(i);
    }

    double operator()(const uint8_t & i)  const
    {
        return static_cast<double>(i);
    }
    double operator()(const uint16_t & i) const
    {
        return static_cast<double>(i);
    }
    double operator()(const uint32_t & i) const
    {
        return static_cast<double>(i);
    }

    double operator()(const float & i)    const
    {
        return i;
    }

    double operator()(const int64_t & i)  const
    {
        return static_cast<double>(i);
    }
    double operator()(const uint64_t & i) const
    {
        return static_cast<double>(i);
    }
    double operator()(const double & i)   const
    {
        return static_cast<double>(i);
    }
};



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

    std::string operator()(const int8_t & i)    const
    {
        return format("%d", i);
    }
    std::string operator()(const int16_t & i)   const
    {
        return format("%d", i);
    }
    std::string operator()(const int32_t & i)   const
    {
        return format("%ld", i);
    }

    std::string operator()(const uint8_t & i)   const
    {
        return format("%u", i);
    }
    std::string operator()(const uint16_t & i)  const
    {
        return format("%u", i);
    }
    std::string operator()(const uint32_t & i)  const
    {
        return format("%lu", i);
    }

    std::string operator()(const float & i)     const
    {
        return format("%f", i);
    }

    std::string operator()(const int64_t & i)    const
    {
        return format("%ld", i);
    }
    std::string operator()(const uint64_t & i)   const
    {
        return format("%lu", i);
    }
    std::string operator()(const double & i)     const
    {
        return format("%f", i);
    }

};

class are_equals: public basic_visitor<are_equals,bool>
{
public:

    template <typename T, typename U>
    bool operator()(const T & lhs, const U & rhs ) const
    {
        return lhs == rhs ;
    }
};

} //end namespace

#endif // VISIDSTRS

