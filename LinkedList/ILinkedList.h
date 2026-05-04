#ifndef ILINKEDLIST_H
#define ILINKEDLIST_H



template <typename T>
class ILinkedList{
public:
    virtual ~ILinkedList() = default;  // Virtual destructor
    virtual void add_start(T value) = 0;
    virtual void add_end(T value) = 0;
    virtual void print(void (*print_func)(T) = default_print) = 0;
    virtual bool remove_node(T node_data) = 0;
    virtual T remove_at(int idx) = 0;
    virtual void insert_at(T data, int idx) = 0;
    virtual void reverse() = 0;
    virtual T get(int idx) = 0;
    virtual T get_last() = 0;
    virtual void set(int idx, T new_value) = 0;
    virtual void set_last(T new_value) = 0;
    virtual void move_node(int idxFrom, int idxTo) = 0;
    virtual void replace(int one_idx, int second_idx) = 0;
    virtual bool is_empty() = 0;
    virtual int Count() = 0;

};

#endif //ILINKEDLIST_H


