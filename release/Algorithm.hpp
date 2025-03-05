#pragma once

#include <memory>
#include <string>
#include <string_view>

#include "./Array.hpp"
#include "./DynamicArray.hpp"
#include "./LinkedList.hpp"
#include "./WordList.hpp"
#include "./SortMergeArray.hpp"

#include "./Search.hpp"
#include "./Sort.hpp"

namespace PerformanceEvaluation {

    // TODO: Can implement each of the various searching and sorting algorithms.

    /*
    * Sorting algorithms
    * 1. Merge Sort
    * 2. Quick Sort
    * 3. Heap Sort
    * ... 
    **/ 

    /*
    * Searching algorithms
    * 1. Linear Search
    * 2. Binary Search 
    **/ 

    class Algorithm {
        public:
            // Linear Search Singly Linked List
            static LinkedListNode*  LinearSearch            (LinkedList&, Search<LinkedList, LinkedListNode*>*, std::string_view, Criteria, SearchType);
            static LinkedList       LinearSearchAndCopy     (LinkedList&, Search<LinkedList, LinkedListNode*>*, std::string_view, Criteria, SearchType);
            static void             LinearSearchAndDisplay  (LinkedList&, Search<LinkedList, LinkedListNode*>*, std::string_view, Criteria, SearchType);
            
            // Binary Search Singly Linked List
            static LinkedListNode*  BinarySearch            (LinkedList&, Search<LinkedList, LinkedListNode*>*, std::string_view, Criteria, SearchType);
            static LinkedList       BinarySearchAndCopy     (LinkedList&, Search<LinkedList, LinkedListNode*>*, std::string_view, Criteria, SearchType);
            static void             BinarySearchAndDisplay  (LinkedList&, Search<LinkedList, LinkedListNode*>*, std::string_view, Criteria, SearchType);
            
            static void SortBy                  (LinkedList&, Sort<LinkedList, LinkedListNode*>*);

            static void SortBy(Array<Dataset>& array, Sort<Array<Dataset>>* sorter);
    };
} // namespace PerformanceEvaluation
