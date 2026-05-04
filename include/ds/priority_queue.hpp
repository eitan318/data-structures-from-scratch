/**
 * @file priority_queue.hpp
 * @brief Priority queue built on top of @ref ds::BinaryHeap.
 */
#ifndef DS_PRIORITY_QUEUE_HPP
#define DS_PRIORITY_QUEUE_HPP

#include <functional>
#include <utility>

#include "binary_heap.hpp"

namespace ds {

/**
 * @brief Max-priority queue: highest priority element comes out first.
 *
 * A thin convenience wrapper over @ref BinaryHeap with @c std::greater so
 * that @ref top yields the maximum. Customise the ordering by supplying a
 * different @p Compare.
 *
 * @tparam T       element type.
 * @tparam Compare ordering used by the underlying heap (default @c std::greater).
 */
template <typename T, typename Compare = std::greater<T>>
class PriorityQueue {
public:
    PriorityQueue() = default;
    explicit PriorityQueue(Compare compare) : heap_(std::move(compare)) {}

    /// Add @p value to the queue. O(log n).
    void enqueue(T value) { heap_.push(std::move(value)); }

    /// Remove and return the highest-priority element. O(log n).
    T dequeue() { return heap_.pop(); }

    /// Peek at the highest-priority element.
    const T& top() const { return heap_.top(); }

    std::size_t size() const noexcept { return heap_.size(); }
    bool empty() const noexcept { return heap_.empty(); }

private:
    BinaryHeap<T, Compare> heap_;
};

}  // namespace ds

#endif  // DS_PRIORITY_QUEUE_HPP
