set( dice_SHARED OFF CACHE BOOL "Build dice as shared library" )
if( dice_SHARED )
    set( dice_LIBRARY_TYPE "SHARED" )
endif( dice_SHARED )

add_library( dice ${dice_LIBRARY_TYPE}
    BasicDie.cpp
    Dice.cpp
    Die.cpp
)
