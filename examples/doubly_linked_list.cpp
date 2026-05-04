#include <iostream>

#include "ds/doubly_linked_list.hpp"

int main() {
    ds::DoublyLinkedList<int> list;
    for (int i = 1; i <= 5; ++i) list.push_back(i);
    list.push_front(0);

    list.insert(3, 99);
    list.remove_at(0);

    std::cout << "list: ";
    list.for_each([](int x) { std::cout << x << ' '; });
    std::cout << '\n';

    list.reverse();
    std::cout << "reversed: ";
    list.for_each([](int x) { std::cout << x << ' '; });
    std::cout << '\n';

    std::cout << "pop_back -> " << list.pop_back() << '\n';
    std::cout << "at(0)=" << list.at(0) << " size=" << list.size() << '\n';
}
