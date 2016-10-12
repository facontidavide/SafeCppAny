#ifndef VARIANT_H
#define VARIANT_H

#include <type_traits>
#include "VariantNumber/typeid.h"
#include "VariantNumber/details/exceptions.h"

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

} //end namespace

#include "VariantNumber/details/variant_impl.h"





#endif // VARIANT_H
