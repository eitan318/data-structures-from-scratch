#ifndef IQUEUE_H
#define IQUEUE_H

template <typename T>
class IQueue {
public:
    virtual ~IQueue() = default;  // Virtual destructor

    virtual void enqueue(T data) = 0;  // Pure virtual function for adding an element
    virtual T dequeue() = 0;           // Pure virtual function for removing an element
    virtual void display() = 0;        // Pure virtual function for displaying elements
    virtual T front() = 0;             // Pure virtual function for getting the front element
    virtual T rear() = 0;              // Pure virtual function for getting the rear element
    virtual bool is_empty() = 0;        // Pure virtual function for checking if the queue is empty
    virtual int size() = 0;            // Pure virtual function for getting the size of the queue
};

#endif // IQUEUE_H
