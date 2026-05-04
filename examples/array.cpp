#include <iostream>

#include "ds/array.hpp"

int main() {
    ds::Array<int> a(5);
    for (std::size_t i = 0; i < a.size(); ++i) a[i] = static_cast<int>(i * i);

    std::cout << "array: ";
    for (std::size_t i = 0; i < a.size(); ++i) std::cout << a[i] << ' ';
    std::cout << '\n';

    try {
        (void)a[99];
    } catch (const std::out_of_range& e) {
        std::cout << "caught: " << e.what() << '\n';
    }
}
