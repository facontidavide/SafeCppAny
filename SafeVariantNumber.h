
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


// to be defined (or not) before including visitors.h
#define USE_64BITS

#include "visitors.h"


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

bool operator == ( SafeVariantNumber& lhs,  SafeVariantNumber& rhs )
{
    return  boost::apply_visitor( are_equals(), lhs, rhs );
}

//-------------------------------------------------------------------


std::string to_string( SafeVariantNumber& val)
{
    return boost::apply_visitor (to_string_visitor(), val );
}

//-------------------------------------------------------------------

template<typename T> T extract(SafeVariantNumber& i )
{
    return boost::get<T>( i );
}




#endif // SAFE_VARIADIC_NUMBER

