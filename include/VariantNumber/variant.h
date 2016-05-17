#ifndef VARIANT_H
#define VARIANT_H

#include "VariantNumber/typeid.h"
#include "VariantNumber/details/visitors.h"

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
        STATIC_ASSERT (std::numeric_limits<T>::is_specialized, _NOT_A_NUMBER);
        assign(value);
    }

    int getType() const
    {
        return _raw_data[8];
    }

    template<typename T> T convert( )
    {
        STATIC_ASSERT (std::numeric_limits<T>::is_specialized, _NOT_A_NUMBER);
        return 0;
    }

    template<typename T> T extract( )
    {
        STATIC_ASSERT (std::numeric_limits<T>::is_specialized, _NOT_A_NUMBER);

        if( _raw_data[8] != getTypeID<T>() )
        {
            throw TypeException("ops");
        }
        return * reinterpret_cast<const T*>( _raw_data );
    }

    template <typename T> void assign(const T& )
    {
        STATIC_ASSERT (std::numeric_limits<T>::is_specialized, _NOT_A_NUMBER);
        _raw_data[8] = UNKNOWN_TYPE;
        throw TypeException("ops");
    }

private:
    uint8_t _raw_data[9];

    template <typename Derived,typename T> T  apply_visitor( basic_visitor<Derived, T> visitor);

};


//----------------------- Implementation ----------------------------------------------

#include "VariantNumber/details/variant_impl.h"

#endif // VARIANT_H

