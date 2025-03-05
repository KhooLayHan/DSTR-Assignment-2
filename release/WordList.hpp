#pragma once

#include <string>
#include <string_view>
#include <memory>

namespace PerformanceEvaluation {
    
    // Implement a Node structure
    struct WordListNode {
        std::string m_Data;
        WordListNode* m_Next;
        
        WordListNode(const std::string& value) 
            : m_Data(value), m_Next(nullptr) {

        }
    };
    
    // Implement the Linked List class
    class WordList {
        public:
            WordList() 
                : m_Head(nullptr), m_Length(0) {

            }
        
            WordList(const WordList& other)
                : m_Head(other.m_Head), m_Length(0) {
            }
            
            WordList(WordList&& other)
                : m_Head(std::move(other.m_Head)), m_Length(0) {
            }
            
            ~WordList() {
                WordListNode* temp;

                while (m_Head != nullptr) {
                    temp = m_Head;
                    m_Head = m_Head->m_Next;

                    delete temp;
                    temp = nullptr;
                }
            }
            
            void InsertBegin(const std::string&);
            
            void InsertEnd(const std::string&);

            void InsertPosition(const std::string&, size_t);
            
            void DisplayAll() const;
            
            size_t GetLength() const;
   
            void DeleteNode(const std::string&);

            void DeleteAll();

            WordListNode* GetHead() const;
            
            void SetHead(WordListNode*);

        protected:
            void DecrementLength();

            void IncrementLength();

            bool Contains(const std::string&, std::string_view) const;

            void IsHeadEmpty() const;

            void IsHeadOrNextEmpty() const;
            
        private:
            WordListNode* m_Head{ nullptr };
            size_t m_Length;
    };
} // namespace PerformanceEvaluation
