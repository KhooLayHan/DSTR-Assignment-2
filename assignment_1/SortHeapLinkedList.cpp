#include "./SortHeapLinkedList.hpp"

namespace PerformanceEvaluation {
    void SortHeapLinkedList::SortBy(LinkedList& linked_list) {
        linked_list.SetHead(HeapSort(linked_list.GetHead())); // Use returned new_head
    }


    // Heap Sort function
    LinkedListNode* SortHeapLinkedList::HeapSort(LinkedListNode* head) {
        if (!head || !head->m_Next) return head;

        size_t length = GetLength(head);
        LinkedListNode** arr = new LinkedListNode*[length];

        // Convert linked list to array
        LinkedListNode* temp = head;
        for (size_t i = 0; i < length; i++) {
            arr[i] = temp;
            temp = temp->m_Next;
        }

        // Build the min heap
        for (int i = length / 2 - 1; i >= 0; i--) {
            Heapify(arr, length, i);
        }

        // Extract elements from heap one by one
        for (int i = length - 1; i > 0; i--) {
            std::swap(arr[0], arr[i]);
            Heapify(arr, i, 0);
        }

        // Reconstruct linked list
        for (size_t i = 0; i < length - 1; i++) {
            arr[i]->m_Next = arr[i + 1];
        }
        arr[length - 1]->m_Next = nullptr;

        LinkedListNode* new_head = arr[0];
        delete[] arr;
        return new_head;
    }

    // Min-heap for ascending order, ensures the smallest element is always at the top
    void SortHeapLinkedList::Heapify(LinkedListNode** arr, int n, int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        DateUtility date_utility;

        if (left < n && CompareAndSortDate(date_utility, arr[left]->m_Data.m_Date, arr[smallest]->m_Data.m_Date)) {
            smallest = left;
        }

        if (right < n && CompareAndSortDate(date_utility, arr[right]->m_Data.m_Date, arr[smallest]->m_Data.m_Date)) {
            smallest = right;
        }

        if (smallest != i) {
            std::swap(arr[i], arr[smallest]);
            Heapify(arr, n, smallest);
        }
    }

    // Function to count the length of the linked list
    size_t SortHeapLinkedList::GetLength(LinkedListNode* head) {
        size_t length = 0;
        while (head) {
            length++;
            head = head->m_Next;
        }
        return length;
    }
} // namespace PerformanceEvaluation
