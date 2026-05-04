/**
 * @file doubly_circular_linked_list.hpp
 * @brief Doubly linked list whose tail loops back to the head.
 */
#ifndef DS_DOUBLY_CIRCULAR_LINKED_LIST_HPP
#define DS_DOUBLY_CIRCULAR_LINKED_LIST_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace ds {

/**
 * @brief Doubly linked circular list.
 *
 * Each node has @c prev and @c next pointers; @c head->prev is the tail
 * and @c tail->next is the head. Insertion / removal at both ends is O(1).
 *
 * @tparam T element type.
 */
template <typename T>
class DoublyCircularLinkedList {
public:
    DoublyCircularLinkedList() = default;
    ~DoublyCircularLinkedList() { clear(); }

    DoublyCircularLinkedList(const DoublyCircularLinkedList&) = delete;
    DoublyCircularLinkedList& operator=(const DoublyCircularLinkedList&) = delete;

    DoublyCircularLinkedList(DoublyCircularLinkedList&& other) noexcept
        : head_(other.head_), size_(other.size_) {
        other.head_ = nullptr;
        other.size_ = 0;
    }

    DoublyCircularLinkedList& operator=(DoublyCircularLinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = other.head_;
            size_ = other.size_;
            other.head_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    /// Insert at the head. O(1).
    void push_front(T value) {
        Node* node = new Node{std::move(value), nullptr, nullptr};
        if (!head_) {
            node->prev = node->next = node;
        } else {
            Node* tail = head_->prev;
            node->next = head_;
            node->prev = tail;
            tail->next = node;
            head_->prev = node;
        }
        head_ = node;
        ++size_;
    }

    /// Insert at the tail. O(1).
    void push_back(T value) {
        push_front(std::move(value));
        head_ = head_->next;  // rotate: new node becomes tail
    }

    /// Remove and return the head value. Throws if empty.
    T pop_front() {
        if (!head_) throw std::out_of_range("pop_front on empty list");
        Node* old = head_;
        T value = std::move(old->data);
        if (size_ == 1) {
            head_ = nullptr;
        } else {
            Node* tail = head_->prev;
            head_ = head_->next;
            head_->prev = tail;
            tail->next = head_;
        }
        delete old;
        --size_;
        return value;
    }

    /// Remove and return the tail value. Throws if empty.
    T pop_back() {
        if (!head_) throw std::out_of_range("pop_back on empty list");
        Node* tail = head_->prev;
        T value = std::move(tail->data);
        if (size_ == 1) {
            head_ = nullptr;
        } else {
            tail->prev->next = head_;
            head_->prev = tail->prev;
        }
        delete tail;
        --size_;
        return value;
    }

    /// Insert before position @p index. O(n/2).
    void insert(std::size_t index, T value) {
        if (index > size_) throw std::out_of_range("insert: index out of range");
        if (index == 0) { push_front(std::move(value)); return; }
        if (index == size_) { push_back(std::move(value)); return; }
        Node* curr = node_at(index);
        Node* node = new Node{std::move(value), curr->prev, curr};
        curr->prev->next = node;
        curr->prev = node;
        ++size_;
    }

    /// Remove the element at @p index, returning its value. O(n/2).
    T remove_at(std::size_t index) {
        if (index >= size_) throw std::out_of_range("remove_at: index out of range");
        if (index == 0) return pop_front();
        if (index == size_ - 1) return pop_back();
        Node* victim = node_at(index);
        T value = std::move(victim->data);
        victim->prev->next = victim->next;
        victim->next->prev = victim->prev;
        delete victim;
        --size_;
        return value;
    }

    T& at(std::size_t index) {
        if (index >= size_) throw std::out_of_range("at: index out of range");
        return node_at(index)->data;
    }

    const T& at(std::size_t index) const {
        if (index >= size_) throw std::out_of_range("at: index out of range");
        return node_at(index)->data;
    }

    std::size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }

    template <typename Fn>
    void for_each(Fn fn) const {
        if (!head_) return;
        Node* curr = head_;
        do {
            fn(curr->data);
            curr = curr->next;
        } while (curr != head_);
    }

private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
    };

    Node* node_at(std::size_t index) const {
        if (index < size_ / 2) {
            Node* curr = head_;
            for (std::size_t i = 0; i < index; ++i) curr = curr->next;
            return curr;
        }
        Node* curr = head_->prev;  // tail
        for (std::size_t i = size_ - 1; i > index; --i) curr = curr->prev;
        return curr;
    }

    void clear() {
        if (!head_) return;
        Node* curr = head_;
        head_->prev->next = nullptr;  // break the cycle
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
        head_ = nullptr;
        size_ = 0;
    }

    Node* head_ = nullptr;
    std::size_t size_ = 0;
};

}  // namespace ds

#endif  // DS_DOUBLY_CIRCULAR_LINKED_LIST_HPP
