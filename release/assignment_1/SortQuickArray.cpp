#include "./SortQuickArray.hpp"

namespace PerformanceEvaluation {
    void SortQuickArray::SortBy(Array<Dataset>& array) {
        if (array.Size() > 1) {  // Ensure there's something to sort
            DateUtility date_utility{};
            QuickSort(array.Data(), 0, array.Size() - 1, date_utility);
        }
    }

    // QuickSort function
    void SortQuickArray::QuickSort(Dataset arr[], int low, int high, DateUtility& date_utility) {
        if (low < high) {
            // Partition the array and get pivot index
            int pivotIndex = Partition(arr, low, high, date_utility);

            // Recursively sort elements before and after the pivot
            QuickSort(arr, low, pivotIndex - 1, date_utility);
            QuickSort(arr, pivotIndex + 1, high, date_utility);
        }
    }

    // Partition function
    int SortQuickArray::Partition(Dataset arr[], int low, int high, DateUtility& date_utility) {
        Dataset pivot = arr[high]; // Choosing the last element as pivot
        int i = low - 1; // Index of smaller element

        for (int j = low; j < high; j++) {
            if (CompareAndSortDate(date_utility, arr[j].m_Date, pivot.m_Date)) { // Sorting by Year
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]); // Place pivot at correct position
        return i + 1;
    }
}