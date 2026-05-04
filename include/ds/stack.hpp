/**
 * @file stack.hpp
 * @brief LIFO container backed by a growable array.
 */
#ifndef DS_STACK_HPP
#define DS_STACK_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace ds {

/**
 * @brief Last-In-First-Out container.
 *
 * Backed by a contiguous buffer that doubles when full, so all operations
 * are amortised O(1).
 *
 * @tparam T element type.
 */
template <typename T>
class Stack {
public:
    explicit Stack(std::size_t initial_capacity = 8)
        : capacity_(initial_capacity == 0 ? 1 : initial_capacity),
          size_(0),
          data_(new T[capacity_]) {}

    ~Stack() { delete[] data_; }

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    Stack(Stack&& other) noexcept
        : capacity_(other.capacity_), size_(other.size_), data_(other.data_) {
        other.capacity_ = 0;
        other.size_ = 0;
        other.data_ = nullptr;
    }

    Stack& operator=(Stack&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            data_ = other.data_;
            other.capacity_ = 0;
            other.size_ = 0;
            other.data_ = nullptr;
        }
        return *this;
    }

    /// Push @p value on top. Amortised O(1).
    void push(T value) {
        if (size_ == capacity_) reserve(capacity_ * 2);
        data_[size_++] = std::move(value);
    }

    /// Pop and return the top element. Throws if empty.
    T pop() {
        if (size_ == 0) throw std::out_of_range("pop on empty stack");
        return std::move(data_[--size_]);
    }

    /// Peek the top element without removing it.
    T& top() {
        if (size_ == 0) throw std::out_of_range("top on empty stack");
        return data_[size_ - 1];
    }

    const T& top() const {
        if (size_ == 0) throw std::out_of_range("top on empty stack");
        return data_[size_ - 1];
    }

    std::size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }

private:
    void reserve(std::size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (std::size_t i = 0; i < size_; ++i) new_data[i] = std::move(data_[i]);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    std::size_t capacity_;
    std::size_t size_;
    T* data_;
};

}  // namespace ds

#endif  // DS_STACK_HPP
