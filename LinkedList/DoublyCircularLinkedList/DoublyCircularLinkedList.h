#ifndef DOUBLYCIRCULARLINKEDLIST_H
#define DOUBLYCIRCULARLINKEDLIST_H

#include <stdexcept>
#include <iostream>
#include <stdbool.h>
#include "../ILinkedList.h"


template <typename T>
class DoublyCircularLinkedList : public ILinkedList<T>{
private:
    struct Node {  
        T data;
        Node* head;

        Node(T value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;

    static void default_print(T data) {
        std::cout << data << " ";
    }

    int count;
    Node* find_node_at(int idx);
    std::pair<Node*, Node*> find_nodes_at(int idx1, int idx2);

public:

    DoublyCircularLinkedList() : head(nullptr), {}
    ~DoublyCircularLinkedList();

    void add_start(T value) override;
    void add_end(T value) override;
    void print(void (*print_func)(T) = default_print) override;
    bool remove_node(T node_data) override;
    T remove_at(int idx) override;
    void insert_at(T data, int idx) override;
    void reverse() override;
    T get(int idx) override;
    T get_last() override;
    void set(int idx, T new_value) override;
    void set_last(T new_value) override;
    void move_node(int idxFrom, int idxTo) override;
    void replace(int one_idx, int second_idx) override;
    int Count() override;
    bool is_empty() override;
};



template <typename T>
void DoublyCircularLinkedList<T>::add_start(T value) {
    Node* new_node = new Node(value);
    if (this->head == nullptr) {
        this->head = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
    } else {
        Node* tail = this->head->prev;
        new_node->next = this->head;
        new_node->prev = tail;
        tail->next = new_node;
        this->head->prev = new_node;
        this->head = new_node;
    }
    this->count++;
}

template <typename T>
void DoublyCircularLinkedList<T>::add_end(T value) {
    Node* new_node = new Node(value);
    if (this->head == nullptr) {
        this->head = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
    } else {
        Node* tail = this->head->prev;
        tail->next = new_node;
        new_node->prev = tail;
        new_node->next = this->head;
        this->head->prev = new_node;
    }
    this->count++;
}



template <typename T>
void DoublyCircularLinkedList<T>::print(void (*print_func)(T)) {
    if (!this->head) return;

    Node* curr = this->head;
    do {
        print_func(curr->data);
        curr = curr->next;
    } while (curr != this->head);
    std::cout << std::endl;
}


template <typename T>
bool DoublyCircularLinkedList<T>::remove_node(T node_data) {
    if (this->head == nullptr) {
        return false;  // List is empty
    }

    Node* curr = this->head;

    do {
        if (curr->data == node_data) {
            if (curr == this->head) {
                // Update the head pointer
                if (this->head->next == this->head) {
                    // Only one node in the list
                    this->head = nullptr;
                } else {
                    this->head = curr->next;
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                }
            } else {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
            }

            delete curr;
            this->count--;
            return true;
        }
        curr = curr->next;
    } while (curr != this->head);

    return false;
}



template <typename T>
typename DoublyCircularLinkedList<T>::Node* DoublyCircularLinkedList<T>::find_node_at(int idx) {
    if (this->head == nullptr) {
        throw std::runtime_error("List is empty!");
    }
    if (idx < 0 || idx >= this->count) {
        throw std::out_of_range("Index out of range!");
    }

    Node* curr = nullptr;
    if (idx < this->count / 2) {
        // Start from the head
        curr = this->head;
        for (int i = 0; i < idx; i++) {
            curr = curr->next;
        }
    }
    else {
        // Start from the tail
        curr = this->head->prev;
        for (int i = this->count - 1; i > idx; i--) {
            curr = curr->prev;
        }
    }
    return curr;
}

template <typename T>
std::pair<typename DoublyCircularLinkedList<T>::Node*, typename DoublyCircularLinkedList<T>::Node*> DoublyCircularLinkedList<T>::find_nodes_at(int idx1, int idx2) {
    if (this->head == nullptr) {
        throw std::runtime_error("List is empty!");
    }
    if (idx1 < 0 || idx1 >= this->count) {
        throw std::out_of_range("Index1 out of range!");
    }
    if (idx2 < 0 || idx2 >= this->count) {
        throw std::out_of_range("Index2 out of range!");
    }
    if (idx1 == idx2) {
        Node* node = this->find_node_at(idx1);
        return std::make_pair(node, node);
    }


    Node* curr_head = this->head;
    Node* curr_tail = this->head->prev;
    Node* node1 = nullptr;
    Node* node2 = nullptr;

    if (idx1 < this->count / 2 && idx2 < this->count / 2) {
        // Start from the head
        for (int i = 0; i < std::max(idx1,idx2); i++) {
            if (i == std::min(idx1, idx2)) {
                node1 = curr_head;
            }
            curr_head = curr_head->next;
        }
        node2 = curr_head;
    }
    else if (idx1 < this->count / 2 || idx2 < this->count / 2){
        // Start from the head and tail
        int i1 = 0;
        int i2 = count - 1;
        while(i1 != std::min(idx1, idx2) || i2 != std::max(idx1, idx2) ) {
            if (i1 != std::min(idx1, idx2)) {
                i1++;
                curr_head = curr_head->next;
            }
            if (i2 != std::max(idx1, idx2)) {
                i2--;
                curr_tail = curr_tail->prev;
            }
            
        }
        node1 = curr_head;
        node2 = curr_tail;
    }
    else {
        // Start from the tail
        for (int i = this->count - 1; i > std::min(idx1,idx2); i--) {
            if (i == std::max(idx1, idx2)) {
                node2 = curr_tail;
            }
            curr_tail = curr_tail->prev;
        }
        node1 = curr_tail;
    }

    if (!node1 || !node2) {
        throw std::runtime_error("Nodes not found, this should not happen if indices are valid.");
    }

    return idx1 < idx2 ? std::make_pair(node1, node2) : std::make_pair(node2, node1);
}
template <typename T>
T DoublyCircularLinkedList<T>::remove_at(int idx) {
    if (idx < 0 || idx >= this->count) {
        throw std::out_of_range("Index out of range!");
    }

    Node* curr = this->find_node_at(idx);
    if (curr == nullptr) {
        throw std::runtime_error("Node not found!");
    }

    T data = curr->data;

    // Update previous node's next pointer, or head if removing the head
    if (curr->prev != nullptr) {
        curr->prev->next = curr->next;
    }
    else {
        // Removing the head
        this->head = curr->next;
    }

    // Update next node's previous pointer, or tail if removing the tail
    if (curr->next != nullptr) {
        curr->next->prev = curr->prev;
    }
    else {
        // Removing the tail
        this->head->prev = curr->prev;
    }

    delete curr;
    this->count--;
    return data;
}

template <typename T>
void DoublyCircularLinkedList<T>::insert_at(T data, int idx) {
   
    if(idx == 0){
        add_start(data);
    }else{
        Node* new_node = new Node(data);
        Node* curr = this->find_node_at(idx - 1);
        new_node->next = curr->next;
        new_node->prev = curr;
        curr->next->prev = new_node;
        curr->next = new_node;
        this->count++;
    }

}


template <typename T>
T DoublyCircularLinkedList<T>::get(int idx) {
    return this->find_node_at(idx)->data;
}

template <typename T>
T DoublyCircularLinkedList<T>::get_last() {
    if (this->head == nullptr) {
        throw std::runtime_error("List is empty!");
    }
    return this->head->prev->data;
}


template <typename T>
void DoublyCircularLinkedList<T>::set(int idx, T new_value) {
    Node* node = this->find_node_at(idx);
    node->data = new_value;
}



template <typename T>
void DoublyCircularLinkedList<T>::set_last(T new_value) {
    if (this->head == nullptr) {
        throw std::runtime_error("List is empty!");
    }
    this->head->prev->data = new_value;
}

template <typename T>
void DoublyCircularLinkedList<T>::reverse() {
    if (this->count <= 1) {
        return;  // List is empty
    }
    Node* temp_head = this->head;
    Node* temp_tail = this->head->prev;
    Node* curr_head = this->head;
    Node* curr_tail = this->head->prev;

    // Traverse from both ends towards the center
    while (curr_head != curr_tail && curr_head->next != curr_tail) {
        std::swap(curr_head->prev, curr_head->next);
        std::swap(curr_tail->prev, curr_tail->next);
        curr_head = curr_head->prev;
        curr_tail = curr_tail->next;
    }
    if (curr_head != curr_tail) {
        std::swap(curr_head->prev, curr_head->next);
    }
    std::swap(curr_tail->prev, curr_tail->next);

    this->head = temp_tail;
    this->head->prev = temp_head;
}


template <typename T>
void DoublyCircularLinkedList<T>::move_node(int idx_from, int idx_to) {
    if (idx_from == idx_to) {
        return;
    }
    
    auto nodes = this->find_nodes_at(idx_from, idx_to);
    Node* node_to_move = nodes.first;

    if (node_to_move->prev) {
        node_to_move->prev->next = node_to_move->next;
    } else {
        this->head = node_to_move->next;
    }

    if (node_to_move->next) {
        node_to_move->next->prev = node_to_move->prev;
    } else {
        this->head->prev = node_to_move->prev;
    }

    if (idx_from < idx_to) {
        // Insert node_to_move after the target node (second node)
        Node* prev_target = nodes.second;
        node_to_move->next = prev_target->next;
        node_to_move->prev = prev_target;

        if (prev_target->next) {
            prev_target->next->prev = node_to_move;
        } else {
            this->head->prev = node_to_move;
        }

        prev_target->next = node_to_move;
    } else {
        // Insert node_to_move before\(instead of) the target node (second node)
        Node* target = nodes.second;
        node_to_move->next = target;
        node_to_move->prev = target->prev;

        if (target->prev) {
            target->prev->next = node_to_move;
        } else {
            this->head = node_to_move;
        }

        target->prev = node_to_move;
    }
}


template <typename T>
int DoublyCircularLinkedList<T>::Count() {
    return this->count;
}

template <typename T>
inline bool DoublyCircularLinkedList<T>::is_empty(){
    return this->count == 0;
}

template <typename T>
void DoublyCircularLinkedList<T>::replace(int idx1, int idx2) {
    if (idx1 == idx2) {
        return; // No need to swap if indices are the same
    }

    auto nodes = this->find_nodes_at(idx1, idx2);


    //A simpler way to swap is data swap: 
    //std::swap(nodes.first->data, nodes.second->data);
    //Here I did pointer swap:
    Node* after_first = nodes.first->next;
    Node* before_first = nodes.first->prev;
    Node* after_second = nodes.second->next;
    Node* before_second = nodes.second->prev;

    // Update pointers of adjacent nodes
    if (after_first != nullptr) {
        after_first->prev = nodes.second;
    }
    else {
        this->head->prev = nodes.second; // If nodes.first was the tail
    }

    if (before_first != nullptr) {
        before_first->next = nodes.second;
    }
    else {
        this->head = nodes.second; // If nodes.first was the head
    }

    if (after_second != nullptr) {
        after_second->prev = nodes.first;
    }
    else {
        this->head->prev = nodes.first; // If nodes.second was the tail
    }

    if (before_second != nullptr) {
        before_second->next = nodes.first;
    }
    else {
        this->head = nodes.first; // If nodes.second was the head
    }

    // Finalize swapping nodes
    nodes.first->prev = before_second == nodes.first ? nodes.second : before_second;
    nodes.second->prev = before_first == nodes.second ? nodes.first : before_first;
    nodes.first->next = after_second == nodes.first ? nodes.second : after_second;
    nodes.second->next = after_first == nodes.second ? nodes.first : after_first;

}

template <typename T>
DoublyCircularLinkedList<T>::~DoublyCircularLinkedList() {
    while (this->count > 0) {
        remove_at(0);
    }
}


#endif // DOUBLYCIRCULARLINKEDLIST_H