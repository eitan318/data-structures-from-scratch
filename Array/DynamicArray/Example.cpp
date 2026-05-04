#include "DynamicArray.h"
#include <iostream>

int main() {
    // Create a DynamicArray of integers with a default capacity of 10
    DynamicArray<int> arr;

    // Add elements to the array
    arr.add(1);
    arr.add(2);
    arr.add(3);
    arr.add(4);
    arr.add(5);

    // Print the array
    std::cout << "Array after adding elements: ";
    for (int i = 0; i < 5; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Insert an element at a specific index
    arr.insert(2, 99);
    std::cout << "Array after inserting 99 at index 2: ";
    for (int i = 0; i < 6; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Remove an element by value
    arr.remove(3);
    std::cout << "Array after removing element 3: ";
    for (int i = 0; i < 5; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Search for an element
    int index = arr.search(99);
    std::cout << "Element 99 found at index: " << index << std::endl;

    // Check if the array is empty
    if (arr.isEmpty()) {
        std::cout << "Array is empty." << std::endl;
    }
    else {
        std::cout << "Array is not empty." << std::endl;
    }

    return 0;
}
