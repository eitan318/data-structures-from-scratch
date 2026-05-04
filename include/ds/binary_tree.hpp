/**
 * @file binary_tree.hpp
 * @brief Plain binary tree with level-order insertion and traversals.
 */
#ifndef DS_BINARY_TREE_HPP
#define DS_BINARY_TREE_HPP

#include <cstddef>
#include <queue>
#include <stack>
#include <utility>

namespace ds {

/**
 * @brief Pointer-based binary tree.
 *
 * Inserts in level order so the tree stays as compact as possible.
 * Provides the four classical traversals (pre/in/post/level) which
 * accept any callable.
 *
 * @note This is *not* a search tree — see @ref BinarySearchTree for that.
 *
 * @tparam T element type.
 */
template <typename T>
class BinaryTree {
public:
    BinaryTree() = default;
    ~BinaryTree() { destroy(root_); }

    BinaryTree(const BinaryTree&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;

    BinaryTree(BinaryTree&& other) noexcept
        : root_(other.root_), size_(other.size_) {
        other.root_ = nullptr;
        other.size_ = 0;
    }

    BinaryTree& operator=(BinaryTree&& other) noexcept {
        if (this != &other) {
            destroy(root_);
            root_ = other.root_;
            size_ = other.size_;
            other.root_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    /// Insert @p value into the first available slot in level order. O(n).
    void insert(T value) {
        Node* node = new Node{std::move(value), nullptr, nullptr};
        if (!root_) {
            root_ = node;
            ++size_;
            return;
        }
        std::queue<Node*> q;
        q.push(root_);
        while (!q.empty()) {
            Node* cur = q.front(); q.pop();
            if (!cur->left)  { cur->left = node;  ++size_; return; }
            if (!cur->right) { cur->right = node; ++size_; return; }
            q.push(cur->left);
            q.push(cur->right);
        }
    }

    /// Pre-order: root, left, right.
    template <typename Fn>
    void pre_order(Fn fn) const { pre_order_impl(root_, fn); }

    /// In-order: left, root, right.
    template <typename Fn>
    void in_order(Fn fn) const { in_order_impl(root_, fn); }

    /// Post-order: left, right, root.
    template <typename Fn>
    void post_order(Fn fn) const { post_order_impl(root_, fn); }

    /// Breadth-first traversal.
    template <typename Fn>
    void level_order(Fn fn) const {
        if (!root_) return;
        std::queue<Node*> q;
        q.push(root_);
        while (!q.empty()) {
            Node* cur = q.front(); q.pop();
            fn(cur->value);
            if (cur->left)  q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
    }

    /// Height of the tree (empty tree => 0).
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

    static int height_impl(Node* n) {
        if (!n) return 0;
        int l = height_impl(n->left);
        int r = height_impl(n->right);
        return 1 + (l > r ? l : r);
    }

    template <typename Fn>
    static void pre_order_impl(Node* n, Fn& fn) {
        if (!n) return;
        fn(n->value);
        pre_order_impl(n->left, fn);
        pre_order_impl(n->right, fn);
    }

    template <typename Fn>
    static void in_order_impl(Node* n, Fn& fn) {
        if (!n) return;
        in_order_impl(n->left, fn);
        fn(n->value);
        in_order_impl(n->right, fn);
    }

    template <typename Fn>
    static void post_order_impl(Node* n, Fn& fn) {
        if (!n) return;
        post_order_impl(n->left, fn);
        post_order_impl(n->right, fn);
        fn(n->value);
    }

    Node* root_ = nullptr;
    std::size_t size_ = 0;
};

}  // namespace ds

#endif  // DS_BINARY_TREE_HPP
