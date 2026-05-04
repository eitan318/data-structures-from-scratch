/**
 * @file bit_array.hpp
 * @brief Compact array of bits packed into machine words.
 */
#ifndef DS_BIT_ARRAY_HPP
#define DS_BIT_ARRAY_HPP

#include <cstddef>
#include <cstdint>
#include <stdexcept>

namespace ds {

/**
 * @brief Fixed-size array of bits backed by @c std::uint64_t words.
 *
 * Uses one bit of storage per element, giving 8x density over a
 * @c bool array. All operations are O(1).
 */
class BitArray {
public:
    /// Construct an array of @p size bits, all initialised to 0.
    explicit BitArray(std::size_t size)
        : size_(size),
          word_count_((size + bits_per_word - 1) / bits_per_word),
          data_(new std::uint64_t[word_count_ == 0 ? 1 : word_count_]()) {}

    ~BitArray() { delete[] data_; }

    BitArray(const BitArray&) = delete;
    BitArray& operator=(const BitArray&) = delete;

    /// Set bit at @p index to 1.
    void set(std::size_t index) {
        check(index);
        data_[index / bits_per_word] |= (uint64_t{1} << (index % bits_per_word));
    }

    /// Clear bit at @p index to 0.
    void clear(std::size_t index) {
        check(index);
        data_[index / bits_per_word] &= ~(uint64_t{1} << (index % bits_per_word));
    }

    /// Flip bit at @p index.
    void flip(std::size_t index) {
        check(index);
        data_[index / bits_per_word] ^= (uint64_t{1} << (index % bits_per_word));
    }

    /// Read bit at @p index.
    bool get(std::size_t index) const {
        check(index);
        return (data_[index / bits_per_word] >> (index % bits_per_word)) & 1u;
    }

    /// Number of bits in the array.
    std::size_t size() const noexcept { return size_; }

private:
    static constexpr std::size_t bits_per_word = 8 * sizeof(std::uint64_t);

    void check(std::size_t index) const {
        if (index >= size_) throw std::out_of_range("BitArray index out of range");
    }

    std::size_t size_;
    std::size_t word_count_;
    std::uint64_t* data_;
};

}  // namespace ds

#endif  // DS_BIT_ARRAY_HPP
