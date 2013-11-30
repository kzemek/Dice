#ifndef SRD_DICE_BASICDIE_HPP
#define SRD_DICE_BASICDIE_HPP

#include "Die.hpp"

#include "Dice.hpp"
#include "utility/make_unique.hpp"

#include <memory>
#include <random>

namespace dice {
    template<unsigned int sides, typename RandomEngine = std::mt19937>
    class BasicDie: public Die {
    public:
        auto roll( const unsigned int times = 1 ) -> result_type override {
            static thread_local
                RandomEngine generator{ std::random_device{}() };
            static thread_local
                std::uniform_int_distribution<result_type> distribution{ 1, sides };

            result_type result = 0;
            for( int attempt = 0; attempt < times; ++attempt )
                result += distribution( generator );
            return result;
        }

        auto clone() const -> std::unique_ptr<Die> override {
            return utility::make_unique<BasicDie>( *this );
        }

    private:
        auto hash() const -> std::size_t override {
            return sides;
        }
    };

    namespace basic {
        extern BasicDie<4> d4;
        extern BasicDie<6> d6;
        extern BasicDie<8> d8;
        extern BasicDie<10> d10;
        extern BasicDie<12> d12;
        extern BasicDie<20> d20;
        extern BasicDie<100> d100;
    }
}

#endif // SRD_DICE_BASICDIE_HPP
