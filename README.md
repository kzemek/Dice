# Dice
Dice library is a small, high-performant, **thread-safe**, idiomatic and unit-tested implementation of gaming dice written in C++11.

## Compilation and installation
The following commands will compile the library and install it to /usr/local/lib directory, with headers in /usr/local/include direcory.
```bash
mkdir build
cd build/
cmake ..
make
```

By default, dice will be built as a static library. Add ```-Ddice_SHARED=ON``` to ```cmake ..``` to build it as a shared library instead.

The built library will be located in ```build/src/dice```. To use the library, you may also want to add src/ to your include path. The structure is made up this way because dice were meant to be a part of a bigger project, not a standalone library; it may be changed in the future.

## Usage
The basic class of the library is Dice. Dice is a collection of Die objects. In most cases, you don't need to concern yourself about Die objects - they are implicitly converted to Dice collection.

You can import all needed declarations by including ```dice/include.hpp```


The namespace dice::basic contains Die objects representing standard dice. Out of the box you can use any of the following die types: d4, d6, d8, d10, d12, d20 and d100 (also known as d% or dp).
```cpp
using namespace dice::basic;
using dice::Dice;

d20.roll();         // d20 is of type Die
Dice dice = d20;    // but is implicitly converted to Dice
dice.roll();
```

### Construction
You can use Dice constructor, which takes a Die and an amount.
```cpp
using namespace dice::basic;
using dice::Dice;

Dice d{ d4, 2 };    // create dice collection consisting of two four-sided dice
d.roll();
```

Usually though, you'll want to use the more idiomatic approach.
```cpp
using namespace dice::basic;
using dice::Dice;

auto d = 2*d4;      // create dice collection consisting of two four-sided dice
d.roll();
```

### Addition
You can add a modifier to all of the collection's rolls.
```cpp
using namespace dice::basic;
using dice::Dice;

auto d = 2*d12 + 4;
d.roll();           // returns a number between 6 (2*1 + 4) and 28 (2*12 + 4)

d = d - 8;
d.roll();           // returns a number between -2 (2*1 - 4) and 20 (2*12 - 4)
```

You can also add dice collections. It works for Die objects as well (the Dice.hpp header has to be included).
```cpp
using namespace dice::basic;
using dice::Dice;

auto d = d6 + d4;
d = d + 2 * d12;
d = d + 2*d6;       // d = 3*d6 + d4 + 2*d12
d.roll();
```

## Customization
### Creating custom-sided die type
```cpp
using dice::BasicDie;
using dice::Dice;

BasicDie<13> d13;
d13.roll();

auto d = 3*d13;
d.roll();
```

### Changing the random number generator
BasicDie is a Die implementation that uses std::mt19937 generator by default. You can easily create a die type using a different generator.
```cpp
using dice::BasicDie;

BasicDie<4, std::knuth_b> d4;
d4.roll();
```

### Using custom Die implementation
```cpp
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
```
