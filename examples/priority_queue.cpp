#include <iostream>

#include "ds/priority_queue.hpp"

int main() {
    ds::PriorityQueue<int> pq;  // max-priority by default
    for (int x : {5, 1, 9, 3, 7, 2}) pq.enqueue(x);

    std::cout << "by priority: ";
    while (!pq.empty()) std::cout << pq.dequeue() << ' ';
    std::cout << '\n';
}
