#ifndef SRD_DICE_DIE_HPP
#define SRD_DICE_DIE_HPP

#include <random>

namespace dice {

template<unsigned int sides, typename RandomEngine = std::mt19937>
class Die {
public:
    using result_type = unsigned int;

    static auto roll() -> result_type {
        static thread_local RandomEngine generator{ std::random_device{}() };
        static thread_local std::uniform_int_distribution<result_type>
                            distribution{ 1, sides };

        return distribution( generator );
    }
};

}

#endif // SRD_DICE_DIE_HPP
