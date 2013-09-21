#ifndef SRD_DICE_DIE_HPP
#define SRD_DICE_DIE_HPP

namespace dice {

class Die {
public:
    explicit Die( const unsigned int sides );
    auto roll() const -> unsigned int;

private:
    const unsigned int m_sides;
    
    friend struct DieHashHelper;
};

struct DieHashHelper {
    auto operator()( const Die &die ) const -> decltype(die.m_sides);
    auto operator()( const Die &lhs, const Die &rhs ) const -> bool;
};

}

#endif // SRD_DICE_DIE_HPP
