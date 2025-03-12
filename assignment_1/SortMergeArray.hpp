#pragma once

#ifndef SORTMERGEARRAY_H
#define SORTMERGEARRAY_H

#include "./Array.hpp"
#include "./Dataset.hpp"
#include "./Sort.hpp"

namespace PerformanceEvaluation {
    class SortMergeArray : public Sort<Array<Dataset>> {
    public:
        // Function to sort the given array using merge sort
        void SortBy(Array<Dataset>& array) override;

    private:
        // Helper function for merge sort
        void MergeSort(Dataset arr[], int left, int right);

        // Function to merge two halves
        void Merge(Dataset arr[], int left, int mid, int right);
    };
}
#endif // SORTMERGEARRAY_H

