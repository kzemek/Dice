find_package( gmock )
include_directories( ${GMOCK_INCLUDE_DIR} )
include_directories( ${GTEST_INCLUDE_DIR} )

find_package( Threads )
set( TEST_LIBS ${CMAKE_THREAD_LIBS_INIT} ${GTEST_ALL_LIBRARIES} )

add_subdirectory( dice )
