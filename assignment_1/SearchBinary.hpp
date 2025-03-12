#pragma once

#include "./Search.hpp"

namespace PerformanceEvaluation
{
    class SearchBinary : public Search<LinkedList, LinkedListNode*> {
        public:
            // Override linear search methods with empty implementations
            LinkedListNode*         LinearSearch            (std::string_view, const LinkedList&, Criteria, SearchType) override { return nullptr; }
            LinkedList              LinearSearchAndCopy     (std::string_view, const LinkedList&, Criteria, SearchType) override { return LinkedList(); }
            void                    LinearSearchAndDisplay  (std::string_view, const LinkedList&, Criteria, SearchType) override {}

            // Binary search remains pure virtual, forcing derived classes to implement it
            virtual LinkedListNode* BinarySearch            (std::string_view, const LinkedList&, Criteria, SearchType) = 0;
            virtual LinkedList      BinarySearchAndCopy     (std::string_view, const LinkedList&, Criteria, SearchType) = 0;
            virtual void            BinarySearchAndDisplay  (std::string_view, const LinkedList&, Criteria, SearchType) = 0; 
    };
} // namespace PerformanceEvaluation
