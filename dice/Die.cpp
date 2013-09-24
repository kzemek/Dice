#include "Die.hpp"

namespace dice {
    auto operator==( const Die &lhs, const Die &rhs ) -> bool {
        return lhs.hash() == rhs.hash();
    }
}
