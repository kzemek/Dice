#include "Dice.hpp"

#include <utility>

namespace dice {

Dice::Dice( const Die &die, const unsigned int amount ) {
    m_storedDice.emplace( die, amount );
}

auto Dice::roll() const -> int {
    decltype(roll()) result = 0;

    for( const auto &entry: m_storedDice )
        for( auto amount = entry.second; amount > 0; --amount )
            result += entry.first.roll();

    return result + m_bonus;
}

auto operator*( const unsigned int amount, const Die &die ) -> Dice {
    return Dice( die, amount );
}

auto operator+( const Dice &lhs, const Dice &rhs ) -> Dice {
    Dice result{ lhs };
    for( const auto &entry: rhs.m_storedDice )
        result.m_storedDice[entry.first] += entry.second;

    result.m_bonus += rhs.m_bonus;
    return std::move( result );
}

auto operator+( const Dice &dice, const int bonus ) -> Dice {
    Dice result{ dice };
    result.m_bonus += bonus;
    return std::move( result );
}

}
