#include "array.h"
#include <stdio.h>

int main() {
    int size = 10;
    Array* arr = create_array(size, sizeof(int));

    // Set values in the array using 'method-like' calls
    for (int i = 0; i < size; i++) {
        int value = i * 2;
        set(arr, i, &value);
    }

    // Get and print values from the array using 'method-like' calls
    for (int i = 0; i < size; i++) {
        int* value = (int*)get(arr, i);
        printf("%d\n", *value);
    }

    free_array(arr);
    return 0;
}
