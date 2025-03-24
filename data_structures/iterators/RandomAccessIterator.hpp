#pragma once

#include <iterator>
#include <cassert>

namespace TCMS {
    /**
     * @brief A random access iterator that supports bidirectional traversal and random access.
     * @tparam T The type of elements the iterator points to.
     */
    template <typename T>
    class RandomAccessIterator {
    public:
        using ValueType = T;                       // Type of the elements
        using Pointer = T*;                        // Pointer to an element
        using Reference = T&;                      // Reference to an element
        using DifferenceType = std::ptrdiff_t;     // Difference type for pointer arithmetic
        using IteratorCategory = std::random_access_iterator_tag; // Iterator category

        /**
         * @brief Constructs a RandomAccessIterator.
         * @param ptr Pointer to the current element.
         * @param begin Pointer to the beginning of the range.
         * @param end Pointer to the end of the range.
         */
        explicit RandomAccessIterator(Pointer ptr, Pointer begin, Pointer end) 
            : m_Pointer(ptr), m_Begin(begin), m_End(end) {}

        /**
         * @brief Dereference operator.
         * @return A reference to the current element.
         * @throws std::runtime_error If the iterator is null.
         */
        Reference operator*() const {
            assert(m_Pointer != nullptr && "Dereferencing nullptr iterator!");
            return *m_Pointer;
        }

        /**
         * @brief Arrow operator.
         * @return A pointer to the current element.
         */
        Pointer operator->() const { return m_Pointer; }

        /**
         * @brief Pre-increment operator.
         * @return A reference to the updated iterator.
         * @throws std::runtime_error If incrementing goes out of bounds.
         */
        RandomAccessIterator& operator++() {
            assert(m_Pointer + 1 <= m_End && "Out of bounds!");
            ++m_Pointer;
            return *this;
        }

        /**
         * @brief Post-increment operator.
         * @return A copy of the iterator before incrementing.
         */
        RandomAccessIterator operator++(int) {
            RandomAccessIterator temp = *this;
            ++(*this);
            return temp;
        }

        /**
         * @brief Pre-decrement operator.
         * @return A reference to the updated iterator.
         * @throws std::runtime_error If decrementing goes out of bounds.
         */
        RandomAccessIterator& operator--() {
            assert(m_Pointer - 1 >= m_Begin && "Out of bounds!");
            --m_Pointer;
            return *this;
        }

        /**
         * @brief Post-decrement operator.
         * @return A copy of the iterator before decrementing.
         */
        RandomAccessIterator operator--(int) {
            RandomAccessIterator temp = *this;
            --(*this);
            return temp;
        }

        /**
         * @brief Addition operator.
         * @param offset The number of positions to move forward.
         * @return A new iterator pointing to the new position.
         */
        RandomAccessIterator operator+(DifferenceType offset) const {
            return RandomAccessIterator(m_Pointer + offset, m_Begin, m_End);
        }

        /**
         * @brief Subtraction operator.
         * @param offset The number of positions to move backward.
         * @return A new iterator pointing to the new position.
         */
        RandomAccessIterator operator-(DifferenceType offset) const {
            return RandomAccessIterator(m_Pointer - offset, m_Begin, m_End);
        }

        /**
         * @brief Difference operator.
         * @param other The iterator to subtract from this one.
         * @return The distance between the two iterators.
         */
        DifferenceType operator-(const RandomAccessIterator& other) const {
            return m_Pointer - other.m_Pointer;
        }

        /**
         * @brief Addition assignment operator.
         * @param offset The number of positions to move forward.
         * @return A reference to the updated iterator.
         */
        RandomAccessIterator& operator+=(DifferenceType offset) {
            m_Pointer += offset;
            return *this;
        }

        /**
         * @brief Subtraction assignment operator.
         * @param offset The number of positions to move backward.
         * @return A reference to the updated iterator.
         */
        RandomAccessIterator& operator-=(DifferenceType offset) {
            m_Pointer -= offset;
            return *this;
        }

        /**
         * @brief Indexing operator.
         * @param index The offset from the current position.
         * @return A reference to the element at the specified offset.
         */
        Reference operator[](DifferenceType index) const {
            return *(m_Pointer + index);
        }

        /**
         * @brief Equality operator.
         * @param other The iterator to compare with.
         * @return True if the iterators point to the same element, false otherwise.
         */
        bool operator==(const RandomAccessIterator& other) const {
            return m_Pointer == other.m_Pointer;
        }

        /**
         * @brief Inequality operator.
         * @param other The iterator to compare with.
         * @return True if the iterators point to different elements, false otherwise.
         */
        bool operator!=(const RandomAccessIterator& other) const {
            return m_Pointer != other.m_Pointer;
        }

        /**
         * @brief Less-than operator.
         * @param other The iterator to compare with.
         * @return True if this iterator points to an earlier element, false otherwise.
         */
        bool operator<(const RandomAccessIterator& other) const {
            return m_Pointer < other.m_Pointer;
        }

        /**
         * @brief Greater-than operator.
         * @param other The iterator to compare with.
         * @return True if this iterator points to a later element, false otherwise.
         */
        bool operator>(const RandomAccessIterator& other) const {
            return m_Pointer > other.m_Pointer;
        }

        /**
         * @brief Less-than-or-equal operator.
         * @param other The iterator to compare with.
         * @return True if this iterator points to an earlier or the same element, false otherwise.
         */
        bool operator<=(const RandomAccessIterator& other) const {
            return m_Pointer <= other.m_Pointer;
        }

        /**
         * @brief Greater-than-or-equal operator.
         * @param other The iterator to compare with.
         * @return True if this iterator points to a later or the same element, false otherwise.
         */
        bool operator>=(const RandomAccessIterator& other) const {
            return m_Pointer >= other.m_Pointer;
        }

    private:
        Pointer m_Pointer; // Pointer to the current element
        Pointer m_Begin;   // Pointer to the beginning of the range
        Pointer m_End;     // Pointer to the end of the range
    };
} // namespace TCMS