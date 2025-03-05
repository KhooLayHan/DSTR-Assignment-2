#include "./SortHeapArray.hpp"

namespace PerformanceEvaluation {
    void SortHeapArray::SortBy(Array<Dataset>& array) {
        if (array.Size() > 1) {  // Ensure there's something to sort
            DateUtility date_utility{};
            HeapSort(array.Data(), array.Size(), date_utility);
        }
    }

    // Heapify function to maintain the max heap property
    void SortHeapArray::Heapify(Dataset arr[], int n, int i, DateUtility& date_utility) {
        int largest = i; // Initialize largest as root
        int left = 2 * i + 1; // Left child
        int right = 2 * i + 2; // Right child

        // Compare left child with root
        if (left < n && CompareAndSortDate(date_utility, arr[largest].m_Date, arr[left].m_Date)) {
            largest = left;
        }

        // Compare right child with largest so far
        if (right < n && CompareAndSortDate(date_utility, arr[largest].m_Date, arr[right].m_Date)) {
            largest = right;
        }

        // If largest is not root, swap and continue heapifying
        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            Heapify(arr, n, largest, date_utility);
        }
    }

    // Heap Sort function
    void SortHeapArray::HeapSort(Dataset arr[], int n, DateUtility& date_utility) {
        // Build heap (rearrange array)
        for (int i = n / 2 - 1; i >= 0; i--) {
            Heapify(arr, n, i, date_utility);
        }

        // Extract elements one by one
        for (int i = n - 1; i > 0; i--) {
            // Move current root to end
            std::swap(arr[0], arr[i]);

            // Call Heapify on the reduced heap
            Heapify(arr, i, 0, date_utility);
        }
    }
}
