#include "../IBinaryTree.h"
#include <queue>
#include <stack>
#include <functional>
#include <stdexcept>
#include <algorithm>

template <typename T>
class Node {
public:
    T value;
    Node* left;
    Node* right;
    Node(T val) : value(val), left(nullptr), right(nullptr) {}
};

template <typename T>
class NodeBasedBinaryTree : public IBinaryTree<T, Node<T>*> {
public:
    NodeBasedBinaryTree();                     // Constructor
    ~NodeBasedBinaryTree();                    // Destructor

    void depth_first_insert(T value) override;
    void level_order_insert(T value) override;
    void remove(T value) override;

    Node<T>* search(T value) override;
    void in_order_traversal(std::function<bool(Node<T>*)> func) override;
    void pre_order_traversal(std::function<bool(Node<T>*)> func) override;
    void post_order_traversal(std::function<bool(Node<T>*)> func) override;
    void level_order_traversal(std::function<void(Node<T>*)> func) override;

    T find_min() override;
    T find_max() override;
    int height() override;
    int size() override;
    bool is_empty() override;
    T getValueAt(Node<T>* place) override;

private:
    Node<T>* root;                   // Root node
    int node_count;                 // Number of nodes in the tree

    int height(Node<T>* node);       // Helper function to calculate height
    void in_order_traversal(Node<T>* node, std::function<bool(Node<T>*)> func);
    void pre_order_traversal(Node<T>* node, std::function<bool(Node<T>*)> func);
    void post_order_traversal(Node<T>* node, std::function<bool(Node<T>*)> func);
};

// Constructor
template <typename T>
NodeBasedBinaryTree<T>::NodeBasedBinaryTree() : root(nullptr), node_count(0) {}

// Destructor
template <typename T>
NodeBasedBinaryTree<T>::~NodeBasedBinaryTree() {
    post_order_traversal(root, [](Node<T>* node) { delete node; });
}

// Level-order insertion
template <typename T>
void NodeBasedBinaryTree<T>::level_order_insert(T value) {
    Node<T>* newNode = new Node<T>(value);

    if (!root) {
        root = newNode;
        node_count++;
        return;
    }

    std::queue<Node<T>*> q;
    q.push(root);

    while (!q.empty()) {
        Node<T>* current = q.front();
        q.pop();

        if (!current->left) {
            current->left = newNode;
            node_count++;
            return;
        } else {
            q.push(current->left);
        }

        if (!current->right) {
            current->right = newNode;
            node_count++;
            return;
        } else {
            q.push(current->right);
        }
    }
}

// Depth-first insertion (pre-order)
template <typename T>
void NodeBasedBinaryTree<T>::depth_first_insert(T value) {
    Node<T>* new_node = new Node<T>(value);

    if (!root) {
        root = new_node;
        node_count++;
        return;
    }

    std::stack<Node<T>*> stack;
    stack.push(root);

    while (!stack.empty()) {
        Node<T>* current = stack.top();
        stack.pop();

        if (!current->left) {
            current->left = new_node;
            node_count++;
            return;
        } else if (!current->right) {
            current->right = new_node;
            node_count++;
            return;
        }

        // Push children onto the stack
        stack.push(current->right);
        stack.push(current->left);
    }
}


// Remove a value
template <typename T>
void NodeBasedBinaryTree<T>::remove(T value) {
    if (!root) return;

    Node<T>* nodeToRemove = nullptr;
    Node<T>* deepestNode = nullptr;
    Node<T>* parentOfDeepestNode = nullptr;

    std::queue<Node<T>*> q;
    q.push(root);

    while (!q.empty()) {
        Node<T>* current = q.front();
        q.pop();

        if (current->value == value) {
            nodeToRemove = current;
        }

        if (current->left) {
            parentOfDeepestNode = current;
            deepestNode = current->left;
            q.push(current->left);
        }

        if (current->right) {
            parentOfDeepestNode = current;
            deepestNode = current->right;
            q.push(current->right);
        }
    }

    if (nodeToRemove) {
        if (deepestNode) {
            nodeToRemove->value = deepestNode->value;

            if (parentOfDeepestNode->right == deepestNode) {
                parentOfDeepestNode->right = nullptr;
            } else {
                parentOfDeepestNode->left = nullptr;
            }
            delete deepestNode;
            node_count--;
        } else {
            delete root;
            root = nullptr;
            node_count--;
        }
    }
}

// Search for a value
template <typename T>
Node<T>* NodeBasedBinaryTree<T>::search(T value) {
    Node<T>* foundNode = nullptr;

    pre_order_traversal(root, [&foundNode, value](Node<T>* node) -> bool {
        if (node->value == value) {
            foundNode = node;
            return true;
        }
        return false;
    });

    return foundNode;
}

// Calculate height
template <typename T>
int NodeBasedBinaryTree<T>::height() {
    return height(root);
}

// Get the size of the tree
template <typename T>
int NodeBasedBinaryTree<T>::size() {
    return node_count;
}

// Check if the tree is empty
template <typename T>
bool NodeBasedBinaryTree<T>::is_empty() {
    return root == nullptr;
}

// In-order traversal with a function
template <typename T>
void NodeBasedBinaryTree<T>::in_order_traversal(std::function<bool(Node<T>*)> func) {
    in_order_traversal(root, func);
}

// Pre-order traversal with a function
template <typename T>
void NodeBasedBinaryTree<T>::pre_order_traversal(std::function<bool(Node<T>*)> func) {
    pre_order_traversal(root, func);
}

// Post-order traversal with a function
template <typename T>
void NodeBasedBinaryTree<T>::post_order_traversal(std::function<bool(Node<T>*)> func) {
    post_order_traversal(root, func);
}

// Level-order traversal with a function
template <typename T>
void NodeBasedBinaryTree<T>::level_order_traversal(std::function<void(Node<T>*)> func) {
    if (!root) return;
    
    std::queue<Node<T>*> q;
    q.push(root);

    while (!q.empty()) {
        Node<T>* current = q.front();
        q.pop();
        func(current);

        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
}

// Helper functions

// In-order traversal helper
template <typename T>
void NodeBasedBinaryTree<T>::in_order_traversal(Node<T>* node, std::function<bool(Node<T>*)> func) {
    if (node) {
        in_order_traversal(node->left, func);
        if (func(node)) return;
        in_order_traversal(node->right, func);
    }
}

// Post-order traversal helper
template <typename T>
void NodeBasedBinaryTree<T>::post_order_traversal(Node<T>* node, std::function<bool(Node<T>*)> func) {
    if (node) {
        post_order_traversal(node->left, func);
        post_order_traversal(node->right, func);
        if (func(node)) return;
    }
}

// Pre-order traversal helper
template <typename T>
void NodeBasedBinaryTree<T>::pre_order_traversal(Node<T>* node, std::function<bool(Node<T>*)> func) {
    if (node) {
        if (func(node)) return;
        pre_order_traversal(node->left, func);
        pre_order_traversal(node->right, func);
    }
}

// Calculate height of a node
template <typename T>
int NodeBasedBinaryTree<T>::height(Node<T>* node) {
    if (!node) return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return 1 + std::max(leftHeight, rightHeight);
}

// Find minimum value in the tree
template <typename T>
T NodeBasedBinaryTree<T>::find_min() {
    if (!root) throw std::runtime_error("Tree is empty");

    T min_value = root->value;
    in_order_traversal(root, [&min_value](Node<T>* node) -> bool {
        if (node->value < min_value) {
            min_value = node->value;
        }
        return false;
    });
    return min_value;
}

// Find maximum value in the tree
template <typename T>
T NodeBasedBinaryTree<T>::find_max() {
    if (!root) throw std::runtime_error("Tree is empty");

    T max_value = root->value;
    in_order_traversal(root, [&max_value](Node<T>* node) -> bool {
        if (node->value > max_value) {
            max_value = node->value;
        }
        return false;
    });
    return max_value;
}

template <typename T>
T NodeBasedBinaryTree<T>::getValueAt(Node<T>* place){
    return place->value;
}
