#include "singly_linked_list.h"
#include <string.h>

void print_int(void* data) {
    printf("%d ", *(int*)data);
}

void print_float(void* data) {
    printf("%.2f ", *(float*)data);
}

void print_char(void* data) {
    printf("%c ", *(char*)data);
}

int cmp_int(void* a, void* b) {
    return *(int*)a - *(int*)b;
}

int cmp_float(void* a, void* b) {
    return (*(float*)a > *(float*)b) - (*(float*)a < *(float*)b);
}

int cmp_char(void* a, void* b) {
    return *(char*)a - *(char*)b;
}

int main() {
    Node* head = NULL;

    // Add integers to the list
    int a = 10, b = 20, c = 30, d = 40;
    add_node(&head, &a, sizeof(int));
    add_node(&head, &b, sizeof(int));
    add_node(&head, &c, sizeof(int));
    add_node(&head, &d, sizeof(int));

    printf("List after adding integers: ");
    print_list(head, print_int);
    printf("\n");

    // Insert an integer at index 2
    int e = 25;
    insert_at(&head, &e, sizeof(int), 2);
    printf("List after inserting 25 at index 2: ");
    print_list(head, print_int);
    printf("\n");

    // Remove an integer by value
    remove_node(&head, &b, sizeof(int), cmp_int);
    printf("List after removing 20: ");
    print_list(head, print_int);
    printf("\n");

    // Remove at index 1
    remove_at(&head, 1);
    printf("List after removing at index 1: ");
    print_list(head, print_int);
    printf("\n");

    // Reverse the list
    head = reverse_list(head);
    printf("List after reversing: ");
    print_list(head, print_int);
    printf("\n");

    // Move a node from index 1 to index 0
    move_node(&head, 1, 0);
    printf("List after moving node from index 1 to index 0: ");
    print_list(head, print_int);
    printf("\n");

    // Free the list
    free_list(head);

    // Add characters to the list
    head = NULL;
    char f = 'A', g = 'B', h = 'C';
    add_node(&head, &f, sizeof(char));
    add_node(&head, &g, sizeof(char));
    add_node(&head, &h, sizeof(char));

    printf("List after adding characters: ");
    print_list(head, print_char);
    printf("\n");

    // Reverse the list
    head = reverse_list(head);
    printf("List after reversing: ");
    print_list(head, print_char);
    printf("\n");

    free_list(head);

    return 0;
}
