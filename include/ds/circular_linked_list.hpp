/**
 * @file circular_linked_list.hpp
 * @brief Singly linked list whose tail loops back to the head.
 */
#ifndef DS_CIRCULAR_LINKED_LIST_HPP
#define DS_CIRCULAR_LINKED_LIST_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace ds {

/**
 * @brief Singly linked circular list.
 *
 * Stores only a pointer to the @c tail; @c tail->next is the @c head, which
 * gives O(1) push at both ends.
 *
 * @tparam T element type.
 */
template <typename T>
class CircularLinkedList {
public:
    CircularLinkedList() = default;
    ~CircularLinkedList() { clear(); }

    CircularLinkedList(const CircularLinkedList&) = delete;
    CircularLinkedList& operator=(const CircularLinkedList&) = delete;

    CircularLinkedList(CircularLinkedList&& other) noexcept
        : tail_(other.tail_), size_(other.size_) {
        other.tail_ = nullptr;
        other.size_ = 0;
    }

    CircularLinkedList& operator=(CircularLinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            tail_ = other.tail_;
            size_ = other.size_;
            other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    /// Insert at the head. O(1).
    void push_front(T value) {
        Node* node = new Node{std::move(value), nullptr};
        if (!tail_) {
            tail_ = node;
            node->next = node;
        } else {
            node->next = tail_->next;
            tail_->next = node;
        }
        ++size_;
    }

    /// Insert at the tail. O(1).
    void push_back(T value) {
        push_front(std::move(value));
        tail_ = tail_->next;  // rotate so the new node becomes tail
    }

    /// Remove and return the head value. Throws if empty.
    T pop_front() {
        if (!tail_) throw std::out_of_range("pop_front on empty list");
        Node* head = tail_->next;
        T value = std::move(head->data);
        if (head == tail_) {
            tail_ = nullptr;
        } else {
            tail_->next = head->next;
        }
        delete head;
        --size_;
        return value;
    }

    /// Insert before position @p index. O(n).
    void insert(std::size_t index, T value) {
        if (index > size_) throw std::out_of_range("insert: index out of range");
        if (index == 0) { push_front(std::move(value)); return; }
        if (index == size_) { push_back(std::move(value)); return; }
        Node* prev = tail_->next;
        for (std::size_t i = 1; i < index; ++i) prev = prev->next;
        prev->next = new Node{std::move(value), prev->next};
        ++size_;
    }

    /// Remove element at @p index, returning its value. O(n).
    T remove_at(std::size_t index) {
        if (index >= size_) throw std::out_of_range("remove_at: index out of range");
        if (index == 0) return pop_front();
        Node* prev = tail_->next;
        for (std::size_t i = 1; i < index; ++i) prev = prev->next;
        Node* victim = prev->next;
        T value = std::move(victim->data);
        prev->next = victim->next;
        if (victim == tail_) tail_ = prev;
        delete victim;
        --size_;
        return value;
    }

    T& at(std::size_t index) {
        if (index >= size_) throw std::out_of_range("at: index out of range");
        Node* curr = tail_->next;
        for (std::size_t i = 0; i < index; ++i) curr = curr->next;
        return curr->data;
    }

    const T& at(std::size_t index) const {
        if (index >= size_) throw std::out_of_range("at: index out of range");
        Node* curr = tail_->next;
        for (std::size_t i = 0; i < index; ++i) curr = curr->next;
        return curr->data;
    }

    std::size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }

    template <typename Fn>
    void for_each(Fn fn) const {
        if (!tail_) return;
        Node* curr = tail_->next;
        do {
            fn(curr->data);
            curr = curr->next;
        } while (curr != tail_->next);
    }

private:
    struct Node {
        T data;
        Node* next;
    };

    void clear() {
        if (!tail_) return;
        Node* curr = tail_->next;
        tail_->next = nullptr;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
        tail_ = nullptr;
        size_ = 0;
    }

    Node* tail_ = nullptr;
    std::size_t size_ = 0;
};

}  // namespace ds

#endif  // DS_CIRCULAR_LINKED_LIST_HPP
