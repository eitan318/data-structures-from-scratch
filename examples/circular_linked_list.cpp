#include <iostream>

#include "ds/circular_linked_list.hpp"

int main() {
    ds::CircularLinkedList<int> list;
    for (int i = 1; i <= 4; ++i) list.push_back(i);
    list.push_front(0);

    std::cout << "list: ";
    list.for_each([](int x) { std::cout << x << ' '; });
    std::cout << '\n';

    list.remove_at(2);
    std::cout << "after remove_at(2): ";
    list.for_each([](int x) { std::cout << x << ' '; });
    std::cout << '\n';
}
