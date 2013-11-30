#include "Dice.hpp"

#include <utility>

namespace dice {
    Dice::Dice( const Die &die, const unsigned int amount )
        : m_storedDice{ { die.clone(), amount } } {}

    auto Dice::roll() const -> result_type {
        result_type result = 0;

        for( const auto &entry: m_storedDice )
            result += entry.first->roll( entry.second );

        return result + m_bonus;
    }

    auto operator*( const unsigned int amount, const Die &die ) -> Dice {
        return { die, amount };
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

    auto operator-( const Dice &dice, const int bonus ) -> Dice {
        return operator+( dice, -bonus );
    }

    auto operator+( const Die &lhs, const Die &rhs ) -> Dice {
        return Dice{ lhs } + rhs;
    }
}
