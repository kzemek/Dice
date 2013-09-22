#include "Dice.hpp"

namespace dice {

Dice::Dice( const DieBox &die, const unsigned int amount )
    : m_storedDice{ { die, amount } } {}

auto Dice::roll() const -> result_type {
    result_type result = 0;

    for( const auto &entry: m_storedDice )
        for( auto amount = entry.second; amount > 0; --amount )
            result += entry.first.roll();

    return result + m_bonus;
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
