#pragma once

#ifndef SORT_HEAP_LINKED_LIST_HPP
#define SORT_HEAP_LINKED_LIST_HPP

#include "./Sort.hpp"

namespace PerformanceEvaluation {
    class SortHeapLinkedList final : public Sort<LinkedList, LinkedListNode*> {
        protected:
            void SortBy(LinkedList&) override;
        private:
            // Function to count the length of the linked list
            size_t GetLength(LinkedListNode*);
            
            // Applies heap sort
            LinkedListNode* HeapSort(LinkedListNode*);
        
            // Min-heap for ascending order, ensures the smallest element is always at the top
            void Heapify(LinkedListNode**, int32_t, int32_t);
    };
} // namespace PerformanceEvaluation

#endif