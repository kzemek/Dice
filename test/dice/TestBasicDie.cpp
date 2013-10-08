#include "dice/BasicDie.hpp"

#include "utility/make_unique.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <array>

using namespace dice;
using namespace testing;

class RandomEngineFixture: public ::testing::Test {
private:
    class RandomEngineMock {
    public:
        MOCK_METHOD1( constructor, void(unsigned int) );
        MOCK_METHOD0( operatorParentheses, unsigned int() );
    };

    static RandomEngineMock *g_randomEngineMock;

public:
    class RandomEngineMockProxy {
    public:
        using result_type = unsigned int;

        explicit RandomEngineMockProxy( result_type value = 0 ) {
            g_randomEngineMock->constructor( value );
        }

        auto operator()() -> result_type {
            return g_randomEngineMock->operatorParentheses();
        }

        auto seed( result_type ) -> void {}
        auto discard( unsigned long long ) -> void {}
        static constexpr auto min() -> result_type { return 0; }
        static constexpr auto max() -> result_type { return 11; }
    };

    NiceMock<RandomEngineMock> randomEngineMock;

    RandomEngineFixture() {
        g_randomEngineMock = &randomEngineMock;
    }

    ~RandomEngineFixture() {
        g_randomEngineMock = nullptr;
    }
};

RandomEngineFixture::RandomEngineMock *RandomEngineFixture::g_randomEngineMock{ nullptr };


TEST_F( RandomEngineFixture, RandomEngineShouldBeCreatedOnRoll ) {
    EXPECT_CALL( randomEngineMock, constructor(_) );
    BasicDie<10, RandomEngineMockProxy>{}.roll();
}

TEST_F( RandomEngineFixture, RandomEngineShouldBeSeeded ) {
    unsigned int lastSeed = 0;

    EXPECT_CALL( randomEngineMock, constructor( Ne(0) ) ).WillOnce( SaveArg<0>( &lastSeed ) );
    BasicDie<13, RandomEngineMockProxy>{}.roll();

    Mock::VerifyAndClearExpectations( &randomEngineMock );

    EXPECT_CALL( randomEngineMock, constructor( Ne( ByRef( lastSeed ) ) ) );
    BasicDie<14, RandomEngineMockProxy>{}.roll();
}

TEST_F( RandomEngineFixture, RandomEngineShouldBeSharedBetweenDiceOfSameClass ) {
    EXPECT_CALL( randomEngineMock, constructor(_) );
    BasicDie<15, RandomEngineMockProxy>{}.roll();
    BasicDie<15, RandomEngineMockProxy>{}.roll();

    Mock::VerifyAndClearExpectations( &randomEngineMock );

    EXPECT_CALL( randomEngineMock, constructor(_) );
    BasicDie<16, RandomEngineMockProxy>{}.roll();
}

TEST_F( RandomEngineFixture, RandomEngineShouldBeUsedForRolls ) {
    EXPECT_CALL( randomEngineMock, operatorParentheses() ).Times( AtLeast( 1 ) );
    BasicDie<17, RandomEngineMockProxy>{}.roll();
}

TEST( BasicDieTest, PopularDiceTypesAreAvailable ) {
    dice::basic::d4.roll();
    dice::basic::d6.roll();
    dice::basic::d8.roll();
    dice::basic::d10.roll();
    dice::basic::d12.roll();
    dice::basic::d20.roll();
    dice::basic::d100.roll();
}

TEST( BasicDieTest, RollShouldOnlyReturnValuesBetweenOneAndMax ) {
    BasicDie<1> d1;
    for( int i = 0; i < 10000; ++i )
        ASSERT_EQ( d1.roll(), 1 );

    BasicDie<1337> d1337;
    for( int i = 0; i < 10000; ++i )
        ASSERT_THAT( d1337.roll(), AllOf( Ge( 1 ), Le( 1337 ) ) );
}

/// This test uses Pearson's chi-squared test
TEST( BasicDieTest, RollDistributionShouldBeUniform ) {
    constexpr int maxValue = 251; // 250 degrees of freedom
    constexpr int rolls = 1000000;
    constexpr unsigned int expectedFreq = rolls / maxValue;

    std::array<unsigned int, maxValue + 1> occurences;
    occurences.fill( 0 );

    BasicDie<maxValue> die;
    for( int i = 0; i < rolls; ++i )
        ++occurences.at( die.roll() );

    long double X2 = 0;
    for( int i = 1; i <= maxValue; ++i ) {
        const int numeratorRoot = occurences[i] - expectedFreq;
        X2 += static_cast<long double>( numeratorRoot * numeratorRoot ) / expectedFreq;
    }

    // We assert that the probability of observing a test statistic at least
    // as extreme in a chi-squared distribution is statistically
    // non-significant (p > 0.05).
    ASSERT_LT( X2, 311.346 );
}

TEST( BasicDieTest, RollShouldRollDieSpecificNumberOfTimes ) {
    BasicDie<1> d1;
    for( int i = 0; i < 1000; ++i )
        ASSERT_EQ( d1.roll( 1337 ), 1337 );

    BasicDie<1337> d1337;
    for( int i = 0; i < 1000; ++i )
        ASSERT_THAT( d1337.roll( 1000 ), AllOf( Ge( 1000 ), Le( 1337000 ) ) );
}
