#pragma once

#include <cmath>

#include "./Array.hpp"
#include "./Dataset.hpp"
#include "./FileHandling.hpp"
#include "./HashMap.hpp"
#include "./HashSet.hpp"
#include "./LinkedList.hpp"
#include "./Vector.hpp"
#include "./WordList.hpp"
#include "./WordListSorted.hpp"

#include "./DynamicArray.hpp"

#include <functional>
namespace PerformanceEvaluation
{
    // Function to count occurrences of words in a WordList and store them in a HashMap
    HashMap<std::string, int32_t> GetWordCount(const WordList&);
    
    // Function to count occurrences of words in a DynamicArray of strings and store them in a HashMap
    HashMap<std::string, int32_t> GetWordCount(const DynamicArray<std::string>&);
 
    // Convert a LinkedList into a WordList using a HashSet for filtering unique words
    WordList ConvertLinkedListToWordList(const LinkedList&, HashSet<std::string>&);

    // Convert a DynamicArray of Dataset objects into a DynamicArray of strings using a HashSet for filtering unique words
    DynamicArray<std::string> ConvertDynamicArrayToWordArray(const DynamicArray<Dataset>&, HashSet<std::string>&);

    // Extract word-count pairs from a HashMap and sort them into a WordListSorted (sorted linked list)
    WordListSorted CheckAndSortHashMapLinkedList(HashMap<std::string, int32_t>&);
    
    // Extract word-count pairs from a HashMap and sort them into a sorted DynamicArray of strings
    DynamicArray<std::string> CheckAndSortHashMapArray(HashMap<std::string, int32_t>&);

    // Structure to represent a key-value pair for word counting
    struct KeyValue {
        std::string m_Key;
        int32_t m_Value;

        // Overloaded assignment operator to allow construction from a std::pair<std::string, int>
        KeyValue& operator=(const std::pair<std::string, int>& p) {
            m_Key = p.first;
            m_Value = p.second;
            return *this;
        }
    };

    // Function to process data from CSV files (true.csv and fake.csv) for linked list processing
    void Question_2_LinkedList_ExtraExclusive(const FilePath& true_file_path = "./CSV/true.csv", const FilePath& fake_file_path = "./CSV/fake.csv");

    // Function to process data from CSV files (true.csv and fake.csv) for array processing
    void Question_2_Array_ExtraExclusive(const FilePath& true_file_path = "./CSV/true.csv", const FilePath& fake_file_path = "./CSV/fake.csv");

    // Function to calculate percentage with precision handling (rounded to 4 decimal places)
    constexpr double CalculatePercentage(size_t numerator, size_t denominator) {
        return denominator == 0 ? 0.0 : std::round((static_cast<double>(numerator) / denominator) * 1000000) / 10000.0;
    }

    // Function to display the first 'size_t' number of elements from a DynamicArray of Datasets
    void DisplayFirst(size_t, const DynamicArray<Dataset>&);

    // Function to display all elements from a DynamicArray of strings
    void DisplayAll(const DynamicArray<std::string>&);

    // Template function to perform Merge Sort on a DynamicArray
    template <typename T>
    void MergeSort(DynamicArray<T>& arr) {
        if (arr.GetLength() <= 1)
            return; // Already sorted

        DynamicArray<T> temp(arr.GetLength()); // Temporary array for merging

        // Lambda function to merge two sorted halves of the array
        auto merge = [](DynamicArray<T>& arr, DynamicArray<T>& temp, size_t left, size_t mid, size_t right) {
            size_t i = left, j = mid + 1, k = left;

            // Merge both halves
            while (i <= mid && j <= right) {
                if (arr[i] <= arr[j])
                    temp[k++] = arr[i++];
                else
                    temp[k++] = arr[j++];
            }

            // Copy any remaining elements from left subarray
            while (i <= mid)
                temp[k++] = arr[i++];

            // Copy any remaining elements from right subarray
            while (j <= right)
                temp[k++] = arr[j++];

            // Copy sorted elements back into original array
            for (size_t idx = left; idx <= right; idx++)
                arr[idx] = temp[idx];
        };

        // Recursive function to divide and sort the array
        std::function<void(DynamicArray<T>&, DynamicArray<T>&, size_t, size_t)> mergeSortHelper =
            [&](DynamicArray<T>& arr, DynamicArray<T>& temp, size_t left, size_t right) {
                if (left >= right)
                    return;

                size_t mid = left + (right - left) / 2;
                mergeSortHelper(arr, temp, left, mid);
                mergeSortHelper(arr, temp, mid + 1, right);
                merge(arr, temp, left, mid, right);
            };

        // Start merge sort
        mergeSortHelper(arr, temp, 0, arr.GetLength() - 1);
    }
} // namespace PerformanceEvaluation
