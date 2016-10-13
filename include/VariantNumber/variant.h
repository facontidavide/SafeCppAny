#ifndef VARIANT_H
#define VARIANT_H

#include <type_traits>
#include <limits>
#include "VariantNumber/typeid.h"
#include "VariantNumber/details/exceptions.h"
#include "VariantNumber/details/conversion_impl.h"


namespace VariantNumber
{

class VarNumber
{

public:

    VarNumber() {
        _raw_data[8] = UNKNOWN_TYPE;
    }


    template<typename T> VarNumber(T value);

    int getType() const;

    template<typename T> T convert( );

    template<typename T> T extract( ) const;

    template <typename T> void assign(const T& value);

private:
    uint8_t _raw_data[9];

};


//----------------------- Implementation ----------------------------------------------


template<typename T>
inline VarNumber::VarNumber(T value)
{
    static_assert (std::numeric_limits<T>::is_specialized, "not a number");
    assign(value);
}

inline int VarNumber::getType() const {
    return _raw_data[8];
}

template<typename T>
inline T VarNumber::extract( ) const
{
    static_assert (std::numeric_limits<T>::is_specialized, "not a number");

    if( _raw_data[8] != getTypeID<T>() )
    {
        throw TypeException("ops");
    }
    return * reinterpret_cast<const T*>( _raw_data );
}

template <typename T>
inline void VarNumber::assign(const T& value)
{
    static_assert (std::numeric_limits<T>::is_specialized, "not a number");
    *reinterpret_cast<T *>( _raw_data ) =  value;
    _raw_data[8] = getTypeID<T>() ;
}

template<typename DST>
FORCE_INLINE DST VarNumber::convert()
{
    using namespace VariantNumber::details;
    DST target;

    //----------
    switch( _raw_data[8] )
    {
    case Int8:   convert_impl<int8_t,  DST>(*reinterpret_cast<const int8_t*>( _raw_data), target  ); break;
    case Int16:  convert_impl<int16_t, DST>(*reinterpret_cast<const int16_t*>( _raw_data), target  ); break;
    case Int32:  convert_impl<int32_t, DST>(*reinterpret_cast<const int32_t*>( _raw_data), target  ); break;
    case Int64:  convert_impl<int64_t, DST>(*reinterpret_cast<const int64_t*>( _raw_data), target  ); break;

    case UInt8:   convert_impl<uint8_t,  DST>(*reinterpret_cast<const uint8_t*>( _raw_data), target  ); break;
    case UInt16:  convert_impl<uint16_t, DST>(*reinterpret_cast<const uint16_t*>( _raw_data), target  ); break;
    case UInt32:  convert_impl<uint32_t, DST>(*reinterpret_cast<const uint32_t*>( _raw_data), target  ); break;
    case UInt64:  convert_impl<uint64_t, DST>(*reinterpret_cast<const uint64_t*>( _raw_data), target  ); break;

    case Real32:  convert_impl<float, DST>(*reinterpret_cast<const float*>( _raw_data), target  ); break;
    case Real64:  convert_impl<double, DST>(*reinterpret_cast<const double*>( _raw_data), target  ); break;

    default:  throw TypeException("ops"); break;

    }
    return  target;
}

} //end namespace





#endif // VARIANT_H
