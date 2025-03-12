#pragma once

#ifndef SORTQUICKARRAY_H
#define SORTQUICKARRAY_H

#include "./Array.hpp"
#include "./Dataset.hpp"
#include "./Sort.hpp"
#include "./DateUtility.hpp"

namespace PerformanceEvaluation {
    class SortQuickArray : public Sort<Array<Dataset>> {
    public:
        // Function to sort the given array using quicksort
        void SortBy(Array<Dataset>& array) override;

    private:
        // Helper function for quicksort
        void QuickSort(Dataset arr[], int low, int high, DateUtility& date_utility);

        // Function to partition the array
        int Partition(Dataset arr[], int low, int high, DateUtility& date_utility);
    };
}

#endif // SORTQUICKARRAY_H