#include <iostream>

#include "ds/binary_search_tree.hpp"

int main() {
    ds::BinarySearchTree<int> bst;
    for (int x : {5, 2, 8, 1, 3, 7, 9}) bst.insert(x);

    std::cout << "sorted: ";
    bst.in_order([](int x) { std::cout << x << ' '; });
    std::cout << '\n';

    std::cout << "min=" << bst.min() << " max=" << bst.max() << '\n';
    std::cout << "contains(7)=" << bst.contains(7)
              << " contains(4)=" << bst.contains(4) << '\n';

    bst.remove(5);
    std::cout << "after remove(5): ";
    bst.in_order([](int x) { std::cout << x << ' '; });
    std::cout << '\n';
}
