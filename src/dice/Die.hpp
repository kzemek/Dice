#ifndef SRD_DICE_DIE_HPP
#define SRD_DICE_DIE_HPP

#include <memory>

namespace dice {
    class Die {
    public:
        using result_type = unsigned int;

        Die() = default;
        virtual ~Die() = default;
        Die( const Die& ) = default;
        Die( Die&& ) = default;
        Die &operator=( const Die& ) & = default;
        Die &operator=( Die&& ) & = default;

        virtual auto roll( const unsigned int times = 1 ) -> result_type = 0;
        virtual auto clone() const -> std::unique_ptr<Die> = 0;

    private:
        virtual auto hash() const -> std::size_t = 0;

        friend struct DieHashHelper;
        friend auto operator==( const Die&, const Die& ) -> bool;
    };

    struct DieHashHelper {
        auto operator()( const std::shared_ptr<Die> die ) const -> std::size_t {
            return die->hash();
        }

        auto operator()( const std::shared_ptr<Die> lhs,
                         const std::shared_ptr<Die> rhs ) const -> bool {

            return *lhs == *rhs;
        }
    };
}


#endif // SRD_DICE_DIE_HPP
