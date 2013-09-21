#ifndef SRD_DICE_DICE_HPP
#define SRD_DICE_DICE_HPP

#include "Die.hpp"

#include <unordered_map>

namespace dice {

class Dice {
public:
    Dice( const Die &die, const unsigned int amount = 1 );
    auto roll() const -> int;

private:
    int m_bonus = 0;
    std::unordered_map<Die, unsigned int /*amount*/,
                       DieHashHelper, DieHashHelper> m_storedDice;

    friend auto operator+( const Dice&, const Dice& ) -> Dice;
    friend auto operator+( const Dice&, const int ) -> Dice;
};

auto operator*( const unsigned int amount, const Die &die ) -> Dice;
auto operator+( const Dice &lhs, const Dice &rhs ) -> Dice;
auto operator+( const Dice &dice, const int bonus ) -> Dice;

}

#endif // SRD_DICE_DICE_HPP
