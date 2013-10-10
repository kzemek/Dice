#ifndef SRD_DICE_DICE_HPP
#define SRD_DICE_DICE_HPP

#include "Die.hpp"

#include <memory>
#include <unordered_map>

namespace dice {
    class Dice {
    public:
        using result_type = int;

        Dice( const Die &die, const unsigned int amount = 1 );
        auto roll() const -> result_type;

    private:
        int m_bonus = 0;
        std::unordered_map<std::shared_ptr<Die>, unsigned int,
                           DieHashHelper, DieHashHelper> m_storedDice;

        friend auto operator+( const Dice&, const Dice& ) -> Dice;
        friend auto operator+( const Dice&, const int ) -> Dice;
        friend auto operator-( const Dice&, const int ) -> Dice;
    };

    auto operator*( const unsigned int amount, const Die &die ) -> Dice;
}

#endif // SRD_DICE_DICE_HPP
