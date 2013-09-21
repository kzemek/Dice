#include "Die.hpp"

#include <random>

namespace dice {

Die::Die( const unsigned int sides )
    : m_sides{ sides } {}

auto Die::roll() const -> unsigned int {
    static thread_local std::mt19937 generator{ std::random_device{}() };
    static thread_local std::uniform_int_distribution<decltype(roll())>
                        distribution{ 1, m_sides };

    return distribution( generator );
}

auto DieHashHelper::operator()( const Die &die ) const -> decltype(die.m_sides) {
    return die.m_sides;
}

auto DieHashHelper::operator()( const Die &lhs, const Die &rhs ) const -> bool {
    return lhs.m_sides == rhs.m_sides;
}

}
