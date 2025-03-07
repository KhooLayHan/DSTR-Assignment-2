#include "./SortMergeArray.hpp"

namespace PerformanceEvaluation {
    void SortMergeArray::SortBy(Array<Dataset>& array) {
        if (array.Size() > 1) {  // Ensure there's something to sort
            MergeSort(array.Data(), 0, array.Size() - 1);
        }
    }
    
    // Merge function to combine two sorted halves
    void SortMergeArray::Merge(Dataset arr[], int left, int mid, int right) {
        DateUtility date_utility{};

        int leftSize = mid - left + 1;
        int rightSize = right - mid;

        // Create temporary arrays
        Dataset* leftArr = new Dataset[leftSize];
        Dataset* rightArr = new Dataset[rightSize];

        // Copy data to temporary arrays
        for (int i = 0; i < leftSize; i++)
            leftArr[i] = arr[left + i];

        for (int i = 0; i < rightSize; i++)
            rightArr[i] = arr[mid + 1 + i];

        // Merge the temp arrays back into arr[left...right]
        int i = 0, j = 0, k = left;
        while (i < leftSize && j < rightSize) {
            if (CompareAndSortDate(date_utility, leftArr[i].m_Date, rightArr[j].m_Date)
        ) {  // Sorting by Year
                arr[k] = leftArr[i];
                i++;
            } else {
                arr[k] = rightArr[j];
                j++;
            }
            k++;
        }

        // Copy remaining elements of leftArr[], if any
        while (i < leftSize) {
            arr[k] = leftArr[i];
            i++;
            k++;
        }

        // Copy remaining elements of rightArr[], if any
        while (j < rightSize) {
            arr[k] = rightArr[j];
            j++;
            k++;
        }

        // Free allocated memory
        delete[] leftArr;
        delete[] rightArr;
    }

    // Merge Sort function
    void SortMergeArray::MergeSort(Dataset arr[], int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            // Sort first and second halves
            MergeSort(arr, left, mid);
            MergeSort(arr, mid + 1, right);

            // Merge the sorted halves
            Merge(arr, left, mid, right);
        }
    }
} // namespace PerformanceEvaluation
