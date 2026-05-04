#ifndef SLLBASEDQUEUE_H
#define SLLBASEDQUEUE_H

#include "../../LinkedList-/SinglyLinkedList/SinglyLinkedList.h"
#include "../IQueue.h"

template <typename T>
class SLLBasedQueue : public IQueue<T> {
private:
    SinglyLinkedList<T>* list;  // Pointer to the singly linked list

public:
    SLLBasedQueue();   // Constructor
    ~SLLBasedQueue();  // Destructor

    void enqueue(T data) override;
    T dequeue() override;
    void display() override;
    T front() override;
    T rear() override;
    bool is_empty() override;
    int size() override;
};

#endif // QUEUESLL_H

// Implementation

template <typename T>
SLLBasedQueue<T>::SLLBasedQueue() {
    this->list = new SinglyLinkedList<T>();
}

template <typename T>
SLLBasedQueue<T>::~SLLBasedQueue() {
    delete this->list;
}

template <typename T>
void SLLBasedQueue<T>::enqueue(T data) {
    this->list->add_end(data);  // Add element to the end of the queue
}

template <typename T>
T SLLBasedQueue<T>::dequeue() {
    if (this->is_empty()) {
        throw std::out_of_range("Queue is empty");
    }
    T frontData = this->list->get(0);  // Get the front element
    this->list->remove_at(0);          // Remove the front element
    return frontData;
}

template <typename T>
T SLLBasedQueue<T>::front() {
    if (this->is_empty()) {
        throw std::out_of_range("Queue is empty");
    }
    return this->list->get(0);  // Return the front element
}

template <typename T>
T SLLBasedQueue<T>::rear() {
    if (this->is_empty()) {
        throw std::out_of_range("Queue is empty");
    }
    return this->list->get_last();  // Return the rear element
}

template <typename T>
bool SLLBasedQueue<T>::is_empty() {
    return this->list->Count() == 0;  // Check if the queue is empty
}

template <typename T>
int SLLBasedQueue<T>::size() {
    return this->list->Count();  // Return the size of the queue
}

template <typename T>
void SLLBasedQueue<T>::display() {
    this->list->print();  // Display the elements in the queue
}
