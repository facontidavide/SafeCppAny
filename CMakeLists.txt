project(SafeVariadicNumber)
cmake_minimum_required(VERSION 2.8)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
   message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
   set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
   # Set the possible values of build type for cmake-gui
   set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo")
 endif()


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(PocoLib)
find_package(benchmark)

INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/include )



if( POCO_FOUND AND BENCHMARK_FOUND )

    message("building the benckmark")

    add_executable(benchmark_variant benchmark/benchmark.cpp )
    TARGET_LINK_LIBRARIES( benchmark_variant    benchmark pthread  PocoFoundation )

endif()



add_executable(test test/test_variantnumber.cpp )
TARGET_LINK_LIBRARIES( test  )


