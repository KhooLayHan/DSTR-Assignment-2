#include "./WordListSorted.hpp"

#include "./SimpleConsoleLogger.hpp"
#include "./SimpleLoggingService.hpp"

namespace PerformanceEvaluation
{   
    void WordListSorted::InsertSorted(const std::string& word, int32_t count) {
        WordFreqNode* newNode = new WordFreqNode(word, count);
        
        if (!m_Head || m_Head->m_Count <= count) { // Sort by descending frequency
            newNode->m_Next = m_Head;
            m_Head = newNode;
            return;
        }

        WordFreqNode* current = m_Head;
        while (current->m_Next && current->m_Next->m_Count > count) {
            current = current->m_Next;
        }

        newNode->m_Next = current->m_Next;
        current->m_Next = newNode;
    }

    void WordListSorted::MergeSort() {
        m_Head = MergeSortHelper(m_Head);
    }        

    void WordListSorted::DisplayAll() const {
        if (m_Head == nullptr) {
            SimpleConsoleLogger console;
            SimpleLoggingService::UseWarnLogger(console, "The Sorted Word Linked List is empty.");
            return;
        }

        WordFreqNode* temp = m_Head;
        int i = 0;

        while (temp != nullptr) {
            std::cout << "\n\033[34;1m" << ++i << "\033[0m " << temp->m_Word << ", " << temp->m_Count << "\n";
            
            temp = temp->m_Next;
        } 

        std::cout << "\n";
    }

    WordFreqNode* WordListSorted::MergeSortHelper(WordFreqNode* head) {
        if (!head || !head->m_Next) return head;

        WordFreqNode* middle = GetMiddle(head);
        WordFreqNode* rightHalf = middle->m_Next;
        middle->m_Next = nullptr;

        return Merge(MergeSortHelper(head), MergeSortHelper(rightHalf));
    }

    WordFreqNode* WordListSorted::GetMiddle(WordFreqNode* head) {
        if (!head) return head;
        
        WordFreqNode* slow = head;
        WordFreqNode* fast = head->m_Next;

        while (fast && fast->m_Next) {
            slow = slow->m_Next;
            fast = fast->m_Next->m_Next;
        }
        
        return slow;
    }

    WordFreqNode* WordListSorted::Merge(WordFreqNode* left, WordFreqNode* right) {
        if (!left) return right;
        if (!right) return left;

        if (left->m_Count >= right->m_Count) {  // Descending order
            left->m_Next = Merge(left->m_Next, right);
            return left;
        } else {
            right->m_Next = Merge(left, right->m_Next);
            return right;
        }
    }
} // namespace PerformanceEvaluation
