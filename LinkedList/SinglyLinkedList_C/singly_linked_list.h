#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    void* data;
    struct Node* next;
} Node;


Node* create_node(void* data, size_t data_size);
Node* create_int(int value);
Node* create_float(float value);
Node* create_char(Node** head, char value);
void add_node_start(Node** head, void* data, size_t data_size);
void print_list(Node* head, void (*print_func)(void*));
void remove_node(Node** head, void* data, size_t data_size, int (*cmp_func)(void*, void*));
void remove_at(Node** head, int idx);
void add_node(Node** head, void* data, size_t data_size);
void insert_at(Node** head, void* data, size_t data_size, int idx);
Node* reverse_list(Node* head);
void move_node(Node** head, int idxFrom, int idxTo);
void free_list(Node* head);
