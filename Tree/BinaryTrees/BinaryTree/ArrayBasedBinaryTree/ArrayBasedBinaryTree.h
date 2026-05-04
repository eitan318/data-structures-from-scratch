#include <iostream>
#include <cmath>
#include <queue>
#include "../IBinaryTree.h"
#include "../../../Array-/DynamicArray/DynamicArray.h"

template <typename T>
class ArrayBasedBinaryTree : public IBinaryTree<T, int> {
private:
    DynamicArray<T>* tree;  // Using DynamicArray instead of raw array
    int currentSize;        // Number of elements currently in the tree

public:
    ArrayBasedBinaryTree();
    ~ArrayBasedBinaryTree();

    void depth_first_insert(T value) override;
    void level_order_insert(T value) override;
    void remove(T value) override;
    void in_order_traversal(std::function<bool(int)> func) override;
    void pre_order_traversal(std::function<bool(int)> func) override;
    void post_order_traversal(std::function<bool(int)> func) override;
    void level_order_traversal(std::function<void(int)> func) override;

    T find_min() override;
    T find_max() override;
    int height() override;
    int size() override;
    bool is_empty() override;
    int search(T value) override;

    T getValueAt(int place) override;

private:
    void in_order_traversal(int index, std::function<bool(int)> func);
    void pre_order_traversal(int index, std::function<bool(int)> func);
    void post_order_traversal(int index, std::function<bool(int)> func);
};

// Constructor
template <typename T>
ArrayBasedBinaryTree<T>::ArrayBasedBinaryTree() : currentSize(0) {
    this->tree = new DynamicArray<T>();
}

// Destructor
template <typename T>
ArrayBasedBinaryTree<T>::~ArrayBasedBinaryTree() {
    delete this->tree;
}

// Level-order insertion
template <typename T>
void ArrayBasedBinaryTree<T>::level_order_insert(T value) {
    tree->add(value);
    currentSize++;
}

// Depth-first insertion (pre-order)
template <typename T>
void ArrayBasedBinaryTree<T>::depth_first_insert(T value) {
    level_order_insert(value);  // In an array-based tree, depth-first and level-order are functionally similar
}

// Remove a value
template <typename T>
void ArrayBasedBinaryTree<T>::remove(T value) {
    int index = this->search(value);
    if (index == -1) return;

    (*tree)[index] = (*tree)[--currentSize];  // Replace with the last element and reduce size
    tree->remove_at(currentSize);
}

// In-order traversal
template <typename T>
void ArrayBasedBinaryTree<T>::in_order_traversal(int index, std::function<bool(int)> func) {
    if (index >= currentSize) return;

    in_order_traversal(2 * index + 1, func);  // Left child
    if (func(index)) return;
    in_order_traversal(2 * index + 2, func);  // Right child
}

template <typename T>
void ArrayBasedBinaryTree<T>::in_order_traversal(std::function<bool(int)> func) {
    in_order_traversal(0, func);
}

// Pre-order traversal
template <typename T>
void ArrayBasedBinaryTree<T>::pre_order_traversal(int index, std::function<bool(int)> func) {
    if (index >= currentSize) return;

    if (func(index)) return;
    pre_order_traversal(2 * index + 1, func);  // Left child
    pre_order_traversal(2 * index + 2, func);  // Right child
}

template <typename T>
void ArrayBasedBinaryTree<T>::pre_order_traversal(std::function<bool(int)> func) {
    pre_order_traversal(0, func);
}

// Post-order traversal
template <typename T>
void ArrayBasedBinaryTree<T>::post_order_traversal(int index, std::function<bool(int)> func) {
    if (index >= currentSize) return;

    post_order_traversal(2 * index + 1, func);  // Left child
    post_order_traversal(2 * index + 2, func);  // Right child
    if (func(index)) return;
}

template <typename T>
void ArrayBasedBinaryTree<T>::post_order_traversal(std::function<bool(int)> func) {
    post_order_traversal(0, func);
}

// Level-order traversal
template <typename T>
void ArrayBasedBinaryTree<T>::level_order_traversal(std::function<void(int)> func) {
    for (int i = 0; i < currentSize; ++i) {
        func(i);
    }
}

// Find minimum value
template <typename T>
T ArrayBasedBinaryTree<T>::find_min() {
    if (is_empty()) throw std::runtime_error("Tree is empty");

    T min_value = (*tree)[0];
    for (int i = 1; i < currentSize; ++i) {
        if ((*tree)[i] < min_value) {
            min_value = (*tree)[i];
        }
    }
    return min_value;
}

// Find maximum value
template <typename T>
T ArrayBasedBinaryTree<T>::find_max() {
    if (is_empty()) throw std::runtime_error("Tree is empty");

    T max_value = (*tree)[0];
    for (int i = 1; i < currentSize; ++i) {
        if ((*tree)[i] > max_value) {
            max_value = (*tree)[i];
        }
    }
    return max_value;
}

// Calculate height
template <typename T>
int ArrayBasedBinaryTree<T>::height() {
    if (is_empty()) return 0;
    return std::ceil(std::log2(currentSize + 1));
}

// Get the size of the tree
template <typename T>
int ArrayBasedBinaryTree<T>::size() {
    return currentSize;
}

// Check if the tree is empty
template <typename T>
bool ArrayBasedBinaryTree<T>::is_empty() {
    return currentSize == 0;
}

// Search for a value
template <typename T>
int ArrayBasedBinaryTree<T>::search(T value) {
    for (int i = 0; i < currentSize; ++i) {
        if ((*tree)[i] == value) {
            return i;
        }
    }
    return -1;  // Value not found
}

template <typename T>
T ArrayBasedBinaryTree<T>::getValueAt(int place) {
    return (*tree)[place];
}
