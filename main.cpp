#include "dice/include.hpp"
#include <iostream>

using namespace dice::basic;

dice::Dice omg() {
    dice::BasicDie<13> d13;
    return { d13 };
}

int omg2( dice::Dice dice ) {
    return dice.roll();
}

int main() {
    auto d = 102400000ll * dice::BasicDie<3>{};
    std::cout << d.roll() << std::endl;

    auto d2 = omg();
    std::cout << d2.roll() << std::endl;

    std::cout << omg2( d10 ) << std::endl;
    std::cout << d100.roll( 0 ) << std::endl;
}
