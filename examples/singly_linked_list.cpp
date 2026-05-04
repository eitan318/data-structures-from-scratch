#include <iostream>

#include "ds/singly_linked_list.hpp"

int main() {
    ds::SinglyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(0);
    list.insert(2, 99);

    std::cout << "list: ";
    list.for_each([](int x) { std::cout << x << ' '; });
    std::cout << '\n';

    list.reverse();
    std::cout << "reversed: ";
    list.for_each([](int x) { std::cout << x << ' '; });
    std::cout << '\n';

    std::cout << "pop_front -> " << list.pop_front() << '\n';
    std::cout << "size=" << list.size() << '\n';
}
