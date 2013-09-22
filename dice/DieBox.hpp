#ifndef SRD_DICE_DIEBOX_HPP
#define SRD_DICE_DIEBOX_HPP

#include "Die.hpp"

#include <functional>

namespace dice {

class DieBox {
    friend class Dice;
    friend struct DieHashHelper;

private:
    using result_type = Die<4>::result_type;

    template<unsigned int sides, typename RandomEngine>
    DieBox( const Die<sides, RandomEngine> &die )
        : m_roll{ std::function<result_type()>{ &die.roll } }
        , m_sides{ sides }
    {}

    auto roll() const -> result_type {
        return m_roll();
    }

    const std::function<result_type()> m_roll;
    const unsigned int m_sides;
};

struct DieHashHelper {
    auto operator()( const DieBox &die ) const -> decltype(die.m_sides) {
        return die.m_sides;
    }

    auto operator()( const DieBox &lhs, const DieBox &rhs ) const -> bool {
        return lhs.m_sides == rhs.m_sides;
    }
};

}

#endif // SRD_DICE_DIEBOX_HPP
