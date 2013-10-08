cmake_minimum_required( VERSION 2.6 )
project( SRD )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++11 -Wfatal-errors" )
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/" )

include( CTest )
enable_testing()

include_directories( src )
add_subdirectory( src )
add_subdirectory( test )
