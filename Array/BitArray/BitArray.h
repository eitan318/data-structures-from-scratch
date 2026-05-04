#ifndef BITARRAY_H
#define BITARRAY_H

#include <cstdint>  // For uint32_t or uint64_t
#include <stdexcept> // For std::out_of_range

class BitArray {
public:
    BitArray(size_t size) : size_(size) {
        // Determine the number of integer elements needed
        this->data_size_ = (size + bits_per_int - 1) / bits_per_int;
        this->data_ = new uint32_t[data_size_]();
    }

    ~BitArray() {
        delete[] data_;
    }

    void set(size_t index) {
        check_index(index);
        data_[index / bits_per_int] |= (1 << (index % bits_per_int));
    }

    void clear(size_t index) {
        check_index(index);
        data_[index / bits_per_int] &= ~(1 << (index % bits_per_int));
    }

    bool get(size_t index) const {
        check_index(index);
        return (data_[index / bits_per_int] >> (index % bits_per_int)) & 1;
    }


    size_t size() const {
        return size_;
    }

private:
    void check_index(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
    }

    uint32_t* data_;
    size_t size_;
    size_t data_size_;
    static const size_t bits_per_int = 8 * sizeof(uint32_t);
};

#endif // BITARRAY_H
