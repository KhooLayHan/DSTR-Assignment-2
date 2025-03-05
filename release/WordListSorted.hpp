#pragma once 

#include <iostream>
#include <string>

namespace PerformanceEvaluation
{   
    struct WordFreqNode {
        std::string m_Word;
        int32_t m_Count;
        WordFreqNode* m_Next;
        
        WordFreqNode(const std::string& word, int32_t count) 
            : m_Word(word), m_Count(count), m_Next(nullptr) {}
    };

    class WordListSorted {
    private:
        WordFreqNode* m_Head;

    public:
        WordListSorted() : m_Head(nullptr) {}

        ~WordListSorted() {
            while (m_Head) {
                WordFreqNode* temp = m_Head;
                m_Head = m_Head->m_Next;
                delete temp;
            }
        }

        void InsertSorted(const std::string& word, int32_t count);

        void MergeSort();

        void DisplayAll() const;
    private:
        WordFreqNode* MergeSortHelper(WordFreqNode*);

        WordFreqNode* GetMiddle(WordFreqNode*);

        WordFreqNode* Merge(WordFreqNode*, WordFreqNode*);
    };
} // namespace PerformanceEvaluation
