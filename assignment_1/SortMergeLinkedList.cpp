#include <iostream>
#include <string>

#include "./SimpleConsoleLogger.hpp"
#include "./SimpleLoggingService.hpp"

#include "./SortMergeLinkedList.hpp"

namespace PerformanceEvaluation {
    void SortMergeLinkedList::SortBy(LinkedList& linked_list) {
        LinkedListNode* head = linked_list.GetHead();
        Merge(&head);
        linked_list.SetHead(head);
    }

    // Applies merge sort recursively 
    void SortMergeLinkedList::Merge(LinkedListNode** head) {                
        // List is already sorted if list is empty
        if (!(*head) || !((*head)->m_Next)) {
            // SimpleConsoleLogger console;
            // SimpleLoggingService::UseWarnLogger(console, "The linked list is empty.");
            
            return;
        }

        LinkedListNode* left = nullptr;
        LinkedListNode* right = nullptr;

        //Split and get middle of list
        SplitAndGetMiddle(*head, &left, &right);

        Merge(&left);
        Merge(&right);

        // Merge the sorted halves                
        *head = SortAndMerge(left, right);
    }

    // Helper function to split the linked list into two halves
    void SortMergeLinkedList::SplitAndGetMiddle(LinkedListNode* source, LinkedListNode** left, LinkedListNode** right) {
        if (!source || !(source->m_Next)) {
            SimpleConsoleLogger console;
            SimpleLoggingService::UseWarnLogger(console, "The linked list is empty.");
            
            *left = source;
            *right = nullptr;

            return;
        }

        LinkedListNode* first_half = source;
        LinkedListNode* second_half = source->m_Next;
        
        // Iterate until second_half reaches the end of node, by then first_half will be the middle node
        while (second_half && second_half->m_Next) {
            first_half = first_half->m_Next;
            second_half = second_half->m_Next->m_Next;
        }

        *left = source;
        *right = first_half->m_Next;
        first_half->m_Next = nullptr;
    }

    // Helper function to merge two sorted linked lists 
    LinkedListNode* SortMergeLinkedList::SortAndMerge(LinkedListNode* left, LinkedListNode* right) {
        DateUtility date_utility{};

        // Sort by year
        if (!left)
            return right;
        if (!right)
            return left;

        LinkedListNode* result = nullptr;

        if (CompareAndSortDate(date_utility, left->m_Data.m_Date, right->m_Data.m_Date)) {
            result = left;
            result->m_Next = SortAndMerge(left->m_Next, right);
        } else {
            result = right;
            result->m_Next = SortAndMerge(left, right->m_Next);
        }
    
        return result;
    } 
} // namespace PerformanceEvaluation