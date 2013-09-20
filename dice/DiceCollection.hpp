#ifndef SRD_DICE_DICECOLLECTION_HPP
#define SRD_DICE_DICECOLLECTION_HPP

#include "Dice.hpp"

#include <functional>
#include <unordered_map>
#include <utility>

namespace dice {

template<unsigned int sides, typename RandomGenerator>
class Die;

class DiceCollection: public Dice {
public:
	auto roll() const -> result_type override {
		result_type result = 0;

		for( auto &diceElem: m_storedDice ) {
			auto amount = diceElem.second.first;
			auto &roll = diceElem.second.second;

			while( amount --> 0 )
				result += roll();
		}

		return result + m_bonus;
	}

private:
	DiceCollection() = default;

	int m_bonus = 0;

	std::unordered_map<unsigned int /*sides*/,
	                   std::pair<unsigned int /*amount*/, std::function<result_type()>>
	                   > m_storedDice;

    template<unsigned int sides, typename RandomGenerator>
    friend auto operator*( const unsigned int,
    	                   const Die<sides, RandomGenerator>& ) -> DiceCollection;

	friend auto operator+( const DiceCollection&, const int ) -> DiceCollection;

    friend auto operator+( const DiceCollection&,
    	                   const DiceCollection& ) -> DiceCollection;
};

template<unsigned int sides, typename RandomGenerator>
auto operator*( const unsigned int amount,
	            const Die<sides, RandomGenerator>&d ) -> DiceCollection {

	DiceCollection collection;
	collection.m_storedDice.emplace(
		sides, std::make_pair( amount,
			                   std::bind( &Die<sides, RandomGenerator>::roll, &d ) ) );

	return std::move( collection );
}

auto operator+( const DiceCollection &d, const int bonus ) -> DiceCollection {
	DiceCollection collection{ d };
	collection.m_bonus += bonus;
	return std::move( collection );
}

auto operator+( const DiceCollection &lhs,
		        const DiceCollection &rhs ) -> DiceCollection {

	DiceCollection collection{ lhs };

	{
		auto &store = collection.m_storedDice;
		for( auto &entry: rhs.m_storedDice ) {
			if( store.count( entry.first ) )
				store[entry.first].first += entry.second.first;
			else
				store.emplace( entry.first, entry.second );
		}
	}

	collection.m_bonus += rhs.m_bonus;
	return std::move( collection );
}

}

#endif // SRD_DICE_DICECOLLECTION_HPP