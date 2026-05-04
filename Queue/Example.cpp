#include <iostream>
#include "SLLBasedQueue/SLLBasedQueue.h"
#include "ArrayBasedQueue/ArrayBasedQueue.h"
//#include "PriorityQueue.h"

void check(IQueue<int>* queue);

int main() {
    IQueue<int>* queue;
    queue = new ArrayBasedQueue<int>(10);
    check(queue);
    delete queue;
    queue = new SLLBasedQueue<int>();
    check(queue);
    delete queue;
    //queue = new PriorityQueue<int>(100);
    //check(queue);
    //delete queue;
    return 0;
}
void check(IQueue<int>* queue) {
    // Enqueue elements
    queue->enqueue(10);
    queue->enqueue(20);
    queue->enqueue(30);
    queue->enqueue(40);

    // Display the queue
    std::cout << "Queue elements: ";
    queue->display();

    // Front and rear elements
    std::cout << "Front element: " << queue->front() << std::endl;
    std::cout << "Rear element: " << queue->rear() << std::endl;

    // Dequeue an element
    std::cout << "Dequeue element: " << queue->dequeue() << std::endl;

    // Display the queue after dequeue
    std::cout << "Queue elements after dequeue: ";
    queue->display();

    // Check if queue is empty
    std::cout << "Is queue empty? " << (queue->is_empty() ? "Yes" : "No") << std::endl;

    // Queue size
    std::cout << "Queue size: " << queue->size() << std::endl;
    std::cout << "---------------------------------\n";
}
