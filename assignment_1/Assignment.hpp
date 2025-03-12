#pragma once

#include <string>

// Struct with member variables: title, text, subject, date
#include "./Dataset.hpp"

// Data structures
#include "./Array.hpp"
// #include "./WordList.hpp"
#include "./LinkedList.hpp"

// Search and sort algorithms 
#include "./Algorithm.hpp"

// Benchmarking
#include "./Benchmark.hpp"

#include <future>
#include <memory>

// File handling
#include "./FileHandling.hpp"

// Helper classes for debugging and parsing dates
#include "./DateUtility.hpp"
#include "./SimpleLogger.hpp"

#include "./Benchmark.hpp"
#include "./SearchLinearLinkedList.hpp"
#include "./SearchBinaryLinkedList.hpp"
// #include "./SearchWordList.hpp"
#include "./SortMergeLinkedList.hpp"
#include "./SortQuickLinkedList.hpp"
#include "./SortHeapLinkedList.hpp"

#include "./SortMergeArray.hpp"
#include "./SortQuickArray.hpp"
#include "./SortHeapArray.hpp"

#include "./Sort.hpp"

#include "./ConversionUtility.hpp"
#include "./HashMap.hpp"
// #include "./HashMap.hpp"

#include "./WordList.hpp"
#include "./WordListSorted.hpp"

#include "./HashSet.hpp"
#include "./Vector.hpp"
#include "./DynamicArray.hpp"

#include "./SearchLinearDynamicArray.hpp"
namespace PerformanceEvaluation {
    class Assignment {
        public:
            /**
             * Problem Statement 1:
             * How can you efficiently sort the news articles by year and 
             * display the total number of articles in both datasets? 
             */
            static void Question_1_Array();
            static void Question_1_LinkedList();

            /**
             * Problem Statement 2:
             * What percentage of political news articles (including fake and true news) 
             * from the year of 2016 are fake?  
             */
            static void Question_2_Array();
            static void Question_2_LinkedList();

            /**
             * Problem Statement 3:
             * Which words are most frequently used in fake news articles 
             * related to government topics?
             */
            static void Question_3_Array();
            static void Question_3_LinkedList();
    }; // class Assignment
} // namespace PerformanceEvaluation