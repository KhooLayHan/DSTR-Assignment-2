#pragma once

namespace PerformanceEvaluation
{
    // Sourced from ChatGPT
    template <typename T>
    class Iterator {
        public:
            explicit Iterator(T* ptr) : m_Ptr(ptr) {}

            T& operator*() { 
                return *m_Ptr; 
            }

            T* operator->() { 
                return m_Ptr; 
            }
            
            // Prefix increment
            Iterator& operator++() { 
                ++m_Ptr; 
                return *this; 
            } 
            
            // Postfix increment
            Iterator operator++(int32_t) { 
                Iterator temp = *this;
                ++(*this); 
                return temp; 
            } 

            // Prefix increment
            Iterator& operator--() { 
                --m_Ptr; 
                return *this; 
            } 
            
            // Postfix increment
            Iterator operator--(int32_t) { 
                Iterator temp = *this;
                --(*this); 
                return temp; 
            } 

            // Addition (it + n)
            Iterator operator+(int n) const { 
                return Iterator(m_Ptr + n); 
            }

            // Subtraction (it - n)
            Iterator operator-(int n) const { 
                return Iterator(m_Ptr - n); 
            }

            // Difference between iterators (it2 - it1)
            int operator-(const Iterator& other) const { 
                return m_Ptr - other.m_Ptr; 
            }

            // Indexing (it[n])
            T& operator[](int index) const { 
                return *(m_Ptr + index); 
            }

            bool operator!=(const Iterator& other) const { return m_Ptr != other.m_Ptr; }
            bool operator==(const Iterator& other) const { return m_Ptr == other.m_Ptr; }
            bool operator< (const Iterator& other) const { return m_Ptr < other.m_Ptr; }
            bool operator> (const Iterator& other) const { return m_Ptr > other.m_Ptr; }
            bool operator<=(const Iterator& other) const { return m_Ptr <= other.m_Ptr; }
            bool operator>=(const Iterator& other) const { return m_Ptr >= other.m_Ptr; }
        private:
            T* m_Ptr;
    };
} // namespace PerformanceEvaluation
