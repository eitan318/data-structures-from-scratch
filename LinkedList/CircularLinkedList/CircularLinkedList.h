#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H

template <typename T>
class CircularLinkedList : public ILinkedList<T> {
private:
    struct Node {  // Node is nested inside SinglyLinkedList
        T data;
        Node* next;

        Node(T value) : data(value), next(nullptr) {}
    };

    Node* last;
    int count;
    Node* reverse_recursive(Node* curr);

    static void default_print(T data) {
        std::cout << data << " ";
    }

public:
    CircularLinkedList() : last(nullptr), count(0) {}
    ~CircularLinkedList();

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
    bool is_empty() override;
    int Count() override;

};

template <typename T>
inline void CircularLinkedList<T>::add_start(T value)
{
    Node* newNode = new Node(value);
    if (this->last == nullptr) {
        this->last = newNode;
        this->last->next = newNode;
    } else {
        newNode->next = this->last->next;
        this->last->next = newNode;
    }
    count++;
}


template <typename T>
inline void CircularLinkedList<T>::add_end(T value)
{
    Node* newNode = new Node(value);
    if (this->last == nullptr) {
        this->last = newNode;
        this->last->next = newNode;
    } else {
        newNode->next = this->last->next;
        this->last->next = newNode;
        this->last = newNode;
    }
    count++;
}

template <typename T>
inline void CircularLinkedList<T>::print(void (*print_func)(T)) {
    if (this->last == nullptr) return;
    Node* curr = this->last->next;
    do {
        print_func(curr->data);
        curr = curr->next;
    } while (curr != this->last->next);
    std::cout << std::endl;
}


template <typename T>
inline bool CircularLinkedList<T>::remove_node(T node_data) {
    if (this->last == nullptr) return false;

    Node* curr = this->last->next;
    Node* prev = this->last;

    do {
        if (curr->data == node_data) {
            prev->next = curr->next;
            if (curr == this->last) {
                if (curr == prev) {
                    this->last = nullptr; // List becomes empty
                } else {
                    this->last = prev;
                }
            }
            delete curr;
            count--;
            return true;
        }
        prev = curr;
        curr = curr->next;
    } while (curr != this->last->next);

    return false;
}


template <typename T>
inline T CircularLinkedList<T>::remove_at(int idx) {
    if (idx < 0 || idx >= this->count) {
        std::cerr << "Index out of range." << std::endl;
        return T(); // Return default value of T
    }

    Node* curr = this->last->next;
    Node* prev = this->last;

    for (int i = 0; i < idx; i++) {
        prev = curr;
        curr = curr->next;
    }

    prev->next = curr->next;
    if (curr == this->last) {
        this->last = prev;
    }

    T value = curr->data;
    delete curr;
    count--;
    return value;
}

template <typename T>
inline T CircularLinkedList<T>::get(int idx) {
    if (idx < 0 || idx >= this->count) {
        std::cerr << "Index out of range." << std::endl;
        return T(); // Return default value of T
    }

    Node* curr = this->last->next;
    for (int i = 0; i < idx; i++) {
        curr = curr->next;
    }

    return curr->data;
}

template <typename T>
inline void CircularLinkedList<T>::reverse() {
    if (this->last == nullptr) return;

    Node* prev = this->last;
    Node* curr = this->last->next;
    Node* next = nullptr;
    Node* first = curr;

    do {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    } while (prev != this->last);

    this->last = first;
}


template <typename T>
inline T CircularLinkedList<T>::get_last()
{
    return this->last->value;
}

template <typename T>
inline void CircularLinkedList<T>::set(int idx, T new_value)
{
    if(idx < 0 || idx >= this->count){
        std::cerr << "idx out of range." << std::endl;
    }

    if(this->last == nullptr){
        std::cerr << "list empty." << std::endl;
    }

    Node* curr = this->last->next;
    Node* prev = this->last;

    for(int i = idx; i < this->count; i++){
        curr = curr->next;
        prev = prev->next;
    }
    
    curr->value = new_value; 
}

template <typename T>
inline void CircularLinkedList<T>::set_last(T new_value)
{
    this->last->value = new_value;
}

template <typename T>
inline bool CircularLinkedList<T>::is_empty()
{
    return this->size() == 0;
}

template <typename T>
inline int CircularLinkedList<T>::Count()
{
    return this->count;
}

template <typename T>
inline void CircularLinkedList<T>::move_node(int idxFrom, int idxTo)
{
    
    if (idxFrom == idxTo || idxFrom < 0 || idxTo < 0 || idxFrom >= this->count || idxTo >= this->count || this->last == nullptr) {
        return;
    }

    Node* prevFrom = this->last;
    Node* nodeFrom = this->last->next;

    for (int i = 0; i < idxFrom; i++) {
        prevFrom = nodeFrom;
        nodeFrom = nodeFrom->next;
    }

    // Remove nodeFrom from its position
    if (prevFrom != nullptr) {
        prevFrom->next = nodeFrom->next;
    }
    else { 
        this->last = nodeFrom->next;
    }
    if (nodeFrom == this->last) {
        this->last = prevFrom;
    }

    if (idxTo == 0) {
        // Insert at the head
        nodeFrom->next = this->last->next;
        this->last->next = nodeFrom;
    }
    else {
        Node* prevTo = nullptr;
        Node* nodeTo = this->last->next;
        for (int i = 0; i < idxTo; i++) {
            prevTo = nodeTo;
            nodeTo = nodeTo->next;
        }
        prevTo->next = nodeFrom;
        nodeFrom->next = nodeTo;
        if (nodeTo == nullptr) {
            this->last = nodeFrom;
        }
    }
}

template <typename T>
inline void CircularLinkedList<T>::replace(int one_idx, int second_idx) {
    if (one_idx < 0 || one_idx >= this->count || second_idx < 0 || second_idx >= this->count) {
        std::cerr << "Index out of range." << std::endl;
        return;
    }

    Node* node1 = this->last->next;
    for (int i = 0; i < one_idx; i++) {
        node1 = node1->next;
    }

    Node* node2 = this->last->next;
    for (int i = 0; i < second_idx; i++) {
        node2 = node2->next;
    }

    //tried data swap witch is simpler than pointer swap
    std::swap(node1->data, node2->data);
}


#endif // CIRCULARLINKEDLIST_H