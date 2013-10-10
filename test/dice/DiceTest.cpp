#include "dice/Dice.hpp"

#include "utility/make_unique.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace dice;
using namespace testing;

class DiceTestFixture: public ::testing::Test {
private:
    class DieMock {
    public:
        MOCK_METHOD1( roll, Die::result_type(const unsigned int) );
        MOCK_CONST_METHOD0( clone, void() );
        MOCK_CONST_METHOD0( hash, std::size_t() );
    };

public:
    class DieMockWrapper: public Die {
    public:
        auto roll( const unsigned int amount = 1 ) -> result_type override {
            return dieMock->roll( amount );
        }

        auto clone() const -> std::unique_ptr<Die> override {
            dieMock->clone();
            return std::make_unique<DieMockWrapper>( *this );
        }

        auto hash() const -> std::size_t override {
            return dieMock->hash();
        }

        std::shared_ptr<DieMock> dieMock{ std::make_shared<NiceMock<DieMock>>() };
    };

    DieMockWrapper die;
    DieMock &dieMock = *die.dieMock;
};

TEST_F( DiceTestFixture, DieObjectShouldBeImplicitlyCastableToDice ) {
    Dice d = die;
}

TEST_F( DiceTestFixture, DiceObjectShouldStoreeItsOwnClonesOfDice ) {
    auto tempDie = std::make_unique<DieMockWrapper>();
    EXPECT_CALL( *tempDie->dieMock, clone() );

    Dice d( *tempDie );
    tempDie.reset();
    d.roll();
}

TEST_F( DiceTestFixture, DiceShouldDelegateRolls ) {
    EXPECT_CALL( dieMock, roll( 1 ) ).WillOnce( Return( 24 ) );
    ASSERT_EQ( Dice( die ).roll(), 24 );
}

TEST_F( DiceTestFixture, DiceShouldDelegateMultipleRolls ) {
    EXPECT_CALL( dieMock, roll( 128 ) ).WillOnce( Return( 73 ) );
    ASSERT_EQ( Dice( die, 128 ).roll(), 73 );
}

TEST_F( DiceTestFixture, MultiplyingSingleDieShouldGiveDice ) {
    Dice d = 128 * die;
}

TEST_F( DiceTestFixture, AddingDiceShouldYieldSumOfSets ) {
    DieMockWrapper otherDie;
    auto &otherDieMock = *otherDie.dieMock;

    EXPECT_CALL( dieMock, hash() ).WillRepeatedly( Return( 1 ) );
    EXPECT_CALL( otherDieMock, hash() ).WillRepeatedly( Return( 2 ) );

    EXPECT_CALL( dieMock, roll( 17 ) );
    EXPECT_CALL( dieMock, roll( 30 ) );
    EXPECT_CALL( otherDieMock, roll( 3 ) ).Times( 2 );

    (17 * die + 3 * otherDie).roll();
    (13 * die + 17 * die + 3 * otherDie).roll();
}

TEST_F( DiceTestFixture, BonusShouldBeAddedOnTopOfRoll ) {
    EXPECT_CALL( dieMock, roll(1) ).WillRepeatedly( Return( 13 ) );
    EXPECT_CALL( dieMock, roll(10) ).WillRepeatedly( Return( 130 ) );

    auto d = Dice( die ) + 17;
    ASSERT_EQ( d.roll(), 30 );

    auto d2 = d - 7;
    ASSERT_EQ( d2.roll(), 23 );

    auto d3 = 10 * die + 3;
    ASSERT_EQ( d3.roll(), 133 );
}

TEST_F( DiceTestFixture, BonusShouldBeAbleToBringRollResultToNegative ) {
    EXPECT_CALL( dieMock, roll(_) ).WillOnce( Return( 5 ) );

    auto d = Dice( die ) - 24;
    ASSERT_EQ( d.roll(), -19 );
}

TEST_F( DiceTestFixture, NegativeBonusShouldBeAddedProperly ) {
    EXPECT_CALL( dieMock, roll(_) ).WillOnce( Return( 2 ) );

    auto d = Dice( die ) + (-33);
    ASSERT_EQ( d.roll(), -31 );
}

TEST_F( DiceTestFixture, NegativeBonusShouldBeSubstractedProperly ) {
    EXPECT_CALL( dieMock, roll(_) ).WillOnce( Return( 7 ) );

    auto d = Dice( die ) - (-11);
    ASSERT_EQ( d.roll(), 18 );
}

TEST_F( DiceTestFixture, Bonus ) {
    EXPECT_CALL( dieMock, roll(_) ).WillOnce( Return( 2 ) );

    auto d = Dice( die ) + (-33);
    ASSERT_EQ( d.roll(), -31 );
}
