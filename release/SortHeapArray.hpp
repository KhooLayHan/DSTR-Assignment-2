#pragma once

#ifndef SORTHEAPARRAY_H
#define SORTHEAPARRAY_H

#include "./Array.hpp"
#include "./Dataset.hpp"
#include "./Sort.hpp"
#include "./DateUtility.hpp"

namespace PerformanceEvaluation {
    class SortHeapArray : public Sort<Array<Dataset>> {
    public:
        // Function to sort the given array using Heap Sort
        void SortBy(Array<Dataset>& array) override;

    private:
        // Function to build a heap
        void Heapify(Dataset arr[], int n, int i, DateUtility& date_utility);

        // Function to perform Heap Sort
        void HeapSort(Dataset arr[], int n, DateUtility& date_utility);
    };
}

#endif // SORTHEAPARRAY_H
