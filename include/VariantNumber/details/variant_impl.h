#ifndef VARIANT_IMPL_H
#define VARIANT_IMPL_H


//----------------------- Implementation ----------------------------------------------

template <typename Derived,typename T> T  VarNumber::apply_visitor( basic_visitor<Derived, T> visitor)
{
    switch( _raw_data[8] )
    {
    case Int8:   return visitor( * reinterpret_cast<const int8_t *>( _raw_data)  );
    case Int16:  return visitor( * reinterpret_cast<const int16_t *>( _raw_data) );
    case Int32:  return visitor( * reinterpret_cast<const int32_t *>( _raw_data) );
    case Int64:  return visitor( * reinterpret_cast<const int64_t *>( _raw_data) );

    case UInt8:   return visitor( * reinterpret_cast<const uint8_t *>( _raw_data) );
    case UInt16:  return visitor( * reinterpret_cast<const uint16_t *>( _raw_data) );
    case UInt32:  return visitor( * reinterpret_cast<const uint32_t *>( _raw_data) );
    case UInt64:  return visitor( * reinterpret_cast<const uint64_t *>( _raw_data) );

    case Real32:  return visitor( * reinterpret_cast<const float *>( _raw_data) );
    case Real64:  return visitor( * reinterpret_cast<const double *>( _raw_data) );

    default:   return 0;

    }
}

template <> inline void VarNumber::assign<int8_t>(const int8_t& value)
{
    *reinterpret_cast<int8_t *>( _raw_data ) =  value;
    _raw_data[8] = Int8;
}

template <> inline void VarNumber::assign<int16_t>(const int16_t& value)
{
    *reinterpret_cast<int16_t *>( _raw_data ) =  value;
    _raw_data[8] = Int16;
}

template <> inline void VarNumber::assign<int32_t>(const int32_t& value)
{
    *reinterpret_cast<int32_t *>( _raw_data ) =  value;
    _raw_data[8] = Int32;
}

template <> inline void VarNumber::assign<int64_t>(const int64_t& value)
{
   *reinterpret_cast<int64_t *>( _raw_data ) =  value;
    _raw_data[8] = Int64;
}

template <> inline void VarNumber::assign<uint8_t>(const uint8_t& value)
{
    *reinterpret_cast<uint8_t *>( _raw_data ) =  value;
    _raw_data[8] = UInt8;
}

template <> inline void VarNumber::assign<uint16_t>(const uint16_t& value)
{
    *reinterpret_cast<uint16_t *>( _raw_data ) =  value;
    _raw_data[8] = UInt16;
}

template <> inline void VarNumber::assign<uint32_t>(const uint32_t& value)
{
    *reinterpret_cast<uint32_t *>( _raw_data ) =  value;
    _raw_data[8] = UInt32;
}

template <> inline void VarNumber::assign<uint64_t>(const uint64_t& value)
{
     *reinterpret_cast<uint64_t *>( _raw_data ) =  value;
    _raw_data[8] = UInt64;
}

template <> inline void VarNumber::assign<float>(const float& value)
{
    *reinterpret_cast<float *>( _raw_data ) =  value;
    _raw_data[8] = Real32;
}

template <> inline void VarNumber::assign<double>(const double& value)
{
    *reinterpret_cast<double *>( _raw_data ) =  value;
    _raw_data[8] = Real64;
}

//------------------------------------------------------

template<> int8_t  VarNumber::convert<int8_t>()
{
    return  apply_visitor(convert_to_int8() );
}

template<> int16_t VarNumber::convert<int16_t>( )
{
    return  apply_visitor(convert_to_int16() );
}
template<> int32_t VarNumber::convert<int32_t>()
{
    return  apply_visitor(convert_to_int32() );
}

template<> uint8_t  VarNumber::convert<uint8_t>()
{
    return  apply_visitor(convert_to_uint8() );
}
template<> uint16_t VarNumber::convert<uint16_t>()
{
    return  apply_visitor(convert_to_uint16() );
}
template<> uint32_t VarNumber::convert<uint32_t>()
{
    return  apply_visitor(convert_to_uint32() );
}

template<> float VarNumber::convert<float>()
{
    return  apply_visitor(convert_to_float() );
}


template<> int64_t VarNumber::convert<int64_t>()
{
    return  apply_visitor(convert_int64_t() );
}

template<> uint64_t VarNumber::convert<uint64_t>()
{
    return  apply_visitor(convert_uint64_t() );
}

template<> double VarNumber::convert<double>()
{
    return  apply_visitor(convert_double() );
}



} //end namespace

#endif // VARIANT_H

