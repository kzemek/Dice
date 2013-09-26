cmake_minimum_required( VERSION 2.6 )
project( SRD )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -pedantic -std=c++11" )
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/" )

include_directories( src )
add_subdirectory( src )
add_subdirectory( test )
