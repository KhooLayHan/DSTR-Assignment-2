#pragma once

#include <cassert>
#include <iostream>
#include <memory>
#include <string>

#include "./Iterator.hpp"

namespace PerformanceEvaluation
{
    // Implementation of DynamicArray that requires manual resizing unlike Vector
    template <typename T>
    class DynamicArray {
        public:
            DynamicArray(size_t initial_capacity = 2500) : m_Capacity(initial_capacity), m_Length(0) {
                m_Data = new T[m_Capacity];
            }

            // Resize the array when needed by doubling the capacity)
            void Resize(size_t capacity) {
                if (capacity < m_Length)
                    capacity = m_Length; // Prevents data loss when shrinking
                
                T* data = new T[capacity]();

                for (size_t i = 0; i != m_Length; i++) {
                    data[i] = std::move(m_Data[i]);
                }

                delete[] m_Data;
                
                m_Data = data;
                m_Capacity = capacity;
            }

            // Insert at index
            void Insert(size_t index, const T& value) {
                if (index >= m_Capacity)
                    Resize(m_Capacity * 2); // Grow as needed
                
                m_Data[index] = value;

                if (index >= m_Length)
                    m_Length = index + 1;
            }

            // Remove element at index
            void Remove(size_t index) {
                assert(index < m_Length && "Index specified is out of bounds!");

                for (size_t i = index; i < m_Length - 1; i++) 
                    m_Data[i] = std::move(m_Data[i + 1]); // Shifts left
                    
                --m_Length;
            }

            // Access elements
            constexpr T& operator[](size_t index) noexcept {
                if (index >= m_Capacity) {
                    Resize(index + 1);
                }
                if (index >= m_Length) {
                    m_Length = index + 1;
                }
                return m_Data[index];
            }

            constexpr const T& operator[](size_t index) const noexcept {
                if (index > m_Length)
                    assert(index <= m_Length && "Index specified is out of bounds!");
                
                return m_Data[index];
            }

            size_t GetLength() const {
                return m_Length;
            }

            size_t GetCapacity() const {
                return m_Capacity;
            }

            Iterator<T> begin() { return Iterator<T>(m_Data); }
            Iterator<T> end() { return Iterator<T>(m_Data + m_Length); }

            ~DynamicArray() {
                delete[] m_Data;
                m_Data = nullptr; 
            }
        private:
            T* m_Data;
            size_t m_Capacity;
            size_t m_Length;
    };
} // namespace PerformanceEvaluation
