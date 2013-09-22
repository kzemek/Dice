#include "dice/include.hpp"
#include <iostream>

using namespace dice::basic;

int costam( const dice::Dice &d ) {
    return d.roll();
}

int main() {
    dice::Dice d = d12;
    std::cout << d4.roll() << " " << d.roll() << std::endl;

    std::cout << costam( d12 ) << std::endl;

    dice::Die<13> d13{};
    std::cout << (2*d13 + 10).roll() << std::endl;
}
