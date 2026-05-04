/**
 * @file singly_linked_list.hpp
 * @brief Singly linked list with head/tail pointers.
 */
#ifndef DS_SINGLY_LINKED_LIST_HPP
#define DS_SINGLY_LINKED_LIST_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace ds {

/**
 * @brief Singly linked list with O(1) push at head and tail.
 *
 * Maintains @c head and @c tail pointers and a size counter so that
 * @ref push_front, @ref push_back and @ref size are all O(1).
 *
 * @tparam T element type.
 */
template <typename T>
class SinglyLinkedList {
public:
    SinglyLinkedList() = default;
    ~SinglyLinkedList() { clear(); }

    SinglyLinkedList(const SinglyLinkedList&) = delete;
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;

    SinglyLinkedList(SinglyLinkedList&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }

    SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    /// Insert @p value at the head. O(1).
    void push_front(T value) {
        Node* node = new Node{std::move(value), head_};
        head_ = node;
        if (!tail_) tail_ = node;
        ++size_;
    }

    /// Insert @p value at the tail. O(1).
    void push_back(T value) {
        Node* node = new Node{std::move(value), nullptr};
        if (!head_) head_ = node;
        else tail_->next = node;
        tail_ = node;
        ++size_;
    }

    /// Remove the head element and return its value. Throws if empty.
    T pop_front() {
        if (!head_) throw std::out_of_range("pop_front on empty list");
        Node* old = head_;
        T value = std::move(old->data);
        head_ = old->next;
        if (!head_) tail_ = nullptr;
        delete old;
        --size_;
        return value;
    }

    /// Insert @p value before position @p index. O(n).
    void insert(std::size_t index, T value) {
        if (index > size_) throw std::out_of_range("insert: index out of range");
        if (index == 0) { push_front(std::move(value)); return; }
        if (index == size_) { push_back(std::move(value)); return; }
        Node* prev = head_;
        for (std::size_t i = 1; i < index; ++i) prev = prev->next;
        prev->next = new Node{std::move(value), prev->next};
        ++size_;
    }

    /// Remove the element at @p index and return its value. O(n).
    T remove_at(std::size_t index) {
        if (index >= size_) throw std::out_of_range("remove_at: index out of range");
        if (index == 0) return pop_front();
        Node* prev = head_;
        for (std::size_t i = 1; i < index; ++i) prev = prev->next;
        Node* victim = prev->next;
        T value = std::move(victim->data);
        prev->next = victim->next;
        if (victim == tail_) tail_ = prev;
        delete victim;
        --size_;
        return value;
    }

    /// Mutable element access. Throws on out-of-range.
    T& at(std::size_t index) {
        if (index >= size_) throw std::out_of_range("at: index out of range");
        Node* curr = head_;
        for (std::size_t i = 0; i < index; ++i) curr = curr->next;
        return curr->data;
    }

    /// Const element access.
    const T& at(std::size_t index) const {
        if (index >= size_) throw std::out_of_range("at: index out of range");
        Node* curr = head_;
        for (std::size_t i = 0; i < index; ++i) curr = curr->next;
        return curr->data;
    }

    /// Reverse the list in place. O(n).
    void reverse() {
        Node* prev = nullptr;
        Node* curr = head_;
        tail_ = head_;
        while (curr) {
            Node* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head_ = prev;
    }

    std::size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }

    /// Apply @p fn to each element in order.
    template <typename Fn>
    void for_each(Fn fn) const {
        for (Node* n = head_; n; n = n->next) fn(n->data);
    }

private:
    struct Node {
        T data;
        Node* next;
    };

    void clear() {
        while (head_) {
            Node* next = head_->next;
            delete head_;
            head_ = next;
        }
        tail_ = nullptr;
        size_ = 0;
    }

    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    std::size_t size_ = 0;
};

}  // namespace ds

#endif  // DS_SINGLY_LINKED_LIST_HPP
