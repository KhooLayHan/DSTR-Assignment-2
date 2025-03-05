#pragma once

#include "./SearchBinary.hpp"

namespace PerformanceEvaluation
{
    class SearchBinaryLinkedList final : public SearchBinary {
        public:
            // Public API using LinkedList object
            LinkedListNode* BinarySearch            (std::string_view, const LinkedList&, Criteria, SearchType) override;
            
            // Public API that copies to a new Linked List
            LinkedList      BinarySearchAndCopy     (std::string_view, const LinkedList&, Criteria, SearchType) override;
            
            // Public function to perform binary search and display results
            void            BinarySearchAndDisplay  (std::string_view, const LinkedList&, Criteria, SearchType) override;
        protected:
            // Finds the middle node in a given range [head, tail)
            LinkedListNode* FindMiddle                  (LinkedListNode*, LinkedListNode*);
            
            // Recursive Binary Search function
            LinkedListNode* BinarySearchRecursive       (LinkedListNode*, LinkedListNode*, std::string_view, Criteria, SearchType);
            
            // Recursive function for binary search and deep copy
            void            BinarySearchRecursiveCopy   (LinkedListNode*, LinkedListNode*, std::string_view, Criteria, SearchType, LinkedList&, LinkedListNode*&);
            
            // Recursive function for binary search and display
            void            BinarySearchRecursiveDisplay(LinkedListNode*, LinkedListNode*, std::string_view, Criteria, SearchType);
            
            // Function to extract the comparison string based on criteria
            std::string     GetSearchString             (const Dataset&, Criteria);
    };
} // namespace PerformanceEvaluation
