#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "../IQueue.h"
#include <iostream>

template <typename T>
class PriorityQueue : public IQueue<T> {
public:
    PriorityQueue(int capacity);
    ~PriorityQueue();
    
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
PriorityQueue<T>::PriorityQueue(int capacity)
{
}

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{

}

template<typename T>
void PriorityQueue<T>::enqueue(T data)
{

}

template<typename T>
T PriorityQueue<T>::dequeue()
{

}

template<typename T>
void PriorityQueue<T>::display()
{

}

template<typename T>
T PriorityQueue<T>::front()
{

}

template<typename T>
T PriorityQueue<T>::rear()
{

}

template<typename T>
bool PriorityQueue<T>::is_empty()
{
}

template<typename T>
int PriorityQueue<T>::size()
{
}

#endif // PRIORITYQUEUE_H