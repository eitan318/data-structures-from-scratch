/**
 * @file doubly_linked_list.hpp
 * @brief Doubly linked list with bidirectional traversal.
 */
#ifndef DS_DOUBLY_LINKED_LIST_HPP
#define DS_DOUBLY_LINKED_LIST_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace ds {

/**
 * @brief Doubly linked list with O(1) insert/remove at both ends.
 *
 * Random access is O(n/2): @ref at picks the closer end to start from.
 *
 * @tparam T element type.
 */
template <typename T>
class DoublyLinkedList {
public:
    DoublyLinkedList() = default;
    ~DoublyLinkedList() { clear(); }

    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    DoublyLinkedList(DoublyLinkedList&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }

    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {
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

    /// Insert at the head. O(1).
    void push_front(T value) {
        Node* node = new Node{std::move(value), nullptr, head_};
        if (head_) head_->prev = node;
        else tail_ = node;
        head_ = node;
        ++size_;
    }

    /// Insert at the tail. O(1).
    void push_back(T value) {
        Node* node = new Node{std::move(value), tail_, nullptr};
        if (tail_) tail_->next = node;
        else head_ = node;
        tail_ = node;
        ++size_;
    }

    /// Remove and return the head value. Throws if empty.
    T pop_front() {
        if (!head_) throw std::out_of_range("pop_front on empty list");
        Node* old = head_;
        T value = std::move(old->data);
        head_ = old->next;
        if (head_) head_->prev = nullptr;
        else tail_ = nullptr;
        delete old;
        --size_;
        return value;
    }

    /// Remove and return the tail value. Throws if empty.
    T pop_back() {
        if (!tail_) throw std::out_of_range("pop_back on empty list");
        Node* old = tail_;
        T value = std::move(old->data);
        tail_ = old->prev;
        if (tail_) tail_->next = nullptr;
        else head_ = nullptr;
        delete old;
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

    /// Remove the element at @p index. Returns its value. O(n/2).
    T remove_at(std::size_t index) {
        if (index >= size_) throw std::out_of_range("remove_at: index out of range");
        Node* victim = node_at(index);
        T value = std::move(victim->data);
        if (victim->prev) victim->prev->next = victim->next;
        else head_ = victim->next;
        if (victim->next) victim->next->prev = victim->prev;
        else tail_ = victim->prev;
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

    /// Reverse the list in place. O(n).
    void reverse() {
        Node* curr = head_;
        while (curr) {
            Node* next = curr->next;
            curr->next = curr->prev;
            curr->prev = next;
            curr = next;
        }
        std::swap(head_, tail_);
    }

    std::size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }

    template <typename Fn>
    void for_each(Fn fn) const {
        for (Node* n = head_; n; n = n->next) fn(n->data);
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
        Node* curr = tail_;
        for (std::size_t i = size_ - 1; i > index; --i) curr = curr->prev;
        return curr;
    }

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

#endif  // DS_DOUBLY_LINKED_LIST_HPP
