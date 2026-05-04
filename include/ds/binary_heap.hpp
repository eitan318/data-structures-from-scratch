/**
 * @file binary_heap.hpp
 * @brief Array-backed binary heap (min-heap by default).
 */
#ifndef DS_BINARY_HEAP_HPP
#define DS_BINARY_HEAP_HPP

#include <cstddef>
#include <functional>
#include <stdexcept>
#include <utility>
#include <vector>

namespace ds {

/**
 * @brief Generic binary heap stored in an implicit array.
 *
 * The default @p Compare is @c std::less, producing a min-heap. Pass
 * @c std::greater to obtain a max-heap.
 *
 * @tparam T       element type.
 * @tparam Compare strict weak ordering; @c Compare(a, b) is true when
 *                 @c a should bubble up above @c b.
 */
template <typename T, typename Compare = std::less<T>>
class BinaryHeap {
public:
    BinaryHeap() = default;
    explicit BinaryHeap(Compare compare) : cmp_(std::move(compare)) {}

    /// Insert @p value into the heap. O(log n).
    void push(T value) {
        data_.push_back(std::move(value));
        sift_up(data_.size() - 1);
    }

    /// Remove and return the top element (smallest under the comparator). O(log n).
    T pop() {
        if (data_.empty()) throw std::out_of_range("pop on empty heap");
        T result = std::move(data_.front());
        data_.front() = std::move(data_.back());
        data_.pop_back();
        if (!data_.empty()) sift_down(0);
        return result;
    }

    /// Peek at the top element without removing it.
    const T& top() const {
        if (data_.empty()) throw std::out_of_range("top on empty heap");
        return data_.front();
    }

    std::size_t size() const noexcept { return data_.size(); }
    bool empty() const noexcept { return data_.empty(); }

private:
    static std::size_t parent(std::size_t i) { return (i - 1) / 2; }
    static std::size_t left(std::size_t i)   { return 2 * i + 1; }
    static std::size_t right(std::size_t i)  { return 2 * i + 2; }

    void sift_up(std::size_t i) {
        while (i > 0 && cmp_(data_[i], data_[parent(i)])) {
            std::swap(data_[i], data_[parent(i)]);
            i = parent(i);
        }
    }

    void sift_down(std::size_t i) {
        const std::size_t n = data_.size();
        while (true) {
            std::size_t best = i;
            if (left(i) < n && cmp_(data_[left(i)], data_[best])) best = left(i);
            if (right(i) < n && cmp_(data_[right(i)], data_[best])) best = right(i);
            if (best == i) return;
            std::swap(data_[i], data_[best]);
            i = best;
        }
    }

    std::vector<T> data_;
    Compare cmp_{};
};

}  // namespace ds

#endif  // DS_BINARY_HEAP_HPP
