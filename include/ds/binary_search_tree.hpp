/**
 * @file binary_search_tree.hpp
 * @brief Unbalanced binary search tree.
 */
#ifndef DS_BINARY_SEARCH_TREE_HPP
#define DS_BINARY_SEARCH_TREE_HPP

#include <cstddef>
#include <functional>
#include <stdexcept>
#include <utility>

namespace ds {

/**
 * @brief Classical (unbalanced) binary search tree.
 *
 * Average-case operations are O(log n); worst case (sorted input) degrades
 * to O(n). Use a self-balancing tree for guaranteed bounds.
 *
 * @tparam T       key type.
 * @tparam Compare strict weak ordering on @p T (default @c std::less).
 */
template <typename T, typename Compare = std::less<T>>
class BinarySearchTree {
public:
    BinarySearchTree() = default;
    explicit BinarySearchTree(Compare compare) : cmp_(std::move(compare)) {}
    ~BinarySearchTree() { destroy(root_); }

    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    BinarySearchTree(BinarySearchTree&& other) noexcept
        : root_(other.root_), size_(other.size_), cmp_(std::move(other.cmp_)) {
        other.root_ = nullptr;
        other.size_ = 0;
    }

    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept {
        if (this != &other) {
            destroy(root_);
            root_ = other.root_;
            size_ = other.size_;
            cmp_ = std::move(other.cmp_);
            other.root_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    /// Insert @p value. Duplicate values are ignored.
    /// @return true if a new node was created.
    bool insert(T value) {
        Node** slot = &root_;
        while (*slot) {
            if (cmp_(value, (*slot)->value))      slot = &(*slot)->left;
            else if (cmp_((*slot)->value, value)) slot = &(*slot)->right;
            else return false;  // duplicate
        }
        *slot = new Node{std::move(value), nullptr, nullptr};
        ++size_;
        return true;
    }

    /// True if @p value is in the tree.
    bool contains(const T& value) const {
        const Node* n = root_;
        while (n) {
            if (cmp_(value, n->value))      n = n->left;
            else if (cmp_(n->value, value)) n = n->right;
            else return true;
        }
        return false;
    }

    /// Remove @p value. @return true if a node was deleted.
    bool remove(const T& value) {
        Node** slot = &root_;
        while (*slot) {
            if (cmp_(value, (*slot)->value))      slot = &(*slot)->left;
            else if (cmp_((*slot)->value, value)) slot = &(*slot)->right;
            else break;
        }
        if (!*slot) return false;
        Node* victim = *slot;
        if (!victim->left) {
            *slot = victim->right;
        } else if (!victim->right) {
            *slot = victim->left;
        } else {
            // Replace with in-order successor (smallest in the right subtree).
            Node** succ_slot = &victim->right;
            while ((*succ_slot)->left) succ_slot = &(*succ_slot)->left;
            Node* succ = *succ_slot;
            *succ_slot = succ->right;
            succ->left = victim->left;
            succ->right = victim->right;
            *slot = succ;
        }
        delete victim;
        --size_;
        return true;
    }

    /// Smallest key. Throws if empty.
    const T& min() const {
        if (!root_) throw std::out_of_range("min on empty tree");
        const Node* n = root_;
        while (n->left) n = n->left;
        return n->value;
    }

    /// Largest key. Throws if empty.
    const T& max() const {
        if (!root_) throw std::out_of_range("max on empty tree");
        const Node* n = root_;
        while (n->right) n = n->right;
        return n->value;
    }

    /// In-order traversal (sorted order).
    template <typename Fn>
    void in_order(Fn fn) const { in_order_impl(root_, fn); }

    int height() const { return height_impl(root_); }
    std::size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return root_ == nullptr; }

private:
    struct Node {
        T value;
        Node* left;
        Node* right;
    };

    static void destroy(Node* n) {
        if (!n) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }

    static int height_impl(const Node* n) {
        if (!n) return 0;
        int l = height_impl(n->left);
        int r = height_impl(n->right);
        return 1 + (l > r ? l : r);
    }

    template <typename Fn>
    static void in_order_impl(const Node* n, Fn& fn) {
        if (!n) return;
        in_order_impl(n->left, fn);
        fn(n->value);
        in_order_impl(n->right, fn);
    }

    Node* root_ = nullptr;
    std::size_t size_ = 0;
    Compare cmp_{};
};

}  // namespace ds

#endif  // DS_BINARY_SEARCH_TREE_HPP
