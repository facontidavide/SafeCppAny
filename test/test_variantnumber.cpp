#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "VariantNumber/typeid.h"
#include "VariantNumber/variant.h"

TEST_CASE( "AssignAndExtract", "[int]" )
{
    using namespace VariantNumber;

    REQUIRE( sizeof(VarNumber) == 9 );
}
