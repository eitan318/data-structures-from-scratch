#ifndef ARRAYBASEDQUEUE_H
#define ARRAYBASEDQUEUE_H

#include "../IQueue.h"
#include <iostream>

template <typename T>
class ArrayBasedQueue : public IQueue<T> {
public:
    ArrayBasedQueue(int capacity);
    ~ArrayBasedQueue();
    
    void enqueue(T data) override;
    T dequeue() override; 
    void display() override;
    T front() override;
    T rear() override;
    bool is_empty() override;
    int size() override;

private:
    T* array;
    int _capacity;  // Maximum capacity of the queue
    int _front;     // Index of the front element
    int _rear;      // Index of the rear element
    int _count;     // Current number of elements in the queue
};

template <typename T>
ArrayBasedQueue<T>::ArrayBasedQueue(int capacity)
    : _capacity(capacity), _front(0), _rear(-1), _count(0)
{
    this->array = new T[_capacity];
}

template <typename T>
ArrayBasedQueue<T>::~ArrayBasedQueue()
{
    delete[] this->array;
}

template<typename T>
void ArrayBasedQueue<T>::enqueue(T data)
{
    if (_count == _capacity) {
        throw std::overflow_error("Queue is full");
    }
    //moving the pointers around instead of all the next values
    _rear = (_rear + 1) % _capacity;
    array[_rear] = data;
    _count++;
}

template<typename T>
T ArrayBasedQueue<T>::dequeue()
{
    if (is_empty()) {
        throw std::underflow_error("Queue is empty");
    }
    T data = array[_front];
    //moving the pointers around instead of all the next values
    _front = (_front + 1) % _capacity;
    _count--;
    return data;
}

template<typename T>
void ArrayBasedQueue<T>::display()
{
    if (is_empty()) {
        std::cout << "Queue is empty" << std::endl;
        return;
    }
    int i = _front;
    for (int j = 0; j < _count; j++) {
        std::cout << array[i] << " ";
        i = (i + 1) % _capacity;
    }
    std::cout << std::endl;
}

template<typename T>
T ArrayBasedQueue<T>::front()
{
    if (is_empty()) {
        throw std::underflow_error("Queue is empty");
    }
    return array[_front];
}

template<typename T>
T ArrayBasedQueue<T>::rear()
{
    if (is_empty()) {
        throw std::underflow_error("Queue is empty");
    }
    return array[_rear];
}

template<typename T>
bool ArrayBasedQueue<T>::is_empty()
{
    return _count == 0;
}

template<typename T>
int ArrayBasedQueue<T>::size()
{
    return _count;
}

#endif // ARRAYBASEDQUEUE_H