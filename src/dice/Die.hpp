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

        template<typename T>
        friend struct std::hash;
        friend auto operator==( const Die&, const Die& ) -> bool;
    };
}

namespace std {
    template<>
    struct hash<dice::Die*> {
        auto operator()( const dice::Die *die ) const -> std::size_t {
            return die->hash();
        }
    };
}

#endif // SRD_DICE_DIE_HPP
