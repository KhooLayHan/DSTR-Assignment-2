#pragma once

#include "Iterator.hpp"

namespace TCMS
{
    template <typename T>
    class RandomAccessIterator : public Iterator<T, std::random_access_iterator_tag> {
    public:
        using Base = Iterator<T, std::random_access_iterator_tag>;
        using typename Base::Pointer;
        using typename Base::Reference;
        using typename Base::DifferenceType;
        
        explicit RandomAccessIterator(Pointer ptr, Pointer begin, Pointer end) : Base(ptr, begin, end) {

        }

        RandomAccessIterator& operator++() {
            Assert::runtimeAssert(Base::m_Pointer + 1 <= Base::m_End, "Iterator increment out of bounds!");
            ++Base::m_Pointer;
            return *this;
        }

        RandomAccessIterator operator++(int) {
            RandomAccessIterator temp = *this;
            ++(*this);
            return temp;
        }

        RandomAccessIterator& operator--() {
            Assert::runtimeAssert(Base::m_Pointer - 1 >= Base::m_Begin, "Iterator decrement out of bounds!");
            --Base::m_Pointer;
            return *this;
        }

        RandomAccessIterator operator--(int) {
            RandomAccessIterator temp = *this;
            --(*this);
            return temp;
        }

        RandomAccessIterator operator+(DifferenceType offset) const {
            Assert::runtimeAssert(Base::m_Pointer + offset <= Base::m_End, "Iterator addition out of bounds!");
            return RandomAccessIterator(Base::m_Pointer + offset, Base::m_Begin, Base::m_End);
        } 

        RandomAccessIterator operator-(DifferenceType offset) const {
            Assert::runtimeAssert(Base::m_Pointer - offset >= Base::m_Begin, "Iterator subtraction out of bounds!");
            return RandomAccessIterator(Base::m_Pointer - offset, Base::m_Begin, Base::m_End);
        } 

        DifferenceType operator-(const RandomAccessIterator& other) const {
            Assert::runtimeAssert(Base::m_Begin == other.m_Begin && Base::m_End == other.m_End, 
                "Cannot subtract iterators from different ranges!");
            return Base::m_Pointer - other.m_Pointer;
        }
        
        RandomAccessIterator& operator+=(DifferenceType offset) {
            Assert::runtimeAssert(Base::m_Pointer + offset <= Base::m_End && "Iterator addition assignment out of bounds!");
            Base::m_Pointer += offset;
            return *this;
        }

        RandomAccessIterator& operator-=(DifferenceType offset) {
            Assert::runtimeAssert(Base::m_Pointer - offset >= Base::m_Begin && "Iterator subtraction assignment out of bounds!");
            Base::m_Pointer -= offset;
            return *this;
        }

        Reference operator[](DifferenceType index) const {
            Assert::runtimeAssert(index >= 0 && Base::m_Pointer + index <= Base::m_End, "Index out of bounds!");
            Assert::runtimeAssert(Base::m_Pointer != nullptr, "Index null iterator!");
            return *(Base::m_Pointer + index);
        }

        bool operator<(const RandomAccessIterator& other) const noexcept {
            return Base::m_Pointer < other.m_Pointer;
        }

        bool operator>(const RandomAccessIterator& other) const noexcept {
            return Base::m_Pointer > other.m_Pointer;
        }

        bool operator<=(const RandomAccessIterator& other) const noexcept {
            return Base::m_Pointer <= other.m_Pointer;
        }

        bool operator>=(const RandomAccessIterator& other) const noexcept {
            return Base::m_Pointer >= other.m_Pointer;
        }
    };
} // namespace TCMS
