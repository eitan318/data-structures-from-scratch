#include <iostream>

#include "ds/binary_heap.hpp"

int main() {
    ds::BinaryHeap<int> heap;  // min-heap by default
    for (int x : {5, 1, 9, 3, 7, 2}) heap.push(x);

    std::cout << "ascending: ";
    while (!heap.empty()) std::cout << heap.pop() << ' ';
    std::cout << '\n';
}
