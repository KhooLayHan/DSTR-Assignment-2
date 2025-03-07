#pragma once

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <string_view>
#include <memory>
#include <variant>
#include <regex>

// #include "./FileHandling.hpp"
#include "./Dataset.hpp"
// #include "./Array.hpp"

namespace PerformanceEvaluation {
    
    // Implement a Node structure
    struct LinkedListNode {
        Dataset m_Data;
        LinkedListNode* m_Next;
        
        explicit LinkedListNode(const Dataset& value) 
            : m_Data(std::move(value)), m_Next(nullptr) {

        }
    };
    
    // Implement the Linked List class
    class LinkedList {
        public:
            LinkedList() 
                : m_Head(nullptr), m_Length(0) {

            }
        
            LinkedList(const LinkedList& other)
                : m_Head(other.m_Head), m_Length(0) {
            }
            
            LinkedList(LinkedList&& other)
                : m_Head(std::move(other.m_Head)), m_Length(0) {
            }
            
            ~LinkedList() {
                LinkedListNode* temp;

                while (m_Head != nullptr) {
                    temp = m_Head;
                    m_Head = m_Head->m_Next;

                    delete temp;
                    temp = nullptr;
                }
            }
            
            void InsertBegin(const Dataset&);
            
            void InsertEnd(const Dataset&);

            void InsertPosition(const Dataset&, size_t);
            
            void DisplayAll() const;
            
            void DisplayFirst(int32_t count = 10) const;

            void DisplayTitle() const;

            void DisplayText() const;
            
            void DisplaySubject() const;

            void DisplayDate() const;

            void DisplayLength(std::string_view) const;
            
            size_t GetLength() const;

            void DeleteNode(const Dataset&);

            void DeleteAll();

            LinkedListNode* GetHead() const;
            
            void SetHead(LinkedListNode*);

        protected:
            void DecrementLength();

            void IncrementLength();

            bool Contains(const std::string&, std::string_view) const;

            void IsHeadEmpty() const;

            void IsHeadOrNextEmpty() const;
            
        private:
            LinkedListNode* m_Head{ nullptr };
            size_t m_Length;
    };
} // namespace PerformanceEvaluation

#endif