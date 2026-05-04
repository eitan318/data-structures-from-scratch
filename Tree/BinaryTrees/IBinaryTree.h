#ifndef IBINARYTREE_H
#define IBINARYTREE_H

#include <functional> // For std::function

template <typename T, typename IndexerType>
class IBinaryTree {
public:
    virtual void depth_first_insert(T value) = 0;
    virtual void level_order_insert(T value) = 0;
    virtual void remove(T value) = 0;
    virtual void in_order_traversal(std::function<bool(IndexerType)> func) = 0;
    virtual void pre_order_traversal(std::function<bool(IndexerType)> func) = 0;
    virtual void post_order_traversal(std::function<bool(IndexerType)> func) = 0;
    virtual void level_order_traversal(std::function<void(IndexerType)> func) = 0;
    virtual T find_min() = 0;
    virtual T find_max() = 0;
    virtual int height() = 0;
    virtual int size() = 0;
    virtual bool is_empty() = 0;
    virtual IndexerType search(T value) = 0;

    virtual T getValueAt(IndexerType place) = 0;
};

#endif // IBINARYTREE_H