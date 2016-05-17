#ifndef TYPEID_H
#define TYPEID_H

#include <stdint.h>

typedef enum {

    UNKNOWN_TYPE  = 0,
    UInt8  = 1 ,
    UInt16 = 2 ,
    UInt32 = 3 ,
    UInt64 = 4 ,

    Int8   = 5,
    Int16  = 6,
    Int32  = 7,
    Int64 =  8,

    Real32 = 9,
    Real64 = 10,

    LASTYPE   = 11

} TypeID;


inline uint8_t sizeOf( TypeID type)
{
    static  const uint8_t  size_of_types_list[ LASTYPE ]=
        {0,
         1,2,4,8,
         1,2,4,8,
         4,8
        };

    return size_of_types_list[ static_cast<uint8_t>(type) ];
}

inline const char* getName(TypeID type)
{
    static const char type_name_list[][20]={
        "Unknown",
        "UInt8",      "UInt16",         "UInt32",    "UInt64",
        "Int8",       "Int16",          "Int32",     "Int64",
        "Real64",     "Real64"
    };
    return type_name_list[ static_cast<uint8_t>(type) ];
}

template <typename T> TypeID getTypeID()
{
    return UNKNOWN_TYPE;
}

template <> TypeID getTypeID<int8_t>()  {  return Int8; }
template <> TypeID getTypeID<int16_t>() {  return Int16; }
template <> TypeID getTypeID<int32_t>() {  return Int32; }
template <> TypeID getTypeID<int64_t>() {  return Int64; }

template <> TypeID getTypeID<uint8_t>()  {  return UInt8; }
template <> TypeID getTypeID<uint16_t>() {  return UInt16; }
template <> TypeID getTypeID<uint32_t>() {  return UInt32; }
template <> TypeID getTypeID<uint64_t>() {  return UInt64; }

template <> TypeID getTypeID<float>()  {  return Real32; }
template <> TypeID getTypeID<double>() {  return Real64; }

#endif // TYPEID_H
