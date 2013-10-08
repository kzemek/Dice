add_executable( test_dice
    TestBasicDie.cpp
)

target_link_libraries( test_dice
    dice
    ${TEST_LIBS}
)

add_test( test_dice test_dice )
