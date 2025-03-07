#pragma once

#ifndef SORT_MERGE_LINKED_LIST_HPP
#define SORT_MERGE_LINKED_LIST_HPP

#include "./Sort.hpp"

namespace PerformanceEvaluation {
    class SortMergeLinkedList final : public Sort<LinkedList, LinkedListNode*> {
        protected:
            void SortBy(LinkedList&) override;
        private:
            // Applies merge sort recursively 
            void Merge(LinkedListNode**);

            // Helper function to split the linked list into two halves
            void SplitAndGetMiddle(LinkedListNode*, LinkedListNode**, LinkedListNode**);

            // Helper function to merge two sorted linked lists 
            LinkedListNode* SortAndMerge(LinkedListNode*, LinkedListNode*);
    };
} // namespace PerformanceEvaluation

#endif