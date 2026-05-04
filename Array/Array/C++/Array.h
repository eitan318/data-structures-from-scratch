#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

template <typename T>
class Array {
public:
    Array(int capacity);
    ~Array();

    // Accessor
    T& operator[](int index);
    const T& operator[](int index) const;

    // Get length
    int length() const;

private:
    T* data;
    int capacity;
};

#endif // !ARRAY_H

template <typename T>
Array<T>::Array(int capacity) : capacity(capacity) {
    if (capacity <= 0) {
        throw std::invalid_argument("Length must be positive");
    }
    data = new T[capacity]; // Allocate memory for the array
}

template <typename T>
Array<T>::~Array() {
    delete[] data;
}

template <typename T>
int Array<T>::length() const{
    return this->capacity;
}

template <typename T>
const T& Array<T>::operator[](int index) const {
    if (index < 0 || index >= capacity) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

template <typename T>
T& Array<T>::operator[](int index) {
    if (index < 0 || index >= capacity) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}