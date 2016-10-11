#ifndef VARIANT_IMPL_H
#define VARIANT_IMPL_H

namespace detail{

    template <typename T>
    using Invoke = typename T::type;

    template <typename If, typename Then, typename Else>
    using Conditional = Invoke<std::conditional<If::value, Then, Else>>;

    // Logical conjunction metafunction
    template <typename... T>
    struct All : std::true_type {};

    template <typename Head, typename... Tail>
    struct All<Head, Tail...> : Conditional<Head, All<Tail...>, std::false_type> {};

  //  enum class enabled {}; // no value necessary

    enum class enabled { _ }; // just a type that can be used as a template parameter and is as inocuous as possible
    constexpr auto _dummy = enabled::_; // shortcut for dummy value (do not place _ in global scope!)

    template <typename BoolCondition>
    using EnableIf = Invoke<std::enable_if<BoolCondition::value, enabled> >;


    template <typename T>
    struct is_integer : std::integral_constant<bool, std::is_integral<T>::value
                                                         && !std::is_same<T, bool>::value
                                                         && !std::is_same<T, char>::value>
    {
    };

    template <typename From, typename To>
    struct is_safe_integer_conversion
        : std::integral_constant<bool, detail::is_integer<From>::value
                                           && detail::is_integer<To>::value
                                           && sizeof(From) <= sizeof(To)
                                           && std::is_signed<From>::value == std::is_signed<To>::value>
    {
    };

    template <typename From, typename To>
    struct unsigned_to_smaller_conversion
        : std::integral_constant<bool, detail::is_integer<From>::value
                                    && detail::is_integer<To>::value
                                    && (sizeof(From) > sizeof(To))
                                    && !std::is_signed<From>::value
                                    && !std::is_signed<To>::value >
    {
    };

    template <typename From, typename To>
    struct signed_to_smaller_conversion
        : std::integral_constant<bool, detail::is_integer<From>::value
                                    && detail::is_integer<To>::value
                                    && (sizeof(From) > sizeof(To))
                                    && std::is_signed<From>::value
                                    && std::is_signed<To>::value >
    {
    };

    //---------------------------
    template <typename From, typename To>
    struct signed_to_smaller_unsigned_conversion
        : std::integral_constant<bool, detail::is_integer<From>::value
                                    && detail::is_integer<To>::value
                                    && sizeof(From) >= sizeof(To)
                                    && std::is_signed<From>::value
                                    && !std::is_signed<To>::value >
    {
    };

    template <typename From, typename To>
    struct signed_to_larger_unsigned_conversion
        : std::integral_constant<bool, detail::is_integer<From>::value
                                    && detail::is_integer<To>::value
                                    && sizeof(From) < sizeof(To)
                                    && std::is_signed<From>::value
                                    && !std::is_signed<To>::value >
    {
    };

    template <typename From, typename To>
    struct unsigned_to_smaller_signed_conversion
        : std::integral_constant<bool, detail::is_integer<From>::value
                                    && detail::is_integer<To>::value
                                    && (sizeof(From) >= sizeof(To))
                                    && !std::is_signed<From>::value
                                    && std::is_signed<To>::value >
    {
    };

    template <typename From, typename To>
    struct unsigned_to_larger_signed_conversion
        : std::integral_constant<bool, detail::is_integer<From>::value
                                    && detail::is_integer<To>::value
                                    && sizeof(From) < sizeof(To)
                                    && !std::is_signed<From>::value
                                    && std::is_signed<To>::value >
    {
    };

    template <typename From, typename To>
    struct floating_to_signed_conversion
        : std::integral_constant<bool, std::is_floating_point<From>::value
                                    && detail::is_integer<To>::value
                                    && std::is_signed<To>::value >
    {
    };

    template <typename From, typename To>
    struct floating_to_unsigned_conversion
        : std::integral_constant<bool, std::is_floating_point<From>::value
                                    && detail::is_integer<To>::value
                                    && !std::is_signed<To>::value >
    {
    };

}

//----------------------- Implementation ----------------------------------------------

template<typename SRC,typename DST,
         detail::EnableIf< detail::is_safe_integer_conversion<SRC, DST>> = detail::_dummy  >
DST convert_impl( const SRC& from)
{
    return from;
}


template<typename SRC,typename DST,
         detail::EnableIf< detail::unsigned_to_smaller_conversion<SRC, DST>> = detail::_dummy  >
DST convert_impl( const SRC& from)
{
    if (from > static_cast<SRC>(std::numeric_limits<DST>::max()) )
        throw RangeException("Value larger than maximum limit");
    return from;
}

template<typename SRC,typename DST,
         detail::EnableIf< detail::signed_to_smaller_conversion<SRC, DST>> = detail::_dummy  >
DST convert_impl( const SRC& from)
{
    if (from > static_cast<SRC>(std::numeric_limits<DST>::max()) )
        throw RangeException("Value larger than maximum limit");

    if (from < static_cast<SRC>(std::numeric_limits<DST>::min()) )
        throw RangeException("Value smaller than minum limit");

    return from;
}


template<typename SRC,typename DST,
         detail::EnableIf< detail::signed_to_smaller_unsigned_conversion<SRC, DST>> = detail::_dummy  >
DST convert_impl( const SRC& from)
{
    if (from < 0 )
        throw RangeException("Value is negative and can't be converted to signed");

    if (from > static_cast<SRC>(std::numeric_limits<DST>::max()) )
        throw RangeException("Value larger than maximum limit");

    return from;
}


template<typename SRC,typename DST,
         detail::EnableIf< detail::signed_to_larger_unsigned_conversion<SRC, DST>> = detail::_dummy   >
DST convert_impl( const SRC& from)
{
    if ( from < 0 )
        throw RangeException("Value is negative and can't be converted to signed");
    return from;
}

template<typename SRC,typename DST,
         detail::EnableIf< detail::unsigned_to_larger_signed_conversion<SRC, DST>> = detail::_dummy   >
DST convert_impl( const SRC& from)
{
    return from;
}

template<typename SRC,typename DST,
         detail::EnableIf< detail::unsigned_to_smaller_signed_conversion<SRC, DST>> = detail::_dummy   >
DST convert_impl( const SRC& from)
{
    if ( from > static_cast<SRC>(std::numeric_limits<DST>::max()) )
        throw RangeException("Value larger than maximum limit");
    return from;
}

template<typename SRC,typename DST,
         detail::EnableIf< detail::floating_to_signed_conversion<SRC, DST>> = detail::_dummy   >
DST convert_impl( const SRC& from)
{
    if (from > (std::numeric_limits<DST>::max()) ||
        from < (std::numeric_limits<DST>::min()) )
        throw RangeException("Floating point out of range");

    if( from != static_cast<SRC>(static_cast<DST>(from)))
        throw RangeException("Floating point truncated");

    return from;
}

template<typename SRC,typename DST,
         detail::EnableIf< detail::floating_to_unsigned_conversion<SRC, DST>> = detail::_dummy   >
DST convert_impl( const SRC& from)
{
    if ( from <0 || from > std::numeric_limits<DST>::max())
        throw RangeException("Value out of range");

    if( from != static_cast<SRC>(static_cast<DST>(from)))
        throw RangeException("Floating point truncated");

    return from;
}


template<typename DST> DST VarNumber::convert()
{
    switch( _raw_data[8] )
    {
    case Int8:   return convert_impl<int8_t,  DST>( * reinterpret_cast<const int8_t *>( _raw_data)  );
    case Int16:  return convert_impl<int16_t, DST>( * reinterpret_cast<const int16_t *>( _raw_data) );
    case Int32:  return convert_impl<int32_t, DST>( * reinterpret_cast<const int32_t *>( _raw_data) );
    case Int64:  return convert_impl<int64_t, DST>( * reinterpret_cast<const int64_t *>( _raw_data) );

    case UInt8:   return convert_impl<uint8_t,  DST>( * reinterpret_cast<const uint8_t *>( _raw_data) );
    case UInt16:  return convert_impl<uint16_t, DST>( * reinterpret_cast<const uint16_t *>( _raw_data) );
    case UInt32:  return convert_impl<uint32_t, DST>( * reinterpret_cast<const uint32_t *>( _raw_data) );
    case UInt64:  return convert_impl<uint64_t, DST>( * reinterpret_cast<const uint64_t *>( _raw_data) );

    case Real32:  return convert_impl<float, DST>( * reinterpret_cast<const float *>( _raw_data) );
    case Real64:  return convert_impl<double, DST>( * reinterpret_cast<const double *>( _raw_data) );

    default:  throw TypeException("ops");

    }
    return  apply_visitor(convert_to_int8() );
}



#endif // VARIANT_H

