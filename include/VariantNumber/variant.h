#ifndef VARIANT_H
#define VARIANT_H

#include "VariantNumber/details/visitors.h"

namespace VariantNumber
{

class VarNumber
{
private:
    union
    {
        int8_t     _int8;
        int16_t    _int16;
        int32_t    _int32;

        uint8_t     _uint8;
        uint16_t    _uint16;
        uint32_t    _uint32;

        float       _float;
    };

    uint8_t _type_id;

    template <typename Derived,typename T> T  apply_visitor( basic_visitor<Derived, T> visitor);

    template <typename T> void assign(const T& value)
    {
        _type_id = 255;
        throw TypeException("ops");
    }


public:

    VarNumber() : _type_id(255)
    {
    }


    template<typename T> VarNumber(T value)
    {
		STATIC_ASSERT (std::numeric_limits<T>::is_specialized, _NOT_A_NUMBER);
        assign(value);
    }

    int which() const
    {
        return _type_id;
    }

    std::string to_string()
    {
        return apply_visitor( to_string_visitor() );
    }

    template<typename T> T convert( )
    {
        return 0;
    }

    template<typename T> T extract( )
    {
        return 0;
    }

};


//----------------------- Implementation ----------------------------------------------

template <typename Derived,typename T> T  VarNumber::apply_visitor( basic_visitor<Derived, T> visitor)
{
    switch( _type_id )
    {
    case 1:
        return visitor( _int8 );
        break;
    case 2:
        return visitor( _int16 );
        break;
    case 3:
        return visitor( _int32 );
        break;
    case 4:
        return visitor( _uint8 );
        break;
    case 5:
        return visitor( _uint16 );
        break;
    case 6:
        return visitor( _uint32 );
        break;
    case 7:
        return visitor( _float );
        break;
    }
    return 0;
}

template <> inline void VarNumber::assign<int8_t>(const int8_t& value)
{
    _type_id = 1;
    _int8 = value;
}

template <> inline void VarNumber::assign<int16_t>(const int16_t& value)
{
    _type_id = 2;
    _int16 = value;
}

template <> inline void VarNumber::assign<int32_t>(const int32_t& value)
{
    _type_id = 3;
    _int32 = value;
}

template <> inline void VarNumber::assign<uint8_t>(const uint8_t& value)
{
    _type_id = 4;
    _uint8 = value;
}

template <> inline void VarNumber::assign<uint16_t>(const uint16_t& value)
{
    _type_id = 5;
    _uint16 = value;
}

template <> inline void VarNumber::assign<uint32_t>(const uint32_t& value)
{
    _type_id = 6;
    _uint32 = value;
}

template <> inline void VarNumber::assign<float>(const float& value)
{
    _type_id = 7;
    _float = value;
}
//------------------------------------
template <> inline int8_t VarNumber::extract<int8_t>()
{
    if( _type_id != 1 ) throw TypeException("wrong type");
    return _int8 ;
}

template <> inline int16_t VarNumber::extract<int16_t>()
{
    if( _type_id != 2 ) throw TypeException("wrong type");
    return _int16 ;
}

template <> inline int32_t VarNumber::extract<int32_t>()
{
    if( _type_id != 3 ) throw TypeException("wrong type");
    return _int32 ;
}

template <> inline uint8_t VarNumber::extract<uint8_t>()
{
    if( _type_id != 4 ) throw TypeException("wrong type");
    return _uint8 ;
}

template <> inline uint16_t VarNumber::extract<uint16_t>()
{
    if( _type_id != 5 ) throw TypeException("wrong type");
    return _uint16 ;
}

template <> inline uint32_t VarNumber::extract<uint32_t>()
{
    if( _type_id != 6 ) throw TypeException("wrong type");
    return _uint32 ;
}

template <> inline float VarNumber::extract<float>()
{
    if( _type_id != 7 ) throw TypeException("wrong type");
    return _float;
}



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

#ifdef USE_64BITS

template<> int64_t VariantNumber::convert<int64_t>()
{
    return  apply_visitor(convert_int64_t() );
}
template<> uint64_t VariantNumber::convert<uint64_t>()
{
    return  apply_visitor(convert_uint64_t() );
}
template<> double VariantNumber::convert<double>()
{
    return  apply_visitor(convert_double() );
}

#endif

} //end namespace

#endif // VARIANT_H

