#include <iostream>

#include "ds/queue.hpp"

int main() {
    ds::Queue<int> q;
    for (int i = 1; i <= 5; ++i) q.enqueue(i);

    std::cout << "front=" << q.front() << " back=" << q.back() << '\n';
    std::cout << "dequeue order: ";
    while (!q.empty()) std::cout << q.dequeue() << ' ';
    std::cout << '\n';
}
