#include <iostream>

#include "ds/binary_tree.hpp"

int main() {
    ds::BinaryTree<int> tree;
    for (int x : {1, 2, 3, 4, 5, 6, 7}) tree.insert(x);

    std::cout << "level-order: ";
    tree.level_order([](int x) { std::cout << x << ' '; });
    std::cout << '\n';

    std::cout << "in-order:    ";
    tree.in_order([](int x) { std::cout << x << ' '; });
    std::cout << '\n';

    std::cout << "height=" << tree.height() << " size=" << tree.size() << '\n';
}
