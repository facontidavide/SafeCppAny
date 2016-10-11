#ifndef VARIANT_H
#define VARIANT_H

#include <type_traits>
#include "VariantNumber/typeid.h"
#include "VariantNumber/details/visitors.h"
#include "VariantNumber/details/exceptions.h"

namespace VariantNumber
{

class VarNumber
{

public:

    VarNumber()
    {
        _raw_data[8] = UNKNOWN_TYPE;
    }


    template<typename T> VarNumber(T value)
    {
        static_assert (std::numeric_limits<T>::is_specialized, "not a number");
        assign(value);
    }

    int getType() const
    {
        return _raw_data[8];
    }

    template<typename T> T convert( );
    /*{
        static_assert (std::numeric_limits<T>::is_specialized, "no specialization found for this type");
        return 0;
    }*/

    template<typename T> T extract( )
    {
        static_assert (std::numeric_limits<T>::is_specialized, "not a number");

        if( _raw_data[8] != getTypeID<T>() )
        {
            throw TypeException("ops");
        }
        return * reinterpret_cast<const T*>( _raw_data );
    }

    template <typename T> void assign(const T& value)
    {
        static_assert (std::numeric_limits<T>::is_specialized, "not a number");
        *reinterpret_cast<T *>( _raw_data ) =  value;
        _raw_data[8] = getTypeID<T>() ;
    }

private:
    uint8_t _raw_data[9];

    template <typename Derived,typename T> T  apply_visitor( basic_visitor<Derived, T> visitor);

};


//----------------------- Implementation ----------------------------------------------

#include "VariantNumber/details/variant_impl.h"



} //end namespace

#endif // VARIANT_H
