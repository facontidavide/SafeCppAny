#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "SafeAny/safe_any.hpp"

using namespace SafeAny;

TEST_CASE( "AssignAndget", "[int]" )
{
    REQUIRE( sizeof(Any) == 3*sizeof(void*) );

    Any num( (int8_t) 42 );

    auto res1 = num.cast<int8_t>();
    REQUIRE( res1 == 42 );


    // re-assign another number with a different type
    num = Any( 3.123f );
    auto res2 = num.cast<float>();
    REQUIRE( res2 ==  3.123f );

    // throws because of numerical cancellation
    REQUIRE_THROWS( num.cast<int16_t>() );
    REQUIRE_THROWS( num.cast<uint8_t>() );

    // should be safe
    REQUIRE( Any( 3.0 ).cast<int16_t>() == 3);
    REQUIRE( Any( 3.0 ).cast<uint8_t>() == 3);

}

TEST_CASE( "Convert To larger", "[int]" )
{
    {
        Any num( (int8_t) 42 );
        REQUIRE( num.cast<int16_t>() == 42);
        REQUIRE( num.cast<int32_t>() == 42);
        REQUIRE( num.cast<float>() == 42.0f);
    }

    {
        Any num( (int8_t) -42 );
        REQUIRE( num.cast<int16_t>() == -42);
        REQUIRE( num.cast<int32_t>() == -42);
        REQUIRE( num.cast<float>() == -42.0f);
    }

    {
        Any num( (uint8_t) 42 );

        REQUIRE( num.cast<uint16_t>() == 42);
        REQUIRE( num.cast<int16_t>() == 42);
    }
}

TEST_CASE( "Bad casts", "[int]" )
{
    {
        Any num( int32_t(1000000) );
        REQUIRE_THROWS( num.cast<int16_t>());
        REQUIRE_THROWS( num.cast<int8_t>());
        REQUIRE( num.cast<float>() == 1000000.0f);
        REQUIRE( num.cast<int>()   == 1000000);
    }

    {
        Any num( int8_t(-42) );
        REQUIRE_THROWS( num.cast<uint8_t>() );
        REQUIRE_THROWS( num.cast<uint16_t>() );
        REQUIRE_THROWS( num.cast<uint32_t>() );
        REQUIRE( num.cast<int>()   == -42);
    }
}


TEST_CASE( "Basic", "Any" )
{
    REQUIRE( Any(int(250)).cast<uint8_t>() == 250 );

    REQUIRE_THROWS( Any(int(300)).cast<uint8_t>() );

    REQUIRE_THROWS( Any(int(-1)).cast<uint8_t>() );

    REQUIRE( Any(bool(true)).cast<uint8_t>() == 1 );

    REQUIRE( Any(char(100)).cast<uint8_t>() == 100 );
}

TEST_CASE( "String", "Any" )
{
    std::string hello("Hello");

    REQUIRE( Any(int(250)).cast<std::string>() == "250" );

    REQUIRE( Any(hello).cast<std::string>() == hello);

}

TEST_CASE( "Exotic types", "Any" )
{
    enum class Color{
        RED = 0,
        BLUE = 1,
        GREEN = 2 };

    struct Pos2D{ double x, y, z; };

    Pos2D in_pos = {1,2,3};
    Pos2D out_pos = Any(in_pos).cast<Pos2D>();

    REQUIRE( out_pos.x == in_pos.x );
    REQUIRE( out_pos.y == in_pos.y );
    REQUIRE( out_pos.z == in_pos.z );

    Color in_col = Color::BLUE;
    Color out_col = Any(in_col).cast<Color>();

    REQUIRE( in_col == out_col);

    REQUIRE_THROWS( Any(in_pos).cast<Color>() );
    REQUIRE_THROWS( Any(in_col).cast<Pos2D>() );

    REQUIRE_THROWS( Any(in_pos).cast<int>() );
    REQUIRE( Any(in_col).cast<int>() == 1 );

}

