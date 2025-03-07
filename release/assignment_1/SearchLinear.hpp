#pragma once

#include "./Search.hpp"

namespace PerformanceEvaluation
{
    class SearchLinear : public Search<LinkedList, LinkedListNode*> {
        public:
            // Override binary search methods with empty implementations
            LinkedListNode*         BinarySearch            (std::string_view, const LinkedList&, Criteria, SearchType) override { return nullptr; }
            LinkedList              BinarySearchAndCopy     (std::string_view, const LinkedList&, Criteria, SearchType) override { return LinkedList(); }
            void                    BinarySearchAndDisplay  (std::string_view, const LinkedList&, Criteria, SearchType) override {}

            // Linear search remains pure virtual, forcing derived classes to implement it
            virtual LinkedListNode* LinearSearch            (std::string_view, const LinkedList&, Criteria, SearchType) = 0;
            virtual LinkedList      LinearSearchAndCopy     (std::string_view, const LinkedList&, Criteria, SearchType) = 0;
            virtual void            LinearSearchAndDisplay  (std::string_view, const LinkedList&, Criteria, SearchType) = 0;
    };
} // namespace PerformanceEvaluation
