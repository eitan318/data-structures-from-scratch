#include <iostream>

#include "ds/doubly_circular_linked_list.hpp"

int main() {
    ds::DoublyCircularLinkedList<int> list;
    for (int i = 1; i <= 4; ++i) list.push_back(i);
    list.push_front(0);

    std::cout << "list: ";
    list.for_each([](int x) { std::cout << x << ' '; });
    std::cout << '\n';

    list.pop_back();
    list.pop_front();
    std::cout << "after pop_front + pop_back: ";
    list.for_each([](int x) { std::cout << x << ' '; });
    std::cout << '\n';
}
