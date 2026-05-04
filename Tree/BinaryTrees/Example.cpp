#include <iostream>
#include <functional>
#include "ArrayBasedBinaryTree/ArrayBasedBinaryTree.h"
#include "NodeBasedBinaryTree/NodeBasedBinaryTree.h"

// Template function to handle both types of trees
template <typename T, typename IndexerType>
void check(IBinaryTree<T, IndexerType>* tree);
template <typename T>
void check_node_search(IBinaryTree<int, Node<int>*>* nodeTree, T value);
template <typename T>
void check_idx_search(IBinaryTree<int, int>* arrayTree, T value);

int main() {
    // Create an ArrayBasedBinaryTree with a capacity of 15 nodes
    IBinaryTree<int, int>* arrayTree = new ArrayBasedBinaryTree<int>(15);
    std::cout << "Testing ArrayBasedBinaryTree:" << std::endl;
    check(arrayTree);
    check_idx_search(arrayTree, 10);  // Test searching for value 7
    delete arrayTree;

    // Create a NodeBasedBinaryTree
    IBinaryTree<int, Node<int>*>* nodeTree = new NodeBasedBinaryTree<int>();
    std::cout << "\nTesting NodeBasedBinaryTree:" << std::endl;
    check(nodeTree);
    check_node_search(nodeTree, 10);  // Test searching for value 7
    delete nodeTree;

    return 0;
}

// Template function to check both ArrayBasedBinaryTree and NodeBasedBinaryTree
template <typename T, typename IndexerType>
void check(IBinaryTree<T, IndexerType>* tree) {
    std::cout << "----------------------------------" << std::endl;
    
    // Insert some values
    tree->depth_first_insert(10);
    tree->depth_first_insert(5);
    tree->depth_first_insert(15);
    tree->depth_first_insert(3);
    tree->depth_first_insert(7);
    tree->depth_first_insert(12);
    tree->depth_first_insert(18);

    // In-Order Traversal
    std::cout << "In-Order Traversal: ";
    tree->in_order_traversal([tree](IndexerType indexer) {
        std::cout << tree->getValueAt(indexer) << " ";
        return false; // Continue traversal
    });
    std::cout << std::endl;

    // Pre-Order Traversal
    std::cout << "Pre-Order Traversal: ";
    tree->pre_order_traversal([tree](IndexerType indexer) {
        std::cout << tree->getValueAt(indexer) << " ";
        return false; // Continue traversal
    });
    std::cout << std::endl;

    // Post-Order Traversal
    std::cout << "Post-Order Traversal: ";
    tree->post_order_traversal([tree](IndexerType indexer) {
        std::cout << tree->getValueAt(indexer) << " ";
        return false; // Continue traversal
    });
    std::cout << std::endl;

    // Level-Order Traversal
    std::cout << "Level-Order Traversal: ";
    tree->level_order_traversal([tree](IndexerType indexer) {
        std::cout << tree->getValueAt(indexer) << " ";
    });
    std::cout << std::endl;

    // Find minimum and maximum values
    std::cout << "Minimum value in the tree: " << tree->find_min() << std::endl;
    std::cout << "Maximum value in the tree: " << tree->find_max() << std::endl;

    // Get the height of the tree
    std::cout << "Height of the tree: " << tree->height() << std::endl;

    // Check if the tree is empty
    std::cout << "Is the tree empty? " << (tree->is_empty() ? "Yes" : "No") << std::endl;

    // Remove a value
    tree->remove(15);
    std::cout << "After removing 15, In-Order Traversal: ";
    tree->in_order_traversal([tree](IndexerType indexer) {
        std::cout << tree->getValueAt(indexer) << " ";
        return false; // Continue traversal
    });
    std::cout << std::endl;
}


template <typename T>
void check_idx_search(IBinaryTree<int, int>* arrayTree, T value) {
    int searchResult = arrayTree->search(value);
    if (searchResult != -1) {
        std::cout << "Value " << value << " found at index " << searchResult << std::endl;
    } else {
        std::cout << "Value " << value << " not found in the tree." << std::endl;
    }
}

template <typename T>
void check_node_search(IBinaryTree<int, Node<int>*>* nodeTree, T value) {
    Node<int>* searchResult = nodeTree->search(value);

    if (searchResult != nullptr) {
        std::cout << "Value " << value << " found at node: \n{Value: " << searchResult->value <<"} " << std::endl;
        if(searchResult->left != nullptr) {
            std::cout <<  "{left: " << searchResult->left->value <<"} " << std::endl;
        }else{
            std::cout <<  "{left: None} " << std::endl;
        }
        if(searchResult->right != nullptr) {
            std::cout << "{right: " << searchResult->left->value <<"} " << std::endl;
        }else{
            std::cout <<  "{right: None} " << std::endl;
        }
    } else {
        std::cout << "Value " << value << " not found in the tree." << std::endl;
    }
}
