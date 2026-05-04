#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* get(Array* self, int idx) {
    if (idx >= self->arr_size) {
        printf("error\n");
        return NULL;
    }
    return (void*)((char*)self->data + idx * self->data_size);
}

void set(Array* self, int idx, void* new_value) {
    if (idx >= self->arr_size) {
        printf("error\n");
        return;
    }
    void* target = (void*)((char*)self->data + idx * self->data_size);
    memcpy(target, new_value, self->data_size);
}

Array* create_array(int size, size_t data_size) {
    Array* arr = (Array*)malloc(sizeof(Array));
    arr->data = (void*)malloc(size * data_size);
    arr->data_size = data_size;
    arr->arr_size = size;

    return arr;
}

void free_array(Array* arr) {
    free(arr->data);
    free(arr);
}
