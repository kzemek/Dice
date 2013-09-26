add_subdirectory( dice )

add_executable( main main.cpp )
target_link_libraries( main dice )
