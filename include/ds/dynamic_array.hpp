/**
 * @file dynamic_array.hpp
 * @brief Resizable array (vector-like) with amortised O(1) push_back.
 */
#ifndef DS_DYNAMIC_ARRAY_HPP
#define DS_DYNAMIC_ARRAY_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace ds {

/**
 * @brief Dynamic, resizable array.
 *
 * Doubles its capacity when full and halves it when usage drops below 1/4
 * (to keep amortised O(1) push_back without thrashing on remove patterns).
 *
 * @tparam T element type (must be default-constructible and comparable
 *           with @c == for @ref index_of and @ref remove).
 */
template <typename T>
class DynamicArray {
public:
    /// Construct with the given initial capacity (>= 1).
    explicit DynamicArray(std::size_t initial_capacity = 8)
        : capacity_(initial_capacity == 0 ? 1 : initial_capacity),
          size_(0),
          data_(new T[capacity_ == 0 ? 1 : capacity_]) {}

    ~DynamicArray() { delete[] data_; }

    DynamicArray(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;

    DynamicArray(DynamicArray&& other) noexcept
        : capacity_(other.capacity_), size_(other.size_), data_(other.data_) {
        other.capacity_ = 0;
        other.size_ = 0;
        other.data_ = nullptr;
    }

    DynamicArray& operator=(DynamicArray&& other) noexcept {
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

    /// Append @p value to the end. Amortised O(1).
    void push_back(T value) {
        if (size_ == capacity_) reserve(capacity_ * 2);
        data_[size_++] = std::move(value);
    }

    /// Insert @p value at @p index, shifting later elements right. O(n).
    void insert(std::size_t index, T value) {
        if (index > size_) throw std::out_of_range("insert: index out of range");
        if (size_ == capacity_) reserve(capacity_ * 2);
        for (std::size_t i = size_; i > index; --i) {
            data_[i] = std::move(data_[i - 1]);
        }
        data_[index] = std::move(value);
        ++size_;
    }

    /// Remove the element at @p index, shifting later elements left. O(n).
    void remove_at(std::size_t index) {
        if (index >= size_) throw std::out_of_range("remove_at: index out of range");
        for (std::size_t i = index; i + 1 < size_; ++i) {
            data_[i] = std::move(data_[i + 1]);
        }
        --size_;
        if (capacity_ > 1 && size_ * 4 <= capacity_) reserve(capacity_ / 2);
    }

    /// Remove the first element equal to @p value. Returns true if removed.
    bool remove(const T& value) {
        std::size_t i = index_of(value);
        if (i == npos) return false;
        remove_at(i);
        return true;
    }

    /// Return the index of the first element equal to @p value, or @ref npos.
    std::size_t index_of(const T& value) const {
        for (std::size_t i = 0; i < size_; ++i) {
            if (data_[i] == value) return i;
        }
        return npos;
    }

    T& operator[](std::size_t index) {
        if (index >= size_) throw std::out_of_range("index out of range");
        return data_[index];
    }

    const T& operator[](std::size_t index) const {
        if (index >= size_) throw std::out_of_range("index out of range");
        return data_[index];
    }

    std::size_t size() const noexcept { return size_; }
    std::size_t capacity() const noexcept { return capacity_; }
    bool empty() const noexcept { return size_ == 0; }

    /// Sentinel returned by @ref index_of when no match is found.
    static constexpr std::size_t npos = static_cast<std::size_t>(-1);

private:
    void reserve(std::size_t new_capacity) {
        if (new_capacity < 1) new_capacity = 1;
        T* new_data = new T[new_capacity];
        for (std::size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    std::size_t capacity_;
    std::size_t size_;
    T* data_;
};

}  // namespace ds

#endif  // DS_DYNAMIC_ARRAY_HPP
