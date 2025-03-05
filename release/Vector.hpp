#pragma once

#include <cassert>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <utility>

namespace PerformanceEvaluation
{
    template <typename T>
    class Vector {
        public:
            using difference_type = std::ptrdiff_t; // Required for std::distance
            // using iterator_category = std::forward_iterator_tag; // Or bidirectional/random access if extended
            
            Vector() : m_Length(0), m_Capacity(1) {
                m_Data = new T[m_Capacity];
            }

            Vector(std::initializer_list<T> init_list)
                : m_Length(init_list.size()), m_Capacity(init_list.size()) {
                m_Data = new T[m_Capacity];

                size_t i = 0;
                for (const auto& item : init_list) {
                    m_Data[i++] = item;
                }
            }

            // New range-based constructor
            template <typename InputIt>
            Vector(InputIt first, InputIt last) {
                int count = 0;
                for (auto it = first; it != last; ++it) {
                    count++;
                }

                // m_Length = std::distance(first, last);
                m_Length = count;
                m_Capacity = m_Length;
                m_Data = new T[m_Capacity];

                size_t i = 0;
                for (auto it = first; it != last; ++it) {
                    m_Data[i++] = *it;
                }
            }

            ~Vector() {
                delete[] m_Data;
            }

            // Copy constructors
            Vector(const Vector& other) noexcept : m_Length(other.m_Length), m_Capacity(other.m_Capacity) {
                m_Data = new T[m_Capacity];

                for (size_t i = 0; i != m_Length; i++) {
                    m_Data[i] = other.m_Data[i];
                }
            } 

            // Move constructors
            Vector(Vector&& other) noexcept : m_Data(other.m_Data), m_Length(other.m_Length), m_Capacity(other.m_Capacity) {
                other.m_Data = nullptr;
                other.m_Length = 0;
                other.m_Capacity = 0;
            } 

            // Copy assignment
            constexpr Vector& operator=(const Vector<T>& other) noexcept {
                if (this != &other) { // Self-assignment check
                    delete[] m_Data; // Free current memory
                    
                    m_Length = other.m_Length;
                    m_Capacity = other.m_Capacity;
                    m_Data = new T[m_Capacity];
                    
                    for (size_t i = 0; i != m_Length; i++) 
                        m_Data[i] = other.m_Data[i];
                }

                return *this;
            }

            // Move assignment
            constexpr Vector& operator=(Vector<T>&& other) noexcept {
                if (this != &other) { // Self-assignment check
                    delete[] m_Data; // Free current memory
                    
                    m_Data = other.m_Data;
                    m_Length = other.m_Length;
                    m_Capacity = other.m_Capacity;
                    // m_Data = new T[m_Capacity];
                    
                    other.m_Data = nullptr; // Null the other vector's data
                    other.m_Length = 0; 
                    other.m_Capacity = 0; 
                }
                
                return *this;
            }

            // constexpr const Vector& operator=(T&& other) const noexcept {
            //     if (this != &other) { // Self-assignment check
            //         delete[] m_Data; // Free current memory
                    
            //         m_Length = other.m_Length;
            //         m_Capacity = other.m_Capacity;
            //         m_Data = new T[m_Capacity];
                    
            //         other.m_Data = nullptr; // Null the other vector's data
            //         other.m_Length = 0; 
            //         other.m_Capacity = 0; 
            //     }
                
            //     return *this;
            // }

            // Overloading [] operator
            constexpr T& operator[](size_t index) noexcept {
                if (index >= m_Capacity) 
                    Resize(index + 1); // Ensures capacity is sufficient
                if (index >= m_Length) 
                    m_Length = index + 1; // Adjusts length to include new index
                
                return m_Data[index];
            }
            
            constexpr const T& operator[](size_t index) const noexcept {
                if (index > m_Length)
                    assert(index <= m_Length && "Index specified is out of bounds!");
                
                return m_Data[index];
            }

            void Clear() noexcept {
                m_Length = 0;
            }
            
            constexpr bool IsEmpty() const noexcept {
                return m_Length == 0;
            }

            constexpr size_t GetCapacity() const noexcept {
                return m_Capacity;
            } 

            constexpr size_t GetLength() const noexcept {
                return m_Length;
            } 

            void PushBack(const T& value) {
                if (m_Length == m_Capacity)
                    Resize(m_Capacity * 2);

                m_Data[m_Length] = value;
                m_Length++;
            }

            // Sourced from ChatGPT
            template <typename... Args>
            void EmplaceBack(Args&&... args) {
                if (m_Length == m_Capacity)
                    Resize(m_Capacity * 2);

                // Constructs the elements in place at the end of the vector
                ::new(&m_Data[m_Length]) T(std::forward<Args>(args)...);

                m_Length++;
            }

            void PopBack() noexcept {
                if (m_Length > 0)
                    m_Length--;
            }
            
            void Reserve(size_t capacity) {
                if (capacity > m_Capacity)
                    Resize(capacity);
            }

            void Resize(size_t capacity) {
                assert(capacity >= m_Length && "New capacity must be greater than current length!");

                T* data = new T[capacity];

                for (size_t i = 0; i != m_Length; i++) {
                    data[i] = std::move(m_Data[i]);
                }

                delete[] m_Data;

                m_Data = data;
                m_Capacity = capacity;
            }

            constexpr T* GetData() noexcept {
                return m_Data;
            } 

            constexpr const T* GetData() const noexcept {
                return m_Data;
            } 

            struct Iterator {
                using iterator_category = std::random_access_iterator_tag;
                using value_type = T;
                using difference_type = std::ptrdiff_t;
                using pointer = T*;
                using reference = T&;

                T* m_Pointer;

                explicit Iterator(T* pointer) : m_Pointer(pointer) {}

                reference operator*() {
                    return *m_Pointer;
                }

                pointer operator->() {
                    return m_Pointer;
                }

                // Prefix increment
                Iterator& operator++() {
                    ++m_Pointer;
                    return *this;
                }

                // Postfix increment
                Iterator operator++(int) {
                    Iterator temp = *this;
                    ++(*this);
                    return temp;
                }

                // Prefix decrement
                Iterator& operator--() {
                    --m_Pointer;
                    return *this;
                }

                // Postfix decrement
                Iterator operator--(int) {
                    Iterator temp = *this;
                    --(*this);
                    return temp;
                }

                // Iterator arithmetic
                Iterator operator+(difference_type offset) const {
                    return Iterator(m_Pointer + offset);
                }

                Iterator operator-(difference_type offset) const {
                    return Iterator(m_Pointer - offset);
                }

                difference_type operator-(const Iterator& other) const {
                    return m_Pointer - other.m_Pointer;
                }

                Iterator& operator+=(difference_type offset) {
                    m_Pointer += offset;
                    return *this;
                }

                Iterator& operator-=(difference_type offset) {
                    m_Pointer -= offset;
                    return *this;
                }

                reference operator[](difference_type index) const {
                    return *(m_Pointer + index);
                }

                bool operator!=(const Iterator& other) const noexcept {
                    return m_Pointer != other.m_Pointer;
                }

                bool operator==(const Iterator& other) const noexcept {
                    return m_Pointer == other.m_Pointer;
                }

                bool operator<(const Iterator& other) const noexcept {
                    return m_Pointer < other.m_Pointer;
                }

                bool operator>(const Iterator& other) const noexcept {
                    return m_Pointer > other.m_Pointer;
                }

                bool operator<=(const Iterator& other) const noexcept {
                    return m_Pointer <= other.m_Pointer;
                }

                bool operator>=(const Iterator& other) const noexcept {
                    return m_Pointer >= other.m_Pointer;
                }
            };

            Iterator begin() noexcept {
                return Iterator(m_Data);
            }

            Iterator end() noexcept {
                return Iterator(m_Data + m_Length);
            }
            
            Iterator begin() const noexcept {
                return Iterator(m_Data);
            }

            Iterator end() const noexcept {
                return Iterator(m_Data + m_Length);
            }

        private:
            T* m_Data;
            size_t m_Length;
            size_t m_Capacity; 
    };    
} // namespace PerformanceEvaluation
