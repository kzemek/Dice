#ifndef SRD_DICE_DICE_HPP
#define SRD_DICE_DICE_HPP

#include "DieBox.hpp"

#include <unordered_map>

namespace dice {

class Dice {
public:
    using result_type = int;

    template<unsigned int sides, typename RandomEngine>
    Dice( const Die<sides, RandomEngine> &die, const unsigned int amount = 1 )
        : Dice( DieBox{ die }, amount ) {}

    auto roll() const -> result_type;

private:
    Dice( const DieBox &die, const unsigned int amount );

    int m_bonus = 0;
    std::unordered_map<DieBox, unsigned int /*amount*/,
                       DieHashHelper, DieHashHelper> m_storedDice;

    friend auto operator+( const Dice&, const Dice& ) -> Dice;
    friend auto operator+( const Dice&, const int ) -> Dice;
};

template<unsigned int sides, typename RandomEngine>
auto operator*( const unsigned int amount, const Die<sides, RandomEngine> &die ) -> Dice {
    return Dice( die, amount );
}

auto operator+( const Dice &lhs, const Dice &rhs ) -> Dice;
auto operator+( const Dice &dice, const int bonus ) -> Dice;

}

#endif // SRD_DICE_DICE_HPP
