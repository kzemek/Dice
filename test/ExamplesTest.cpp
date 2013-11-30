#include "dice/include.hpp"

#include <gtest/gtest.h>

TEST( TestExamples, example1 ) {
    using namespace dice::basic;
    using dice::Dice;

    d20.roll();         // d20 is of type Die
    Dice dice = d20;    // but is implicitly converted to Dice
    dice.roll();
}

TEST( TestExamples, example2 ) {
    using namespace dice::basic;
    using dice::Dice;

    Dice d{ d4, 2 };    // create dice collection consisting of two four-sided dice
    d.roll();
}

TEST( TestExamples, example3 ) {
    using namespace dice::basic;
    using dice::Dice;

    auto d = 2*d4;      // create dice collection consisting of two four-sided dice
    d.roll();
}

TEST( TestExamples, example4 ) {
    using namespace dice::basic;
    using dice::Dice;

    auto d = 2*d12 + 4;
    d.roll();           // returns a number between 6 (2*1 + 4) and 28 (2*12 + 4)

    d = d - 8;
    d.roll();           // returns a number between -2 (2*1 - 4) and 20 (2*12 - 4)
}

TEST( TestExamples, example5 ) {
    using namespace dice::basic;
    using dice::Dice;
    using dice::Die;

    auto d = d6 + d4;
    d = d + 2 * d12;
    d = d + 2*d6;       // d = 3*d6 + d4 + 2*d12
    d.roll();
}

TEST( TestExamples, example6 ) {
    using dice::BasicDie;
    using dice::Dice;

    BasicDie<13> d13;
    d13.roll();

    auto d = 3*d13;
    d.roll();
}

TEST( TestExamples, example7 ) {
    using dice::BasicDie;

    BasicDie<4, std::knuth_b> d4;
    d4.roll();
}

TEST( TestExamples, example8 ) {
    class MyDie: public dice::Die {
    public:
        auto roll( const unsigned int times = 1 ) -> result_type override {
            return times * 24;
        }

        auto clone() const -> std::unique_ptr<Die> override {
            return utility::make_unique<MyDie>( *this );
        }

    private:
        auto hash() const -> std::size_t override {
            return 24;
        }
    };

    MyDie my;
    auto d = 5*my;
    d.roll();
}
