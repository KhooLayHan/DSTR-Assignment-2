#pragma once

#include <functional>
#include <utility>  // for std::swap
#include "../core/utils/Assert.hpp"

namespace TCMS {
    class Sort {
    public:
        // QuickSort with custom comparator
        template <typename RandomAccessIterator, typename Compare>
        static void quickSort(RandomAccessIterator begin, RandomAccessIterator end, Compare comp) {
            Assert::runtimeAssert(begin <= end, "Sorting an empty range is not allowed!");
            if (begin < end - 1) { // Ensure there are at least 2 elements
                auto pivot = partition(begin, end, comp);
                quickSort(begin, pivot, comp);
                quickSort(pivot + 1, end, comp);
            }
        }

        // BubbleSort with custom comparator
        template <typename RandomAccessIterator, typename Compare>
        static void bubbleSort(RandomAccessIterator begin, RandomAccessIterator end, Compare comp) {
            Assert::runtimeAssert(begin != end, "Sorting an empty range is not allowed!");
            for (auto i = begin; i < end - 1; ++i) {
                for (auto j = begin; j < end - 1 - (i - begin); ++j) {
                    if (!comp(*j, *(j + 1))) { // Use comparator
                        std::swap(*j, *(j + 1));
                    }
                }
            }
        }

    private:
        // Partition function for QuickSort (with custom comparator)
        template <typename RandomAccessIterator, typename Compare>
        static RandomAccessIterator partition(RandomAccessIterator low, RandomAccessIterator high, Compare comp) {
            auto pivot = *(high - 1);
            std::cout << "GGG\n";
            // std::cout << high;
            // std::cout << low;
            auto i = low - 1;
            std::cout << "LLLL\n";
            for (auto j = low; j < high - 1; ++j) {
                if (comp(*j, pivot)) { // Use comparator
                    std::swap(*i, *j);
                    ++i;
                }
            }
            std::swap(*(i), *(high - 1));
            return i + 1;
        }
    };
} // namespace TCMS
