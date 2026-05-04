#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

typedef struct Array Array;

struct Array {
    void* data;                       // Pointer to the array
    size_t data_size;                 // Size of each element
    int arr_size;                     // Number of elements in the array
};

Array* create_array(int size, size_t data_size);
void free_array(Array* arr);
void set(Array* self, int idx, void* new_value);
void* get(Array* self, int idx);

#endif // ARRAY_H
