#include <iostream>

#include "./SearchBinaryLinkedList.hpp"

#include "./SimpleConsoleLogger.hpp"
#include "./SimpleLoggingService.hpp"

namespace PerformanceEvaluation
{
    // Public API using LinkedList object
    LinkedListNode* SearchBinaryLinkedList::BinarySearch(std::string_view target, const LinkedList& linked_list, Criteria criteria, SearchType type) {
        return BinarySearchRecursive(linked_list.GetHead(), nullptr, target, criteria, type);
    }
 
    // Public API that copies to a new Linked List
    LinkedList SearchBinaryLinkedList::BinarySearchAndCopy(std::string_view target, const LinkedList& linked_list, Criteria criteria, SearchType type) {
        LinkedList new_list;
        LinkedListNode* new_tail = nullptr;
        BinarySearchRecursiveCopy(linked_list.GetHead(), nullptr, target, criteria, type, new_list, new_tail);
        return new_list;
    }

    // Public function to perform binary search and display results
    void SearchBinaryLinkedList::BinarySearchAndDisplay( std::string_view target, const LinkedList& linked_list, Criteria criteria, SearchType type) {
        BinarySearchRecursiveDisplay(linked_list.GetHead(), nullptr, target, criteria, type);
    }

    // Finds the middle node in a given range [head, tail)
    LinkedListNode* SearchBinaryLinkedList::FindMiddle(LinkedListNode* start, LinkedListNode* end) {
        if (!start) return nullptr;

        LinkedListNode* slow = start;
        LinkedListNode* fast = start;

        while (fast != end && fast->m_Next != end) {
            slow = slow->m_Next;
            fast = fast->m_Next->m_Next;
        }

        return slow;
    }
    
    // Recursive Binary Search function
    LinkedListNode* SearchBinaryLinkedList::BinarySearchRecursive(LinkedListNode* head, LinkedListNode* tail, std::string_view target, Criteria criteria, SearchType type) {
        if (!head || head == tail) return nullptr; // Base case: Empty or single-node sublist

        LinkedListNode* mid = FindMiddle(head, tail);
        if (!mid) return nullptr;

        std::string middle_value = GetSearchString(mid->m_Data, criteria);

        if (Contains(target, middle_value, type)) {
            return mid; // Found
        } else if (target < middle_value) {
            return BinarySearchRecursive(head, mid, target, criteria, type); // Search left half
        } else {
            return BinarySearchRecursive(mid->m_Next, tail, target, criteria, type); // Search right half
        }
    }

    // Recursive function for binary search and deep copy
    void SearchBinaryLinkedList::BinarySearchRecursiveCopy(LinkedListNode* head, LinkedListNode* tail, std::string_view target, Criteria criteria, SearchType type, LinkedList& new_list, LinkedListNode*& new_tail) {
        if (!head || head == tail) return;

        LinkedListNode* mid = FindMiddle(head, tail);
        if (!mid) return;

        std::string middle_value = GetSearchString(mid->m_Data, criteria);

        if (Contains(target, middle_value, type)) {
            // Deep copy found node
            LinkedListNode* new_node = new LinkedListNode(mid->m_Data);
            
            if (!new_list.GetHead()) {
                new_list.InsertEnd(new_node->m_Data);
                new_tail = new_list.GetHead();
            } else {
                new_tail->m_Next = new_node;
                new_tail = new_node;
            }
        }

        // Search both left and right halves
        BinarySearchRecursiveCopy(head, mid, target, criteria, type, new_list, new_tail);
        BinarySearchRecursiveCopy(mid->m_Next, tail, target, criteria, type, new_list, new_tail);
    }

    // Recursive function for binary search and display
    void SearchBinaryLinkedList::BinarySearchRecursiveDisplay(LinkedListNode* head, LinkedListNode* tail, std::string_view target, Criteria criteria, SearchType type) {
        if (!head || head == tail) return;

        LinkedListNode* mid = FindMiddle(head, tail);
        if (!mid) return;

        std::string middle_value = GetSearchString(mid->m_Data, criteria);

        if (Contains(target, middle_value, type)) {
            mid->m_Data.Display(); // Display the dataset node
        }

        // Search both left and right halves
        BinarySearchRecursiveDisplay(head, mid, target, criteria, type);
        BinarySearchRecursiveDisplay(mid->m_Next, tail, target, criteria, type);
    }

    // Function to extract the comparison string based on criteria
    std::string SearchBinaryLinkedList::GetSearchString(const Dataset& dataset, Criteria criteria) {
        switch (criteria) {
            case Criteria::TITLE:   return ToLowerCase(dataset.m_Title);
            case Criteria::TEXT:    return ToLowerCase(dataset.m_Text);
            case Criteria::SUBJECT: return ToLowerCase(dataset.m_Subject);
            case Criteria::DATE:    return ToLowerCase(dataset.m_Date);
            default:                return "";
        }
    }
}