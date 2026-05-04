#include <iostream>

#include "ds/dynamic_array.hpp"

int main() {
    ds::DynamicArray<int> v;
    for (int i = 1; i <= 5; ++i) v.push_back(i * 10);

    v.insert(2, 99);
    v.remove(40);

    std::cout << "size=" << v.size() << " cap=" << v.capacity() << " : ";
    for (std::size_t i = 0; i < v.size(); ++i) std::cout << v[i] << ' ';
    std::cout << '\n';

    std::cout << "index_of(99) = " << v.index_of(99) << '\n';
}
