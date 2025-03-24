#pragma once

#include <cassert>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <utility>

#include "../utils/Assert.hpp"
#include "./iterators/RandomAccessIterator.hpp"

namespace TCMS
{
    /**
     * @brief A dynamic array implementation with automatic resizing.
     * 
     * @tparam T The type of elements stored in the vector.
     */
    template <typename T>
    class Vector {
    public:
        /**
         * @brief Default constructor. Initializes an empty vector with a capacity of 1.
         */
        Vector() : m_Length(0), m_Capacity(1) {
            m_Data = new T[m_Capacity];
        }

        /**
         * @brief Constructor with initial given capacity.
         * 
         * @param initialCapacity The capacity that dictates the current vector's length and capacity 
         */
        Vector(size_t initialCapacity) : m_Length(initialCapacity), m_Capacity(initialCapacity) {
            m_Data = new T[m_Capacity];
        }

        /**
         * @brief Constructor that initializes the vector with an initializer list.
         * 
         * @param init_list The initializer list containing elements to populate the vector.
         */
        Vector(std::initializer_list<T> init_list)
            : m_Length(init_list.size()), m_Capacity(init_list.size()) {
            m_Data = new T[m_Capacity];

            size_t i = 0;
            for (const auto& item : init_list) {
                m_Data[i++] = item;
            }
        }

        /**
         * @brief Range-based constructor. Initializes the vector with elements from a range.
         * 
         * @tparam InputIt The type of the iterator.
         * @param first The beginning of the range.
         * @param last The end of the range.
         */
        template <typename InputIt>
        Vector(InputIt first, InputIt last) {
            size_t count = 0;
            for (auto it = first; it != last; ++it) {
                count++;
            }

            m_Length = count;
            m_Capacity = m_Length;
            m_Data = new T[m_Capacity];

            size_t i = 0;
            for (auto it = first; it != last; ++it) {
                m_Data[i++] = *it;
            }
        }

        /**
         * @brief Destructor. Clears the vector and deallocates memory.
         */
        ~Vector() {
            clear();
            delete[] m_Data;
        }

        /**
         * @brief Copy constructor. Performs a deep copy of another vector.
         * 
         * @param other The vector to copy from.
         */
        Vector(const Vector& other) noexcept : m_Length(other.m_Length), m_Capacity(other.m_Capacity) {
            m_Data = new T[m_Capacity];

            for (size_t i = 0; i != m_Length; i++) {
                m_Data[i] = other.m_Data[i];
            }
        }

        /**
         * @brief Move constructor. Transfers ownership of resources from another vector.
         * 
         * @param other The vector to move from.
         */
        Vector(Vector&& other) noexcept : m_Data(other.m_Data), m_Length(other.m_Length), m_Capacity(other.m_Capacity) {
            other.m_Data = nullptr;
            other.m_Length = 0;
            other.m_Capacity = 0;
        }

        /**
         * @brief Copy assignment operator. Performs a deep copy of another vector.
         * 
         * @param other The vector to copy from.
         * @return Vector& A reference to the current vector.
         */
        Vector& operator=(const Vector<T>& other) noexcept {
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

        /**
         * @brief Move assignment operator. Transfers ownership of resources from another vector.
         * 
         * @param other The vector to move from.
         * @return Vector& A reference to the current vector.
         */
        Vector& operator=(Vector<T>&& other) noexcept {
            if (this != &other) { // Self-assignment check
                delete[] m_Data; // Free current memory
                
                m_Data = other.m_Data;
                m_Length = other.m_Length;
                m_Capacity = other.m_Capacity;
                
                other.m_Data = nullptr; // Null the other vector's data
                other.m_Length = 0; 
                other.m_Capacity = 0; 
            }
            
            return *this;
        }

        /**
         * @brief Subscript operator. Provides access to the element at the specified index.
         * 
         * @param index The index of the element to access.
         * @return T& A reference to the element at the specified index.
         */
        constexpr T& operator[](size_t index) noexcept {
            if (index >= m_Capacity) 
                resize(index + 1); // Ensures capacity is sufficient
            if (index >= m_Length) 
                m_Length = index + 1; // Adjusts length to include new index
                    
            Assert::runtimeAssert(index <= m_Length, "Index specified is out of bounds!");
            return m_Data[index];
        }

        /**
         * @brief Const subscript operator. Provides read-only access to the element at the specified index.
         * 
         * @param index The index of the element to access.
         * @return const T& A const reference to the element at the specified index.
         */
        constexpr const T& operator[](size_t index) const noexcept {
            Assert::runtimeAssert(index <= m_Length, "Index specified is out of bounds!");
            return m_Data[index];
        }

        /**
         * @brief Clears the vector, setting its length to 0.
         */
        void clear() noexcept {
            m_Length = 0;
        }

        /**
         * @brief Checks if the vector is empty.
         * 
         * @return true If the vector is empty.
         * @return false If the vector is not empty.
         */
        constexpr bool isEmpty() const noexcept {
            return m_Length == 0;
        }

        /**
         * @brief Returns the current capacity of the vector.
         * 
         * @return size_t The capacity of the vector.
         */
        constexpr size_t getCapacity() const noexcept {
            return m_Capacity;
        }

        /**
         * @brief Returns the current length of the vector.
         * 
         * @return size_t The length of the vector.
         */
        constexpr size_t getLength() const noexcept {
            return m_Length;
        }

        /**
         * @brief Adds an element to the end of the vector.
         * 
         * @param value The element to add.
         */
        void pushBack(const T& value) {
            if (m_Length == m_Capacity)
                resize(m_Capacity * 2);

            m_Data[m_Length++] = value;
        }

        /**
         * @brief Constructs an element in place at the end of the vector.
         * 
         * @tparam Args The types of the arguments to forward to the constructor.
         * @param args The arguments to forward to the constructor.
         */
        template <typename... Args>
        void emplaceBack(Args&&... args) {
            if (m_Length == m_Capacity)
                resize(m_Capacity * 2);

            // Constructs the element in place at the end of the vector
            ::new(&m_Data[m_Length]) T(std::forward<Args>(args)...);

            m_Length++;
        }

        /**
         * @brief Removes the last element from the vector.
         */
        void popBack() noexcept {
            if (m_Length > 0)
                m_Length--;
        }

        /**
         * @brief Reserves memory for at least the specified capacity.
         * 
         * @param capacity The minimum capacity to reserve.
         */
        void reserve(size_t capacity) {
            if (capacity > m_Capacity)
                resize(capacity);
        }

        /**
         * @brief Resizes the vector to the specified capacity.
         * 
         * @param capacity The new capacity of the vector.
         */
        void resize(size_t capacity) {
            Assert::runtimeAssert(capacity > m_Length, "New capacity must be greater than current length!");

            T* data = new T[capacity];

            for (size_t i = 0; i != m_Length; i++) {
                data[i] = std::move(m_Data[i]);
            }

            delete[] m_Data;

            m_Data = data;
            m_Capacity = capacity;
        }

        /**
         * @brief Prints the vector's length, capacity, and elements.
         */
        void print() {
            std::cout << "Length: " << m_Length << ", Capacity: " << m_Capacity << "\n";
            
            for (size_t i = 0; i != m_Length; i++) {
                std::cout << "Data: " << m_Data[i] << ", "; 
            }

            std::cout << "\n";
        }

        /**
         * @brief Returns a pointer to the underlying data array.
         * 
         * @return T* A pointer to the data array.
         */
        constexpr T* getData() noexcept {
            return m_Data;
        }

        /**
         * @brief Returns a const pointer to the underlying data array.
         * 
         * @return const T* A const pointer to the data array.
         */
        constexpr const T* getData() const noexcept {
            return m_Data;
        }

        // Iterator types
        using Iterator = RandomAccessIterator<T>;
        using ConstIterator = RandomAccessIterator<const T>;

        /**
         * @brief Returns an iterator to the beginning of the vector.
         * 
         * @return Iterator An iterator to the beginning.
         */
        Iterator begin() noexcept { return Iterator(m_Data, m_Data, m_Data + m_Length); }

        /**
         * @brief Returns an iterator to the end of the vector.
         * 
         * @return Iterator An iterator to the end.
         */
        Iterator end()   noexcept { return Iterator(m_Data + m_Length, m_Data, m_Data + m_Length); }

        /**
         * @brief Returns a const iterator to the beginning of the vector.
         * 
         * @return ConstIterator A const iterator to the beginning.
         */
        ConstIterator begin() const noexcept { return ConstIterator(m_Data, m_Data, m_Data + m_Length); }

        /**
         * @brief Returns a const iterator to the end of the vector.
         * 
         * @return ConstIterator A const iterator to the end.
         */
        ConstIterator end()   const noexcept { return ConstIterator(m_Data + m_Length, m_Data, m_Data + m_Length); }

    private:
        T* m_Data;          // Pointer to the dynamic array
        size_t m_Length;    // Number of elements in the vector
        size_t m_Capacity;  // Total capacity of the vector
    };
} // namespace TCMS