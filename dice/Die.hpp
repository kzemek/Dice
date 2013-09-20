#ifndef SRD_DICE_DIE_HPP
#define SRD_DICE_DIE_HPP

#include "Dice.hpp"

#include <random>

namespace dice {

template<unsigned int sides, typename RandomEngine = std::mt19937>
class Die: public Dice {
public:
	auto roll() const -> result_type override {
		return distribution( generator );
	}

private:
	static thread_local RandomEngine generator;
	static thread_local std::uniform_int_distribution<result_type> distribution;
};

template<unsigned int sides, typename RandomEngine>
thread_local RandomEngine
	Die<sides, RandomEngine>::generator{ std::random_device{}() };

template<unsigned int sides, typename RandomEngine>
thread_local std::uniform_int_distribution<Dice::result_type>
	Die<sides, RandomEngine>::distribution{ 1, sides };

}

#endif // SRD_DICE_DIE_HPP