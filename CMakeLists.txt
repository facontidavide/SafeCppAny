project(AnyNumber)
cmake_minimum_required(VERSION 2.8)

add_compile_options(-std=c++11)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
   message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
   set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
   # Set the possible values of build type for cmake-gui
   set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo")
 endif()


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(benchmark)

INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/include )

add_executable(anynumber_test test/test_safeany.cpp )
TARGET_LINK_LIBRARIES( test  )


