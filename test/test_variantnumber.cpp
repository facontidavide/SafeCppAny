#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "VariantNumber/typeid.h"
#include "VariantNumber/variant.h"

TEST_CASE( "AssignAndExtract", "[int]" )
{
    using namespace VariantNumber;

    REQUIRE( sizeof(VarNumber) == 9 );

    VarNumber num( (int8_t) 42 );

    auto res1 = num.extract<int8_t>();
    REQUIRE( res1 == 42 );

    // these types are different and should throw
    REQUIRE_THROWS( num.extract<int16_t>() );
    REQUIRE_THROWS( num.extract<uint8_t>() );
    REQUIRE_THROWS( num.extract<float>() );

    // re-assign another number with a different type
    num.assign( 3.123f);
    auto res2 = num.extract<float>();
    REQUIRE( res2 ==  3.123f );

    REQUIRE_THROWS( num.extract<int16_t>() );
    REQUIRE_THROWS( num.extract<uint8_t>() );
    REQUIRE_THROWS( num.extract<double>() );
}

TEST_CASE( "Convert To larger", "[int]" )
{
    using namespace VariantNumber;

    {
        VarNumber num( (int8_t) 42 );
        REQUIRE( num.convert<int16_t>() == 42);
        REQUIRE( num.convert<int32_t>() == 42);
        REQUIRE( num.convert<float>() == 42);
    }

    {
        VarNumber num( (int8_t) -42 );
        REQUIRE( num.convert<int16_t>() == -42);
        REQUIRE( num.convert<int32_t>() == -42);
        REQUIRE( num.convert<float>() == -42);
    }

    {
        VarNumber num( (uint8_t) 42 );

        REQUIRE( num.convert<uint16_t>() == 42);
        REQUIRE( num.convert<int16_t>() == 42);
    }
}



