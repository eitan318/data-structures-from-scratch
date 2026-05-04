#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <iostream>
#include <stdbool.h>

template <typename T>
class DynamicArray {
public:
    DynamicArray(int capacity = 10); // Default capacity is set here
    ~DynamicArray();

    // Accessors
    T& operator[](int index);
    const T& operator[](int index) const;

    void add(T data);
    void insert(int idx, T data);
    void remove(T data);
    int search(T data);
    bool isEmpty();


private:
    int capacity;  // Maximum capacity of the array
    int size;       // Number of elements in the array
    T* array;      // Pointer to dynamically allocated array

    void grow();
    void shrink();
};

#endif // !DYNAMICARRAY_H


template <typename T>
DynamicArray<T>::DynamicArray(int capacity) : capacity(capacity), size(0) {
    if (capacity <= 0) {
        throw std::invalid_argument("Capacity must be positive");
    }
    this->array = new T[capacity]; // Allocate memory for the array
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] this->array; // Deallocate memory for the array
}

template <typename T>
const T& DynamicArray<T>::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return array[index];
}

template <typename T>
T& DynamicArray<T>::operator[](int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return array[index];
}



template<typename T>
inline void DynamicArray<T>::add(T data)
{
    if (this->size >= this->capacity) {
        this->grow();
    }
    this->array[size] = data;
    this->size++;
}

template<typename T>
inline void DynamicArray<T>::insert(int idx, T data)
{
    if (this->size >= this->capacity) {
        this->grow();
    }
    for (int i = size; i > idx; i--) {
        this->array[i] = this->array[i - 1];
    }
    this->array[idx] = data;
    this->size++;
}

template<typename T>
inline void DynamicArray<T>::remove(T data)
{
    for (int i = 0; i < this->size; i++) {
        if (this->array[i] == data) {
            for (;i < this->size - 1; i++) {
                this->array[i] = this->array[i + 1];
            }
            this->array[i] = NULL;
            this->size--;
            if (this->size <= this->capacity / 3) {
                this->shrink();
            }
            return;
        }
    }

}

template<typename T>
inline int DynamicArray<T>::search(T data)
{
    for (int i = 0; i < this->size; i++) {
        if (this->array[i] == data) {
            return i;
        }
    }
}

template<typename T>
inline bool DynamicArray<T>::isEmpty()
{
    return this->size == 0;
}

template<typename T>
inline void DynamicArray<T>::grow()
{
    int new_capacity = this->capacity * 2;
    T* new_array = new T[new_capacity];
    for (int i = 0; i < size; i++) {
        new_array[i] = this->array[i];
    }
    this->array = new_array;
}

template<typename T>
inline void DynamicArray<T>::shrink()
{
    int new_capacity = this->capacity / 2;
    T* new_array = new T[new_capacity];
    for (int i = 0; i < size; i++) {
        new_array[i] = this->array[i];
    }
    this->array = new_array;
}
