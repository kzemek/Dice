cmake_minimum_required( VERSION 2.6 )
project( SRD )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/" )
include( CTest )
enable_testing()

if( "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" )
    set( CMAKE_COMPILER_IS_CLANGCXX 1 )
endif( "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" )

if( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGCXX )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++11 -Wfatal-errors"
         CACHE STRING "g++/clang++ compiler flags for all builds" FORCE )
endif( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGCXX )

include_directories( src )
add_subdirectory( src )
add_subdirectory( test )
