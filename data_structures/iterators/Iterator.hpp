#pragma once

#include <cstddef>
#include <iterator>

#include "../../utils/Assert.hpp"

namespace TCMS
{
    template <typename T, typename Category>
    class Iterator {
    public:
        using iterator_category = Category;
        using ValueType = T;
        using DifferenceType = std::ptrdiff_t;
        using Pointer = T*;
        using Reference = T&;
    
        explicit Iterator(Pointer ptr, Pointer begin, Pointer end) : m_Pointer(ptr), m_Begin(begin), m_End(end) {

        }

        Reference operator*() { 
            Assert::runtimeAssert(m_Pointer != nullptr, "Dereferencing nullptr iterator!");
            Assert::runtimeAssert(m_Pointer >= m_Begin && m_Pointer <= m_End, "Iterator dereferencing out of bounds!");
            return *m_Pointer; 
        }
        
        Pointer operator->() { 
            Assert::runtimeAssert(m_Pointer != nullptr, "Accessing nullptr iterator!");
            return m_Pointer; 
        }

        bool operator==(const Iterator& other) const noexcept { return m_Pointer == other.m_Pointer; }
        bool operator!=(const Iterator& other) const noexcept { return m_Pointer != other.m_Pointer; }
    protected:
        Pointer m_Pointer;

        Pointer m_Begin;
        Pointer m_End; 
    };
} // namespace TCMS
