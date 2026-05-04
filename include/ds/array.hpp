/**
 * @file array.hpp
 * @brief Fixed-size, bounds-checked array.
 */
#ifndef DS_ARRAY_HPP
#define DS_ARRAY_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace ds {

/**
 * @brief Fixed-capacity contiguous container with bounds checking.
 *
 * Wraps a heap-allocated buffer of @p T with `operator[]` that throws
 * @c std::out_of_range on invalid indices. Capacity is fixed at construction.
 *
 * @tparam T element type (must be default-constructible)
 */
template <typename T>
class Array {
public:
    /// Construct an array of @p capacity default-initialised elements.
    explicit Array(std::size_t capacity)
        : capacity_(capacity), data_(new T[capacity]()) {
        if (capacity == 0) {
            throw std::invalid_argument("Array capacity must be positive");
        }
    }

    ~Array() { delete[] data_; }

    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;

    Array(Array&& other) noexcept
        : capacity_(other.capacity_), data_(other.data_) {
        other.capacity_ = 0;
        other.data_ = nullptr;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            capacity_ = other.capacity_;
            data_ = other.data_;
            other.capacity_ = 0;
            other.data_ = nullptr;
        }
        return *this;
    }

    /// Mutable element access. Throws @c std::out_of_range on invalid index.
    T& operator[](std::size_t index) {
        check(index);
        return data_[index];
    }

    /// Const element access. Throws @c std::out_of_range on invalid index.
    const T& operator[](std::size_t index) const {
        check(index);
        return data_[index];
    }

    /// Number of elements held by the array.
    std::size_t size() const noexcept { return capacity_; }

private:
    void check(std::size_t index) const {
        if (index >= capacity_) {
            throw std::out_of_range("Array index out of bounds");
        }
    }

    std::size_t capacity_;
    T* data_;
};

}  // namespace ds

#endif  // DS_ARRAY_HPP
