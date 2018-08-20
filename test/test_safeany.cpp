#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "SafeAny/safe_any.hpp"

using namespace SafeAny;

TEST_CASE( "AssignAndExtract", "[int]" )
{
    REQUIRE( sizeof(Any) == 3*sizeof(void*) );

    Any num( (int8_t) 42 );

    auto res1 = num.extract<int8_t>();
    REQUIRE( res1 == 42 );

    // these types are different and should throw
    REQUIRE_THROWS( num.extract<int16_t>() );
    REQUIRE_THROWS( num.extract<uint8_t>() );
    REQUIRE_THROWS( num.extract<float>() );

    // re-assign another number with a different type
    num = Any( 3.123f );
    auto res2 = num.extract<float>();
    REQUIRE( res2 ==  3.123f );

    REQUIRE_THROWS( num.extract<int16_t>() );
    REQUIRE_THROWS( num.extract<uint8_t>() );
    REQUIRE_THROWS( num.extract<double>() );
}

TEST_CASE( "Convert To larger", "[int]" )
{
    {
        Any num( (int8_t) 42 );
        REQUIRE( num.convert<int16_t>() == 42);
        REQUIRE( num.convert<int32_t>() == 42);
        REQUIRE( num.convert<float>() == 42);
    }

    {
        Any num( (int8_t) -42 );
        REQUIRE( num.convert<int16_t>() == -42);
        REQUIRE( num.convert<int32_t>() == -42);
        REQUIRE( num.convert<float>() == -42);
    }

    {
        Any num( (uint8_t) 42 );

        REQUIRE( num.convert<uint16_t>() == 42);
        REQUIRE( num.convert<int16_t>() == 42);
    }
}


TEST_CASE( "Basic", "Any" )
{
    REQUIRE( Any(int(250)).convert<uint8_t>() == 250 );

    REQUIRE_THROWS( Any(int(300)).convert<uint8_t>() );

    REQUIRE_THROWS( Any(int(-1)).convert<uint8_t>() );

    REQUIRE( Any(bool(true)).convert<uint8_t>() == 1 );

    REQUIRE( Any(char(100)).convert<uint8_t>() == 100 );
}

TEST_CASE( "String", "Any" )
{
    std::string hello("Hello");

    REQUIRE( Any(int(250)).convert<std::string>() == "250" );

    REQUIRE( Any(hello).extract<std::string>() == hello);

}


