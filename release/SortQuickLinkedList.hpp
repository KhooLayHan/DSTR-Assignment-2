#pragma once

#ifndef SORT_QUICK_LINKED_LIST_HPP
#define SORT_QUICK_LINKED_LIST_HPP

#include "./Sort.hpp"

namespace PerformanceEvaluation {
    class SortQuickLinkedList final : public Sort<LinkedList, LinkedListNode*> {
        protected:
            void SortBy(LinkedList&) override;
        private:
            // Applies quick sort
            LinkedListNode* QuickSort(LinkedListNode*);

            // Partition the linked list around a pivot, ensuring smaller values comes before it and is to the left
            LinkedListNode* Partition(LinkedListNode*, LinkedListNode**, LinkedListNode**);
    };
} // namespace PerformanceEvaluation

#endif