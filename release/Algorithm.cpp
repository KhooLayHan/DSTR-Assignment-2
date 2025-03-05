#include "./Algorithm.hpp"

namespace PerformanceEvaluation {
    // Singly Linked List Linear Search
    LinkedListNode* Algorithm::LinearSearch(LinkedList& linked_list, Search<LinkedList, LinkedListNode*>* search_interface, std::string_view target, Criteria criteria, SearchType type) {
        if (search_interface) {
            return search_interface->UseLinearSearchAlgorithm(target, linked_list, criteria, type);
        }

        return nullptr;
    }

    // Performs a linear search and returns a copy of the matched elements in a new LinkedList
    LinkedList Algorithm::LinearSearchAndCopy(LinkedList& linked_list, Search<LinkedList, LinkedListNode*>* search_interface, std::string_view target, Criteria criteria, SearchType type) {
        if (search_interface) {
            return search_interface->UseLinearSearchAndCopyAlgorithm(target, linked_list, criteria, type);
        }

        return {};
    }
    
    // Performs a linear search and displays the matched elements
    void Algorithm::LinearSearchAndDisplay(LinkedList& linked_list, Search<LinkedList, LinkedListNode*>* search_interface, std::string_view target, Criteria criteria, SearchType type) {
        if (search_interface) {
            search_interface->UseLinearSearchAndDisplayAlgorithm(target, linked_list, criteria, type);
        }
    }
    
    // Singly Linked List Binary Search
    LinkedListNode* Algorithm::BinarySearch(LinkedList& linked_list, Search<LinkedList, LinkedListNode*>* search_interface, std::string_view target, Criteria criteria, SearchType type) {
        if (search_interface) {
            return search_interface->UseBinarySearchAlgorithm(target, linked_list, criteria, type);
        }
        
        return nullptr;
    }
    
    // Performs a binary search and returns a copy of the matched elements in a new LinkedList
    LinkedList Algorithm::BinarySearchAndCopy(LinkedList& linked_list, Search<LinkedList, LinkedListNode*>* search_interface, std::string_view target, Criteria criteria, SearchType type) {
        if (search_interface) {
            return search_interface->UseBinarySearchAndCopyAlgorithm(target, linked_list, criteria, type);
        }

        return {};
    }
    
    // Performs a binary search and displays the matched elements
    void Algorithm::BinarySearchAndDisplay(LinkedList& linked_list, Search<LinkedList, LinkedListNode*>* search_interface, std::string_view target, Criteria criteria, SearchType type) {
        if (search_interface) {
            search_interface->UseBinarySearchAndDisplayAlgorithm(target, linked_list, criteria, type);
        }
    }

    // Sorting methods for LinkedLists and Arrays

    // Sorts a LinkedList using an external sorting interface
    void Algorithm::SortBy(LinkedList& linked_list, Sort<LinkedList, LinkedListNode*>* sort_interface) {
        if (sort_interface) {
            sort_interface->UseSortingAlgorithm(linked_list);
        }
    }

    // Sorts an Array of Datasets using an external sorting interface
    void Algorithm::SortBy(Array<Dataset>& array, Sort<Array<Dataset>>* sorter) {
        if (sorter) {
            sorter->UseSortingAlgorithm(array);
        }
    }
} // namespace PerformanceEvaluation
