// #pragma once

// #include "Iterator.hpp"

// namespace TCMS
// {
//     template <typename T>
//     class RandomAccessIterator : public Iterator<T, std::random_access_iterator_tag> {
//     public:
//         using Base = Iterator<T, std::random_access_iterator_tag>;
//         using typename Base::Pointer;
//         using typename Base::Reference;
//         using typename Base::DifferenceType;
        
//         explicit RandomAccessIterator(Pointer ptr, Pointer begin, Pointer end) : Base(ptr, begin, end) {

//         }

//         // Explicitly define the copy constructor
//         constexpr RandomAccessIterator(const RandomAccessIterator& other) = default;

//         // Explicitly define the copy assignment operator
//         constexpr RandomAccessIterator& operator=(const RandomAccessIterator& other) = default;

//         // constexpr RandomAccessIterator& operator=(RandomAccessIterator&& other) noexcept {
//         //     if (this != &other) {
//         //         Base::m_Pointer = other.m_Pointer;
//         //         other.m_Pointer = nullptr;
//         //     }

//         //     return *this;
//         // }

//         Reference operator*() { 
//             Assert::runtimeAssert(Base::m_Pointer != nullptr, "Dereferencing nullptr iterator!");
//             Assert::runtimeAssert(Base::m_Pointer >= Base::m_Begin && Base::m_Pointer <= Base::m_End, "Iterator dereferencing out of bounds!");
//             return *Base::m_Pointer; 
//         }
        
//         Pointer operator->() { 
//             Assert::runtimeAssert(Base::m_Pointer != nullptr, "Accessing nullptr iterator!");
//             return Base::m_Pointer; 
//         }

//         const Reference operator*() const { 
//             Assert::runtimeAssert(Base::m_Pointer != nullptr, "Dereferencing nullptr iterator!");
//             Assert::runtimeAssert(Base::m_Pointer >= Base::m_Begin && Base::m_Pointer <= Base::m_End, "Iterator dereferencing out of bounds!");
//             return *Base::m_Pointer; 
//         }
        
//         const Pointer operator->() const { 
//             Assert::runtimeAssert(Base::m_Pointer != nullptr, "Accessing nullptr iterator!");
//             return Base::m_Pointer; 
//         }

//         constexpr RandomAccessIterator& operator=(RandomAccessIterator&& other) noexcept {
//             if (this != &other) {
//                 Base::m_Pointer = other.m_Pointer;
//                 Base::m_Begin = other.m_Begin;
//                 Base::m_End = other.m_End;
//             }
            
//             return *this;
//         }

//         RandomAccessIterator& operator++() {
//             Assert::runtimeAssert(Base::m_Pointer + 1 <= Base::m_End, "Iterator increment out of bounds!");
//             ++Base::m_Pointer;
//             return *this;
//         }

//         RandomAccessIterator operator++(int) {
//             RandomAccessIterator temp = *this;
//             ++(*this);
//             return temp;
//         }

//         RandomAccessIterator& operator--() {
//             Assert::runtimeAssert(Base::m_Pointer - 1 >= Base::m_Begin, "Iterator decrement out of bounds!");
//             --Base::m_Pointer;
//             return *this;
//         }

//         RandomAccessIterator operator--(int) {
//             RandomAccessIterator temp = *this;
//             --(*this);
//             return temp;
//         }

//         RandomAccessIterator operator+(DifferenceType offset) const {
//             Assert::runtimeAssert(Base::m_Pointer + offset <= Base::m_End, "Iterator addition out of bounds!");
//             return RandomAccessIterator(Base::m_Pointer + offset, Base::m_Begin, Base::m_End);
//         } 

//         RandomAccessIterator operator-(DifferenceType offset) const {
//             Assert::runtimeAssert(Base::m_Pointer - offset >= Base::m_Begin, "Iterator subtraction out of bounds!");
//             return RandomAccessIterator(Base::m_Pointer - offset, Base::m_Begin, Base::m_End);
//         } 

//         DifferenceType operator-(const RandomAccessIterator& other) const {
//             Assert::runtimeAssert(Base::m_Begin == other.m_Begin && Base::m_End == other.m_End, 
//                 "Cannot subtract iterators from different ranges!");
//             return Base::m_Pointer - other.m_Pointer;
//         }
        
//         RandomAccessIterator& operator+=(DifferenceType offset) {
//             Assert::runtimeAssert(Base::m_Pointer + offset <= Base::m_End, "Iterator addition assignment out of bounds!");
//             Base::m_Pointer += offset;
//             return *this;
//         }

//         RandomAccessIterator& operator-=(DifferenceType offset) {
//             Assert::runtimeAssert(Base::m_Pointer - offset >= Base::m_Begin, "Iterator subtraction assignment out of bounds!");
//             Base::m_Pointer -= offset;
//             return *this;
//         }

//         Reference operator[](DifferenceType index) const {
//             Assert::runtimeAssert(index >= 0 && Base::m_Pointer + index <= Base::m_End, "Index out of bounds!");
//             Assert::runtimeAssert(Base::m_Pointer != nullptr, "Index null iterator!");
//             return *(Base::m_Pointer + index);
//         }

//         bool operator<(const RandomAccessIterator& other) const noexcept {
//             return Base::m_Pointer < other.m_Pointer;
//         }

//         bool operator>(const RandomAccessIterator& other) const noexcept {
//             return Base::m_Pointer > other.m_Pointer;
//         }

//         bool operator<=(const RandomAccessIterator& other) const noexcept {
//             return Base::m_Pointer <= other.m_Pointer;
//         }

//         bool operator>=(const RandomAccessIterator& other) const noexcept {
//             return Base::m_Pointer >= other.m_Pointer;
//         }
//     };
// } // namespace TCMS

// #pragma once

// #include "Iterator.hpp"
// #include <cassert>

// namespace TCMS {
//     template <typename T>
//     class RandomAccessIterator : public Iterator<T, std::random_access_iterator_tag> {
//     public:
//         using Base = Iterator<T, std::random_access_iterator_tag>;
//         using typename Base::Pointer;
//         using typename Base::Reference;
//         using typename Base::DifferenceType;

//         explicit RandomAccessIterator(Pointer ptr, Pointer begin, Pointer end)
//             : Base(ptr, begin, end) {}

//         // Copy & Move Constructors
//         constexpr RandomAccessIterator(const RandomAccessIterator& other) = default;
//         constexpr RandomAccessIterator(RandomAccessIterator&& other) noexcept = default;

//         // Assignment Operators
//         constexpr RandomAccessIterator& operator=(const RandomAccessIterator& other) = default;
//         constexpr RandomAccessIterator& operator=(RandomAccessIterator&& other) noexcept = default;

//         // Dereferencing Operators
//         Reference operator*() const {
//             assert(Base::m_Pointer != nullptr && "Dereferencing nullptr!");
//             assert(Base::m_Pointer >= Base::m_Begin && Base::m_Pointer < Base::m_End && "Out of bounds!");
//             return *Base::m_Pointer;
//         }

//         Pointer operator->() const { return Base::m_Pointer; }

//         // Increment & Decrement Operators
//         RandomAccessIterator& operator++() {
//             assert(Base::m_Pointer + 1 <= Base::m_End && "Iterator increment out of bounds!");
//             ++Base::m_Pointer;
//             return *this;
//         }

//         RandomAccessIterator operator++(int) {
//             RandomAccessIterator temp = *this;
//             ++(*this);
//             return temp;
//         }

//         RandomAccessIterator& operator--() {
//             assert(Base::m_Pointer - 1 >= Base::m_Begin && "Iterator decrement out of bounds!");
//             --Base::m_Pointer;
//             return *this;
//         }

//         RandomAccessIterator operator--(int) {
//             RandomAccessIterator temp = *this;
//             --(*this);
//             return temp;
//         }

//         // Arithmetic Operators
//         RandomAccessIterator operator+(DifferenceType offset) const {
//             assert(Base::m_Pointer + offset <= Base::m_End && "Addition out of bounds!");
//             return RandomAccessIterator(Base::m_Pointer + offset, Base::m_Begin, Base::m_End);
//         }

//         RandomAccessIterator operator-(DifferenceType offset) const {
//             assert(Base::m_Pointer - offset >= Base::m_Begin && "Subtraction out of bounds!");
//             return RandomAccessIterator(Base::m_Pointer - offset, Base::m_Begin, Base::m_End);
//         }

//         DifferenceType operator-(const RandomAccessIterator& other) const {
//             assert(Base::m_Begin == other.m_Begin && Base::m_End == other.m_End && "Iterator subtraction across different ranges!");
//             return Base::m_Pointer - other.m_Pointer;
//         }

//         RandomAccessIterator& operator+=(DifferenceType offset) {
//             assert(Base::m_Pointer + offset <= Base::m_End && "Addition assignment out of bounds!");
//             Base::m_Pointer += offset;
//             return *this;
//         }

//         RandomAccessIterator& operator-=(DifferenceType offset) {
//             assert(Base::m_Pointer - offset >= Base::m_Begin && "Subtraction assignment out of bounds!");
//             Base::m_Pointer -= offset;
//             return *this;
//         }

//         // Element Access
//         Reference operator[](DifferenceType index) const {
//             assert(index >= 0 && Base::m_Pointer + index < Base::m_End && "Index out of bounds!");
//             return *(Base::m_Pointer + index);
//         }

//         // Comparison Operators
//         bool operator==(const RandomAccessIterator& other) const noexcept { return Base::m_Pointer == other.m_Pointer; }
//         bool operator!=(const RandomAccessIterator& other) const noexcept { return Base::m_Pointer != other.m_Pointer; }
//         bool operator<(const RandomAccessIterator& other) const noexcept { return Base::m_Pointer < other.m_Pointer; }
//         bool operator>(const RandomAccessIterator& other) const noexcept { return Base::m_Pointer > other.m_Pointer; }
//         bool operator<=(const RandomAccessIterator& other) const noexcept { return Base::m_Pointer <= other.m_Pointer; }
//         bool operator>=(const RandomAccessIterator& other) const noexcept { return Base::m_Pointer >= other.m_Pointer; }
//     };
// } // namespace TCMS


#pragma once

#include <iterator>
#include <cassert>

namespace TCMS {
    template <typename T>
    class RandomAccessIterator {
    public:
        using ValueType = T;
        using Pointer = T*;
        using Reference = T&;
        using DifferenceType = std::ptrdiff_t;
        using IteratorCategory = std::random_access_iterator_tag;

        explicit RandomAccessIterator(Pointer ptr, Pointer begin, Pointer end) 
            : m_Pointer(ptr), m_Begin(begin), m_End(end) {}

        // Dereference
        Reference operator*() const {
            assert(m_Pointer != nullptr && "Dereferencing nullptr iterator!");
            return *m_Pointer;
        }

        // Arrow operator
        Pointer operator->() const { return m_Pointer; }

        // Pre-increment
        RandomAccessIterator& operator++() {
            assert(m_Pointer + 1 <= m_End && "Out of bounds!");
            ++m_Pointer;
            return *this;
        }

        // Post-increment
        RandomAccessIterator operator++(int) {
            RandomAccessIterator temp = *this;
            ++(*this);
            return temp;
        }

        // Pre-decrement
        RandomAccessIterator& operator--() {
            assert(m_Pointer - 1 >= m_Begin && "Out of bounds!");
            --m_Pointer;
            return *this;
        }

        // Post-decrement
        RandomAccessIterator operator--(int) {
            RandomAccessIterator temp = *this;
            --(*this);
            return temp;
        }

        // Arithmetic operations
        RandomAccessIterator operator+(DifferenceType offset) const { return RandomAccessIterator(m_Pointer + offset, m_Begin, m_End); }
        RandomAccessIterator operator-(DifferenceType offset) const { return RandomAccessIterator(m_Pointer - offset, m_Begin, m_End); }
        DifferenceType operator-(const RandomAccessIterator& other) const { return m_Pointer - other.m_Pointer; }

        RandomAccessIterator& operator+=(DifferenceType offset) {
            m_Pointer += offset;
            return *this;
        }
        RandomAccessIterator& operator-=(DifferenceType offset) {
            m_Pointer -= offset;
            return *this;
        }

        // Indexing
        Reference operator[](DifferenceType index) const { return *(m_Pointer + index); }

        // Comparisons
        bool operator==(const RandomAccessIterator& other) const { return m_Pointer == other.m_Pointer; }
        bool operator!=(const RandomAccessIterator& other) const { return m_Pointer != other.m_Pointer; }
        bool operator<(const RandomAccessIterator& other) const { return m_Pointer < other.m_Pointer; }
        bool operator>(const RandomAccessIterator& other) const { return m_Pointer > other.m_Pointer; }
        bool operator<=(const RandomAccessIterator& other) const { return m_Pointer <= other.m_Pointer; }
        bool operator>=(const RandomAccessIterator& other) const { return m_Pointer >= other.m_Pointer; }

    private:
        Pointer m_Pointer;
        Pointer m_Begin;
        Pointer m_End;
    };
}
