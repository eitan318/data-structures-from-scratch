/**
 * @file queue.hpp
 * @brief FIFO queue backed by a circular buffer.
 */
#ifndef DS_QUEUE_HPP
#define DS_QUEUE_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace ds {

/**
 * @brief First-In-First-Out queue using a ring buffer.
 *
 * Stores @c front and @c rear indices that wrap around the underlying array.
 * The buffer doubles when full, giving amortised O(1) @ref enqueue and
 * worst-case O(1) @ref dequeue.
 *
 * @tparam T element type.
 */
template <typename T>
class Queue {
public:
    explicit Queue(std::size_t initial_capacity = 8)
        : capacity_(initial_capacity == 0 ? 1 : initial_capacity),
          size_(0),
          front_(0),
          data_(new T[capacity_]) {}

    ~Queue() { delete[] data_; }

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    Queue(Queue&& other) noexcept
        : capacity_(other.capacity_),
          size_(other.size_),
          front_(other.front_),
          data_(other.data_) {
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.data_ = nullptr;
    }

    Queue& operator=(Queue&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            front_ = other.front_;
            data_ = other.data_;
            other.capacity_ = 0;
            other.size_ = 0;
            other.front_ = 0;
            other.data_ = nullptr;
        }
        return *this;
    }

    /// Add @p value at the back. Amortised O(1).
    void enqueue(T value) {
        if (size_ == capacity_) grow();
        data_[(front_ + size_) % capacity_] = std::move(value);
        ++size_;
    }

    /// Remove and return the front value. Throws if empty.
    T dequeue() {
        if (size_ == 0) throw std::out_of_range("dequeue on empty queue");
        T value = std::move(data_[front_]);
        front_ = (front_ + 1) % capacity_;
        --size_;
        return value;
    }

    T& front() {
        if (size_ == 0) throw std::out_of_range("front on empty queue");
        return data_[front_];
    }

    const T& front() const {
        if (size_ == 0) throw std::out_of_range("front on empty queue");
        return data_[front_];
    }

    T& back() {
        if (size_ == 0) throw std::out_of_range("back on empty queue");
        return data_[(front_ + size_ - 1) % capacity_];
    }

    const T& back() const {
        if (size_ == 0) throw std::out_of_range("back on empty queue");
        return data_[(front_ + size_ - 1) % capacity_];
    }

    std::size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }

private:
    void grow() {
        std::size_t new_capacity = capacity_ * 2;
        T* new_data = new T[new_capacity];
        for (std::size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[(front_ + i) % capacity_]);
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
        front_ = 0;
    }

    std::size_t capacity_;
    std::size_t size_;
    std::size_t front_;
    T* data_;
};

}  // namespace ds

#endif  // DS_QUEUE_HPP
