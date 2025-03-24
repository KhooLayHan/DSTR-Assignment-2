#pragma once

#include <cstddef>
#include <iterator>
#include "../../utils/Assert.hpp"

namespace TCMS
{
    /**
     * @brief A base iterator class that provides common iterator functionality.
     * @tparam T The type of elements the iterator points to.
     * @tparam Category The iterator category (e.g., std::forward_iterator_tag).
     */
    template <typename T, typename Category>
    class Iterator {
    public:
        using iterator_category = Category; // Iterator category
        using ValueType = T;               // Type of the elements
        using DifferenceType = std::ptrdiff_t; // Difference type for pointer arithmetic
        using Pointer = T*;                // Pointer to an element
        using Reference = T&;              // Reference to an element

        /**
         * @brief Constructs an Iterator.
         * @param ptr Pointer to the current element.
         * @param begin Pointer to the beginning of the range.
         * @param end Pointer to the end of the range.
         */
        explicit Iterator(Pointer ptr, Pointer begin, Pointer end) 
            : m_Pointer(ptr), m_Begin(begin), m_End(end) {}

        /**
         * @brief Dereference operator.
         * @return A reference to the current element.
         * @throws std::runtime_error If the iterator is null or out of bounds.
         */
        Reference operator*() { 
            Assert::runtimeAssert(m_Pointer != nullptr, "Dereferencing nullptr iterator!");
            Assert::runtimeAssert(m_Pointer >= m_Begin && m_Pointer <= m_End, "Iterator dereferencing out of bounds!");
            return *m_Pointer; 
        }

        /**
         * @brief Arrow operator.
         * @return A pointer to the current element.
         * @throws std::runtime_error If the iterator is null.
         */
        Pointer operator->() { 
            Assert::runtimeAssert(m_Pointer != nullptr, "Accessing nullptr iterator!");
            return m_Pointer; 
        }

        /**
         * @brief Equality operator.
         * @param other The iterator to compare with.
         * @return True if the iterators point to the same element, false otherwise.
         */
        bool operator==(const Iterator& other) const noexcept { 
            return m_Pointer == other.m_Pointer; 
        }

        /**
         * @brief Inequality operator.
         * @param other The iterator to compare with.
         * @return True if the iterators point to different elements, false otherwise.
         */
        bool operator!=(const Iterator& other) const noexcept { 
            return m_Pointer != other.m_Pointer; 
        }

    protected:
        Pointer m_Pointer; // Pointer to the current element
        Pointer m_Begin;   // Pointer to the beginning of the range
        Pointer m_End;     // Pointer to the end of the range
    };
} // namespace TCMS