#include <iostream>

#include "ds/stack.hpp"

int main() {
    ds::Stack<int> s;
    for (int i = 1; i <= 5; ++i) s.push(i);

    std::cout << "top=" << s.top() << " size=" << s.size() << '\n';
    std::cout << "pop order: ";
    while (!s.empty()) std::cout << s.pop() << ' ';
    std::cout << '\n';
}
