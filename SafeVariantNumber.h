
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

#ifndef SAFE_VARIANT_NUMBER_H
#define SAFE_VARIANT_NUMBER_H

#include <stdint.h>
#include <boost/variant.hpp>
#include "check_limits.h"


#define USE_64BITS

typedef boost::variant<
    int8_t,
    int16_t,
    int32_t,
    uint8_t,
    uint16_t,
    uint32_t,
    float
#ifdef USE_64BITS
    ,double,
    int64_t,
    uint64_t
#endif
>
SafeVariantNumber;


class convert_int8_t: public boost::static_visitor<int8_t>
{
public:

    int8_t operator()(int8_t & i)   const { return i; }
    int8_t operator()(int16_t & i)  const { return convertToSmaller<int16_t, int8_t>( i ); }
    int8_t operator()(int32_t & i)  const { return convertToSmaller<int32_t, int8_t>( i ); }

    int8_t operator()(uint8_t & i)  const { return convertUnsignedToSigned<uint8_t,  int8_t>( i ); }
    int8_t operator()(uint16_t & i) const { return convertUnsignedToSigned<uint16_t, int8_t>( i ); }
    int8_t operator()(uint32_t & i) const { return convertUnsignedToSigned<uint32_t, int8_t>( i ); }

    int8_t operator()(float & i)    const { return convertToSmaller<float,int8_t>( i ); }

#ifdef USE_64BITS
    int8_t operator()(int64_t & i)  const { return convertToSmaller<int64_t, int8_t>( i );}
    int8_t operator()(uint64_t & i) const { return convertUnsignedToSigned<uint64_t, int8_t>( i ); }
    int8_t operator()(double & i)   const { return convertToSmaller<double,int8_t>( i ); }
#endif

};

class convert_int16_t: public boost::static_visitor<int16_t>
{
public:

    int16_t operator()(int8_t & i)   const { return i; }
    int16_t operator()(int16_t & i)  const { return i; }
    int16_t operator()(int32_t & i)  const { return convertToSmaller<int32_t,int16_t>( i ); }

    int16_t operator()(uint8_t & i)  const { return convertUnsignedToSigned<uint8_t,  int16_t>( i ); }
    int16_t operator()(uint16_t & i) const { return convertUnsignedToSigned<uint16_t, int16_t>( i ); }
    int16_t operator()(uint32_t & i) const { return convertUnsignedToSigned<uint32_t, int16_t>( i ); }

    int16_t operator()(float & i)    const { return convertToSmaller<float,int16_t>( i ); }

#ifdef USE_64BITS
    int16_t operator()(int64_t & i)  const { return convertToSmaller<int64_t, int16_t>( i );}
    int16_t operator()(uint64_t & i) const { return convertUnsignedToSigned<uint64_t, int16_t>( i ); }
    int16_t operator()(double & i)   const { return convertToSmaller<double, int16_t>( i ); }
#endif

};

class convert_int32_t: public boost::static_visitor<int32_t>
{
public:

    int32_t operator()(int8_t & i)   const { return i; }
    int32_t operator()(int16_t & i)  const { return i; }
    int32_t operator()(int32_t & i)  const { return i; }

    int32_t operator()(uint8_t & i)  const { return convertUnsignedToSigned<uint8_t,  int32_t>( i ); }
    int32_t operator()(uint16_t & i) const { return convertUnsignedToSigned<uint16_t, int32_t>( i ); }
    int32_t operator()(uint32_t & i) const { return convertUnsignedToSigned<uint32_t, int32_t>( i ); }

    int32_t operator()(float & i)    const { return convertToSmaller<float, int32_t>( i ); }

#ifdef USE_64BITS
    int32_t operator()(int64_t & i)  const { return convertToSmaller<int64_t, int32_t>( i );}
    int32_t operator()(uint64_t & i) const { return convertUnsignedToSigned<uint64_t, int32_t>( i ); }
    int32_t operator()(double & i)   const { return convertToSmaller<double, int32_t>( i ); }
#endif
};

//-------------------------------------------------------------------
class convert_uint8_t: public boost::static_visitor<uint8_t>
{
public:

    uint8_t operator()(int8_t & i)   const { return convertSignedToUnsigned<int8_t,  uint8_t>( i ); }
    uint8_t operator()(int16_t & i)  const { return convertSignedToUnsigned<int16_t, uint8_t>( i ); }
    uint8_t operator()(int32_t & i)  const { return convertSignedToUnsigned<int32_t, uint8_t>( i ); }

    uint8_t operator()(uint8_t & i)  const { return i; }
    uint8_t operator()(uint16_t & i) const { return convertToSmallerUnsigned<uint16_t, uint8_t>( i ); }
    uint8_t operator()(uint32_t & i) const { return convertToSmallerUnsigned<uint32_t, uint8_t>( i ); }

    uint8_t operator()(float & i)    const { return convertSignedFloatToUnsigned<float, uint8_t>( i );}

#ifdef USE_64BITS
    uint8_t operator()(int64_t & i)  const { return convertSignedToUnsigned<int64_t, uint8_t>( i );}
    uint8_t operator()(uint64_t & i) const { return convertToSmallerUnsigned<uint64_t, uint8_t>( i ); }
    uint8_t operator()(double & i)   const { return convertSignedFloatToUnsigned<double, uint8_t>( i ); }
#endif

};

class convert_uint16_t: public boost::static_visitor<uint16_t>
{
public:

    uint16_t operator()(int8_t & i)   const { return convertSignedToUnsigned<int8_t,  uint16_t>( i ); }
    uint16_t operator()(int16_t & i)  const { return convertSignedToUnsigned<int16_t, uint16_t>( i ); }
    uint16_t operator()(int32_t & i)  const { return convertSignedToUnsigned<int32_t, uint16_t>( i ); }

    uint16_t operator()(uint8_t & i)  const { return i; }
    uint16_t operator()(uint16_t & i) const { return i; }
    uint16_t operator()(uint32_t & i) const { return convertToSmallerUnsigned<uint32_t, uint16_t>( i ); }

    uint16_t operator()(float & i)    const { return convertSignedFloatToUnsigned<float, uint16_t>( i );}

#ifdef USE_64BITS
    uint16_t operator()(int64_t & i)  const { return convertSignedToUnsigned<int64_t, uint16_t>( i );}
    uint16_t operator()(uint64_t & i) const { return convertToSmallerUnsigned<uint64_t, uint16_t>( i ); }
    uint16_t operator()(double & i)   const { return convertSignedFloatToUnsigned<double, uint16_t>( i ); }
#endif

};

class convert_uint32_t: public boost::static_visitor<uint32_t>
{
public:

    uint32_t operator()(int8_t & i)   const { return convertSignedToUnsigned<int8_t,  uint32_t>( i ); }
    uint32_t operator()(int16_t & i)  const { return convertSignedToUnsigned<int16_t, uint32_t>( i ); }
    uint32_t operator()(int32_t & i)  const { return convertSignedToUnsigned<int32_t, uint32_t>( i ); }

    uint32_t operator()(uint8_t & i)  const { return i; }
    uint32_t operator()(uint16_t & i) const { return i; }
    uint32_t operator()(uint32_t & i) const { return i; }

    uint32_t operator()(float & i)    const { return convertSignedFloatToUnsigned<float, uint32_t>( i );}

#ifdef USE_64BITS
    uint32_t operator()(int64_t & i)  const { return convertSignedToUnsigned<int64_t, uint32_t>( i );}
    uint32_t operator()(uint64_t & i) const { return convertToSmallerUnsigned<uint64_t, uint32_t>( i ); }
    uint32_t operator()(double & i)   const { return convertSignedFloatToUnsigned<double, uint32_t>( i ); }
#endif

};

#ifdef USE_64BITS

class convert_int64_t: public boost::static_visitor<int64_t>
{
public:

    int64_t operator()(int8_t & i)   const { return i; }
    int64_t operator()(int16_t & i)  const { return i; }
    int64_t operator()(int32_t & i)  const { return i; }

    int64_t operator()(uint8_t & i)  const { return convertUnsignedToSigned<uint8_t,  int64_t>( i ); }
    int64_t operator()(uint16_t & i) const { return convertUnsignedToSigned<uint16_t, int64_t>( i ); }
    int64_t operator()(uint32_t & i) const { return convertUnsignedToSigned<uint32_t, int64_t>( i ); }

    int64_t operator()(float & i)    const { return convertToSmaller<float, int64_t>( i ); }

#ifdef USE_64BITS
    int64_t operator()(int64_t & i)  const { return i;}
    int64_t operator()(uint64_t & i) const { return convertUnsignedToSigned<uint64_t, int64_t>( i ); }
    int64_t operator()(double & i)   const { return convertToSmaller<double, int64_t>( i ); }
#endif
};


class convert_uint64_t: public boost::static_visitor<uint64_t>
{
public:

    uint64_t operator()(int8_t & i)   const { return convertSignedToUnsigned<int8_t,  uint64_t>( i ); }
    uint64_t operator()(int16_t & i)  const { return convertSignedToUnsigned<int16_t, uint64_t>( i ); }
    uint64_t operator()(int32_t & i)  const { return convertSignedToUnsigned<int32_t, uint64_t>( i ); }

    uint64_t operator()(uint8_t & i)  const { return i; }
    uint64_t operator()(uint16_t & i) const { return i; }
    uint64_t operator()(uint32_t & i) const { return i; }

    uint64_t operator()(float & i)    const { return convertSignedFloatToUnsigned<float, uint64_t>( i );}

    uint64_t operator()(int64_t & i)  const { return convertSignedToUnsigned<int64_t, uint64_t>( i ); }
    uint64_t operator()(uint64_t & i) const { return i; }
    uint64_t operator()(double & i)   const { return convertSignedFloatToUnsigned<double, uint64_t>( i ); }
};

#endif

//-------------------------------------------------------------------

class convert_float: public boost::static_visitor<float>
{
public:

    float operator()(int8_t & i)   const { return static_cast<float>(i); }
    float operator()(int16_t & i)  const { return static_cast<float>(i); }
    float operator()(int32_t & i)  const { return static_cast<float>(i); }

    float operator()(uint8_t & i)  const { return static_cast<float>(i); }
    float operator()(uint16_t & i) const { return static_cast<float>(i); }
    float operator()(uint32_t & i) const { return static_cast<float>(i); }

    float operator()(float & i)    const { return i;  }

#ifdef USE_64BITS
    float operator()(int64_t & i)  const { return static_cast<float>(i); }
    float operator()(uint64_t & i) const { return static_cast<float>(i); }
    float operator()(double & i)   const { return static_cast<float>(i); }
#endif
};

#ifdef USE_64BITS

class convert_double: public boost::static_visitor<double>
{
public:

    double operator()(int8_t & i)   const { return static_cast<double>(i); }
    double operator()(int16_t & i)  const { return static_cast<double>(i); }
    double operator()(int32_t & i)  const { return static_cast<double>(i); }

    double operator()(uint8_t & i)  const { return static_cast<double>(i); }
    double operator()(uint16_t & i) const { return static_cast<double>(i); }
    double operator()(uint32_t & i) const { return static_cast<double>(i); }

    double operator()(float & i)    const { return i;  }

    double operator()(int64_t & i)  const { return static_cast<double>(i); }
    double operator()(uint64_t & i) const { return static_cast<double>(i); }
    double operator()(double & i)   const { return static_cast<double>(i); }
};

#endif

//-------------------------------------------------------------------

template<typename T> T convert(SafeVariantNumber& any ) { return 0; }

template<> int8_t  convert<int8_t>(SafeVariantNumber& any )    {  return  boost::apply_visitor(convert_int8_t(), any ); }
template<> int16_t convert<int16_t>(SafeVariantNumber& any )   {  return  boost::apply_visitor(convert_int16_t(), any ); }
template<> int32_t convert<int32_t>(SafeVariantNumber& any )   {  return  boost::apply_visitor(convert_int32_t(), any ); }

template<> uint8_t  convert<uint8_t>(SafeVariantNumber& any )  {  return  boost::apply_visitor(convert_uint8_t(), any ); }
template<> uint16_t convert<uint16_t>(SafeVariantNumber& any ) {  return  boost::apply_visitor(convert_uint16_t(), any ); }
template<> uint32_t convert<uint32_t>(SafeVariantNumber& any ) {  return  boost::apply_visitor(convert_uint32_t(), any ); }

template<> float convert<float>(SafeVariantNumber& any )       {  return  boost::apply_visitor(convert_float(), any ); }
#ifdef USE_64BITS

template<> int64_t convert<int64_t>(SafeVariantNumber& any )   {  return  boost::apply_visitor(convert_int64_t(), any ); }
template<> uint64_t convert<uint64_t>(SafeVariantNumber& any ) {  return  boost::apply_visitor(convert_uint64_t(), any ); }
template<> double convert<double>(SafeVariantNumber& any )     {  return  boost::apply_visitor(convert_double(), any ); }

#endif
//-------------------------------------------------------------------

class are_equals: public boost::static_visitor<bool>
{
public:

    template <typename T, typename U>
    bool operator()( const T & lhs, const U & rhs ) const
    {
        return lhs == rhs ;
    }
};

bool operator == ( SafeVariantNumber& lhs,  SafeVariantNumber& rhs )
{
    return  boost::apply_visitor( are_equals(), lhs, rhs );
}

//-------------------------------------------------------------------

class to_string: public boost::static_visitor<std::string>
{
    template<typename T> std::string format(const char* format_description, T& value) const
    {
        char buffer[64];
        sprintf(buffer, format_description, value);
        return std::string(buffer);
    }

public:

    std::string operator()(int8_t & i)    const { return format("%d", i); }
    std::string operator()(int16_t & i)   const { return format("%d", i); }
    std::string operator()(int32_t & i)   const { return format("%ld", i); }

    std::string operator()(uint8_t & i)   const { return format("%u", i); }
    std::string operator()(uint16_t & i)  const { return format("%u", i); }
    std::string operator()(uint32_t & i)  const { return format("%lu", i); }

    std::string operator()(float & i)     const { return format("%f", i); }

#ifdef USE_64BITS
    std::string operator()(int64_t & i)    const { return format("%lld", i); }
    std::string operator()(uint64_t & i)   const { return format("%llu", i); }
    std::string operator()(double & i)     const { return format("%f", i); }

#endif
};




#endif // SAFE_VARIADIC_NUMBER
