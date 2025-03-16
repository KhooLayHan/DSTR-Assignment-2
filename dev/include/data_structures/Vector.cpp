// // #pragma once

// // #include <cassert>
// // #include "../core/utils/Assert.hpp"
// // #include <initializer_list>
// // #include <iostream>
// // #include <memory>  // For smart pointers
// // #include <utility>

// // #include "./iterators/RandomAccessIterator.hpp"

// // namespace TCMS
// // {
// //     template <typename T>
// //     class Vector {
// //     public:
// //         Vector() : m_Length(0), m_Capacity(1) {
// //             m_Data = std::make_unique<std::shared_ptr<T>[]>(m_Capacity);
// //         }

// //         Vector(std::initializer_list<std::shared_ptr<T>> init_list)
// //             : m_Length(init_list.size()), m_Capacity(init_list.size()) {
// //             m_Data = std::make_unique<std::shared_ptr<T>[]>(m_Capacity);

// //             size_t i = 0;
// //             for (const auto& item : init_list) {
// //                 m_Data[i++] = item;
// //             }
// //         }

// //         ~Vector() = default;  // Smart pointers automatically manage memory

// //         // Copy constructor
// //         Vector(const Vector& other) noexcept : m_Length(other.m_Length), m_Capacity(other.m_Capacity) {
// //             m_Data = std::make_unique<std::shared_ptr<T>[]>(m_Capacity);

// //             for (size_t i = 0; i != m_Length; i++) {
// //                 m_Data[i] = other.m_Data[i];  // Copy shared_ptr references
// //             }
// //         }

// //         // Move constructor
// //         Vector(Vector&& other) noexcept 
// //             : m_Data(std::move(other.m_Data)), m_Length(other.m_Length), m_Capacity(other.m_Capacity) {
// //             other.m_Length = 0;
// //             other.m_Capacity = 0;
// //         }

// //         // Copy assignment
// //         Vector& operator=(const Vector& other) noexcept {
// //             if (this != &other) {  
// //                 m_Length = other.m_Length;
// //                 m_Capacity = other.m_Capacity;
// //                 m_Data = std::make_unique<std::shared_ptr<T>[]>(m_Capacity);

// //                 for (size_t i = 0; i != m_Length; i++) {
// //                     m_Data[i] = other.m_Data[i];  
// //                 }
// //             }
// //             return *this;
// //         }

// //         // Move assignment
// //         Vector& operator=(Vector&& other) noexcept {
// //             if (this != &other) {  
// //                 m_Data = std::move(other.m_Data);
// //                 m_Length = other.m_Length;
// //                 m_Capacity = other.m_Capacity;

// //                 other.m_Length = 0;
// //                 other.m_Capacity = 0;
// //             }
// //             return *this;
// //         }

// //         constexpr std::shared_ptr<T>& operator[](size_t index) noexcept {
// //             Assert::runtimeAssert(index < m_Length, "Index out of bounds!");
// //             return m_Data[index];
// //         }
        
// //         constexpr const std::shared_ptr<T>& operator[](size_t index) const noexcept {
// //             Assert::runtimeAssert(index < m_Length, "Index out of bounds!");
// //             return m_Data[index];
// //         }

// //         void clear() noexcept {
// //             m_Length = 0;
// //         }

// //         constexpr bool isEmpty() const noexcept {
// //             return m_Length == 0;
// //         }

// //         constexpr size_t getCapacity() const noexcept {
// //             return m_Capacity;
// //         }

// //         constexpr size_t getLength() const noexcept {
// //             return m_Length;
// //         }

// //         void pushBack(const std::shared_ptr<T>& value) {
// //             if (m_Length == m_Capacity)
// //                 resize(m_Capacity * 2);

// //             m_Data[m_Length++] = value;
// //         }

// //         template <typename... Args>
// //         void emplaceBack(Args&&... args) {
// //             if (m_Length == m_Capacity)
// //                 resize(m_Capacity * 2);

// //             m_Data[m_Length] = std::make_shared<T>(std::forward<Args>(args)...);
// //             m_Length++;
// //         }

// //         void popBack() noexcept {
// //             if (m_Length > 0)
// //                 m_Length--;
// //         }

// //         void reserve(size_t capacity) {
// //             if (capacity > m_Capacity)
// //                 resize(capacity);
// //         }

// //         void resize(size_t capacity) {
// //             Assert::runtimeAssert(capacity > m_Length, "New capacity must be greater than current length!");

// //             auto data = std::make_unique<std::shared_ptr<T>[]>(capacity);

// //             for (size_t i = 0; i != m_Length; i++) {
// //                 data[i] = std::move(m_Data[i]);
// //             }

// //             m_Data = std::move(data);
// //             m_Capacity = capacity;
// //         }

// //         void print() {
// //             std::cout << "Length: " << m_Length << ", Capacity: " << m_Capacity << "\n";
            
// //             for (size_t i = 0; i != m_Length; i++) {
// //                 std::cout << "Data: " << (m_Data[i] ? m_Data[i]->getName() : "nullptr") << ", "; 
// //             }

// //             std::cout << "\n";
// //         }

// //         constexpr std::shared_ptr<T>* getData() noexcept {
// //             return m_Data.get();
// //         }

// //         constexpr const std::shared_ptr<T>* getData() const noexcept {
// //             return m_Data.get();
// //         }

// //         using Iterator = RandomAccessIterator<std::shared_ptr<T>>;
// //         using ConstIterator = RandomAccessIterator<const std::shared_ptr<T>>;

// //         Iterator begin() noexcept { return Iterator(m_Data.get(), m_Data.get(), m_Data.get() + m_Length); }
// //         Iterator end() noexcept { return Iterator(m_Data.get() + m_Length, m_Data.get(), m_Data.get() + m_Length); }
        
// //         ConstIterator begin() const noexcept { return ConstIterator(m_Data.get(), m_Data.get(), m_Data.get() + m_Length); }
// //         ConstIterator end() const noexcept { return ConstIterator(m_Data.get() + m_Length, m_Data.get(), m_Data.get() + m_Length); }

// //     private:
// //         std::unique_ptr<std::shared_ptr<T>[]> m_Data;
// //         size_t m_Length;
// //         size_t m_Capacity;
// //     };
// // } // namespace TCMS

// #pragma once

// #include <cassert>
// #include "../core/utils/Assert.hpp"
// #include <initializer_list>
// #include <iostream>
// #include <memory>
// #include <utility>

// #include "./iterators/RandomAccessIterator.hpp"

// namespace TCMS
// {
//     template <typename T>
//     class Vector {
//         public:
//             Vector() : m_Length(0), m_Capacity(1) {
//                 m_Data = new T[m_Capacity];
//             }

//             Vector(std::initializer_list<T> init_list)
//                 : m_Length(init_list.size()), m_Capacity(init_list.size()) {
//                 m_Data = new T[m_Capacity];

//                 size_t i = 0;
//                 for (const auto& item : init_list) {
//                     m_Data[i++] = item;
//                     // i++;
//                 }
//             }

//             // New range-based constructor
//             template <typename InputIt>
//             Vector(InputIt first, InputIt last) {
//                 size_t count = 0;
//                 for (auto it = first; it != last; ++it) {
//                     count++;
//                 }

//                 // m_Length = std::distance(first, last);
//                 m_Length = count;
//                 m_Capacity = m_Length;
//                 m_Data = new T[m_Capacity];

//                 size_t i = 0;
//                 for (auto it = first; it != last; ++it) {
//                     m_Data[i++] = *it;
//                 }
//             }

//             ~Vector() {
//                 clear();
//                 delete[] m_Data;
//             }

//             // Copy constructors
//             Vector(const Vector& other) noexcept : m_Length(other.m_Length), m_Capacity(other.m_Capacity) {
//                 m_Data = new T[m_Capacity];

//                 for (size_t i = 0; i != m_Length; i++) {
//                     m_Data[i] = other.m_Data[i];
//                 }
//             } 

//             // Move constructors
//             Vector(Vector&& other) noexcept : m_Data(other.m_Data), m_Length(other.m_Length), m_Capacity(other.m_Capacity) {
//                 other.m_Data = nullptr;
//                 other.m_Length = 0;
//                 other.m_Capacity = 0;
//             } 

//             // Copy assignment
//             Vector& operator=(const Vector<T>& other) noexcept {
//                 if (this != &other) { // Self-assignment check
//                     delete[] m_Data; // Free current memory
                    
//                     m_Length = other.m_Length;
//                     m_Capacity = other.m_Capacity;
//                     m_Data = new T[m_Capacity];
                    
//                     for (size_t i = 0; i != m_Length; i++) 
//                         m_Data[i] = other.m_Data[i];
//                 }

//                 return *this;
//             }

//             // Move assignment
//             Vector& operator=(Vector<T>&& other) noexcept {
//                 if (this != &other) { // Self-assignment check
//                     delete[] m_Data; // Free current memory
                    
//                     m_Data = other.m_Data;
//                     m_Length = other.m_Length;
//                     m_Capacity = other.m_Capacity;
//                     // m_Data = new T[m_Capacity];
                    
//                     other.m_Data = nullptr; // Null the other vector's data
//                     other.m_Length = 0; 
//                     other.m_Capacity = 0; 
//                 }
                
//                 return *this;
//             }

//             // constexpr const Vector& operator=(T&& other) const noexcept {
//             //     if (this != &other) { // Self-assignment check
//             //         delete[] m_Data; // Free current memory
                    
//             //         m_Length = other.m_Length;
//             //         m_Capacity = other.m_Capacity;
//             //         m_Data = new T[m_Capacity];
                    
//             //         other.m_Data = nullptr; // Null the other vector's data
//             //         other.m_Length = 0; 
//             //         other.m_Capacity = 0; 
//             //     }
                
//             //     return *this;
//             // }

//             // Overloading [] operator
//             constexpr T& operator[](size_t index) noexcept {
//                 if (index >= m_Capacity) 
//                     resize(index + 1); // Ensures capacity is sufficient
//                 if (index >= m_Length) 
//                     m_Length = index + 1; // Adjusts length to include new index
                    
//                 Assert::runtimeAssert(index <= m_Length, "Index specified is out of bounds!");
//                 return m_Data[index];
//             }
            
//             constexpr const T& operator[](size_t index) const noexcept {
//                 Assert::runtimeAssert(index <= m_Length, "Index specified is out of bounds!");
//                 return m_Data[index];
//             }

//             void clear() noexcept {
//                 m_Length = 0;
//             }
            
//             constexpr bool isEmpty() const noexcept {
//                 return m_Length == 0;
//             }

//             constexpr size_t getCapacity() const noexcept {
//                 return m_Capacity;
//             } 

//             constexpr size_t getLength() const noexcept {
//                 return m_Length;
//             } 

//             void pushBack(const T& value) {
//                 if (m_Length == m_Capacity)
//                     resize(m_Capacity * 2);

//                 m_Data[m_Length++] = value;
//             }

//             // Sourced from ChatGPT
//             template <typename... Args>
//             void emplaceBack(Args&&... args) {
//                 if (m_Length == m_Capacity)
//                     resize(m_Capacity * 2);

//                 // Constructs the elements in place at the end of the vector
//                 ::new(&m_Data[m_Length]) T(std::forward<Args>(args)...);

//                 m_Length++;
//             }

//             void popBack() noexcept {
//                 if (m_Length > 0)
//                     m_Length--;
//             }
            
//             void reserve(size_t capacity) {
//                 if (capacity > m_Capacity)
//                     resize(capacity);
//             }

//             void resize(size_t capacity) {
//                 Assert::runtimeAssert(capacity > m_Length, "New capacity must be greater than current length!");

//                 T* data = new T[capacity];

//                 for (size_t i = 0; i != m_Length; i++) {
//                     data[i] = std::move(m_Data[i]);
//                 }

//                 delete[] m_Data;

//                 m_Data = data;
//                 m_Capacity = capacity;
//             }

//             void print() {
//                 std::cout << "Length: " << m_Length << ", Capacity: " << m_Capacity << "\n";
                
//                 for (size_t i = 0; i != m_Length; i++) {
//                     std::cout << "Data: " << m_Data[i] << ", "; 
//                 }

//                 std::cout << "\n";
//             }

//             constexpr T* getData() noexcept {
//                 return m_Data;
//             } 

//             constexpr const T* getData() const noexcept {
//                 return m_Data;
//             } 

//             using Iterator = RandomAccessIterator<T>;
//             using ConstIterator = RandomAccessIterator<const T>;

//             Iterator begin() noexcept { return Iterator(m_Data, m_Data, m_Data + m_Length); }
//             Iterator end()   noexcept { return Iterator(m_Data + m_Length, m_Data, m_Data + m_Length); }
            
//             ConstIterator begin() const noexcept { return ConstIterator(m_Data, m_Data, m_Data + m_Length); }
//             ConstIterator end()   const noexcept { return ConstIterator(m_Data + m_Length, m_Data, m_Data + m_Length); }
//         private:
//             T* m_Data;
//             size_t m_Length;
//             size_t m_Capacity; 
//     };    
// } // namespace TCMS
