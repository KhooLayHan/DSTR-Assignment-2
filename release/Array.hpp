#pragma once

#include <cassert>
#include <array>
#include <iostream>
#include <string>
#include <memory> 

#include "./Dataset.hpp"
namespace PerformanceEvaluation {

    template <typename T, size_t Length = 25000>
    class Array {
        public:
            Array() : m_Size(0) {}

            // ✅ Copy constructor for safe copying
            Array(const Array& other) : m_Size(other.m_Size) {
                for (size_t i = 0; i < other.m_Size; i++) {
                    m_Data[i] = other.m_Data[i];
                }
            }

            ~Array() {} // Destructor
            
            // Overloading [] operator
            constexpr T& operator[](size_t index) noexcept {
                assert(index < Length && "Index specified is out of bounds!");

                return m_Data[index];
            }

            constexpr const T& operator[](size_t index) const noexcept {
                assert(index < Length && "Index specified is out of bounds!");

                return m_Data[index];
            }
            
            void DisplayFirst(size_t count) const {
                if (m_Size == 0) {
                    std::cout << "Array is empty.\n";
                    return;
                }
            
                size_t limit = (count > m_Size) ? m_Size : count; // Ensure we don't exceed the stored elements
            
                for (size_t i = 0; i < limit; i++) {
                    std::cout << "\n\033[34;1mID:\033[0m "       << m_Data[i].m_Id      << "\n";
                    std::cout << "\033[34;1mTITLE:\033[0m "      << m_Data[i].m_Title   << "\n";
                    std::cout << "\033[34;1mTEXT:\033[0m "       << m_Data[i].m_Text    << "\n";
                    std::cout << "\033[34;1mSUBJECT:\033[0m "    << m_Data[i].m_Subject << "\n";
                    std::cout << "\033[34;1mDATE:\033[0m "       << m_Data[i].m_Date    << "\n";
                }
            
                std::cout << "\n";
            }

            void InsertEnd(const T& value) {
                if (m_Size < Length) {
                    m_Data[m_Size++] = value;
                } else {
                    //std::cerr << "Array is full. Cannot insert more elements." << std::endl;
                    return;
                }
            }

            void DisplayLength(std::string_view file_path) const {
                std::cout << "The total number of elements in the array from " << file_path << " dataset is "
                    << m_Size << ".\n";
            }

            T* getHead() const {
                return m_Data;
            }

            T* Data() {
                return m_Data;  // Return pointer to first element
            }

            size_t Size() const {
                return m_Size;
            }

            T* begin() { return m_Data; }
            T* end() { return m_Data + m_Size; }

            const T* begin() const { return m_Data; }
            const T* end() const { return m_Data + m_Size; }

            void DeleteElement(const T&);
        private:
            T m_Data[Length]; // To accept any type 
            size_t m_Size;    // Number of elements currently in array
    };

} // namespace PerformanceEvaluation