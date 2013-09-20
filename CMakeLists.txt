cmake_minimum_required( VERSION 2.6 )
project( SRD )

SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11" )

add_subdirectory( dice )

add_executable( main main.cpp )
target_link_libraries( main dice )

