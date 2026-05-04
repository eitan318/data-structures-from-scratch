#include "SinglyLinkedList/SinglyLinkedList.h" // Include your LinkedList header
#include "DoublyLinkedList/DoublyLinkedList.h"
#include "CircularLinkedList/CircularLinkedList.h"
#include "DoublyCircularLinkedList/DoublyCircularLinkedList.h"


#include <iostream>

int check(ILinkedList<int>* list, char* name);

int main() {
    // Create a SinglyLinkedList
    ILinkedList<int>* singly_list = new SinglyLinkedList<int>();
    check(singly_list, "SinglyLinkedList");
    delete singly_list;
    ILinkedList<int>* doubly_list = new DoublyLinkedList<int>();
    check(doubly_list, "DoublyLinkedList");
    delete doubly_list;
    ILinkedList<int>* circular_list = new SinglyLinkedList<int>();
    check(circular_list, "CircularLinkedList");
    delete circular_list;
    ILinkedList<int>* doubly_circular_list = new DoublyLinkedList<int>();
    check(doubly_circular_list, "DoublyCircularLinkedList");
    delete doubly_circular_list;
}

// Custom print function for demonstration
void print_int(int data) {
    std::cout << data << " ";
}

int check(ILinkedList<int>* list, char* name) {

    std::cout << "--------------" << name << "----------------\n";

    // Add elements to the list
    list->add_start(1);
    list->add_end(2);
    list->add_end(3);
    list->add_end(4);
    list->add_end(5);

    std::cout << "Original list: ";
    list->print(print_int);

    // Insert elements at specific positions
    list->insert_at(10, 2);
    list->insert_at(20, 0);

    std::cout << "After inserting 10 at index 2 and 20 at index 0: ";
    list->print(print_int);

    // Remove elements
    list->remove_node(3);
    std::cout << "After removing 3: ";
    list->print(print_int);

    // Remove element at specific index
    int removed_value = list->remove_at(1);
    std::cout << "Removed value at index 1: " << removed_value << std::endl;
    std::cout << "After removing element at index 1: ";
    list->print(print_int);

    // Replace elements at specific indices
    list->replace(1, 2);
    std::cout << "After replacing elements at indices 1 and 2: ";
    list->print(print_int);

    // Move element from one index to another
    list->move_node(0, 2);
    std::cout << "After moving element from index 0 to 2: ";
    list->print(print_int);

    // Reverse the list
    list->reverse();
    std::cout << "After reversing the list: ";
    list->print(print_int);

    // Get elements at specific indices
    try {
        std::cout << "Element at index 1: " << list->get(1) << std::endl;
        std::cout << "Last element: " << list->get_last() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    // Set elements at specific indices
    list->set(1, 100);
    list->set_last(200);
    std::cout << "After setting element at index 1 to 100 and last element to 200: ";
    list->print(print_int);

    return 0;
}
