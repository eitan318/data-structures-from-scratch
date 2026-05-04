#include <iostream>

#include "ds/bit_array.hpp"

int main() {
    ds::BitArray bits(16);
    for (std::size_t i = 0; i < bits.size(); i += 2) bits.set(i);
    bits.flip(1);

    std::cout << "bits: ";
    for (std::size_t i = 0; i < bits.size(); ++i) std::cout << bits.get(i);
    std::cout << '\n';
}
