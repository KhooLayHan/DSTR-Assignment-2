#pragma once

#ifndef SORT_HPP
#define SORT_HPP

#include "./DateUtility.hpp"

#include "./Array.hpp"
#include "./LinkedList.hpp"
#include "./WordList.hpp"

namespace PerformanceEvaluation
{
    template<typename T, typename N = void>
    class Sort {
        public:
            void UseSortingAlgorithm(T& linked_list) {
                SortBy(linked_list);
            }

            virtual ~Sort() = default;
        protected:
            virtual void SortBy(T&) = 0;

            constexpr auto CompareAndSortDate(const DateUtility& date_utility, const std::string& first_date, const std::string& second_date) {
                const auto& [left_day, left_month, left_year] = date_utility.ParseDate(first_date);
                const auto& [right_day, right_month, right_year] = date_utility.ParseDate(second_date);
            
                return std::tie(left_year, left_month, left_day) <= std::tie(right_year, right_month, right_day);
            };

            // Ascending order
            constexpr auto Compare(const std::string& first_word, const std::string& second_word) {
                return first_word > second_word;
            };
    };
} // namespace PerformanceEvaluation

#endif 