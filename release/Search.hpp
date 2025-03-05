#pragma once

#include <string>
#include <string_view>

#include "./Array.hpp"
#include "./LinkedList.hpp"
#include "./WordList.hpp"

namespace PerformanceEvaluation
{
    enum class SearchType {
        PARTIAL = 0,
        IMPARTIAL = 1,
    };

    template<typename T, typename N = void>
    class Search {
        public:
            // Linear Search Linked List
            N UseLinearSearchAlgorithm(std::string_view target, const T& linked_list, Criteria criteria, SearchType type) {
                return LinearSearch(target, linked_list, criteria, type);
            }
            
            T UseLinearSearchAndCopyAlgorithm(std::string_view target, const T& linked_list, Criteria criteria, SearchType type) {
                return LinearSearchAndCopy(target, linked_list, criteria, type);
            }
            
            void UseLinearSearchAndDisplayAlgorithm(std::string_view target, const T& linked_list, Criteria criteria, SearchType type) {
                LinearSearchAndDisplay(target, linked_list, criteria, type);
            }
            
            // Binary Search Linked List
            N UseBinarySearchAlgorithm(std::string_view target, const T& linked_list, Criteria criteria, SearchType type) {
                return BinarySearch(target, linked_list, criteria, type);
            }
            
            T UseBinarySearchAndCopyAlgorithm(std::string_view target, const T& linked_list, Criteria criteria, SearchType type) {
                return BinarySearchAndCopy(target, linked_list, criteria, type);
            }
            
            void UseBinarySearchAndDisplayAlgorithm(std::string_view target, const T& linked_list, Criteria criteria, SearchType type) {
                BinarySearchAndDisplay(target, linked_list, criteria, type);
            }
                     
            virtual ~Search() = default;
        protected:
            constexpr bool Contains(std::string_view target, std::string_view dataset_str, SearchType type) {
                switch (type) {
                    case SearchType::IMPARTIAL: return dataset_str.find(target) != std::string::npos;
                    case SearchType::PARTIAL:   return dataset_str == target;
                    default:                    return false; 
                };

                return false;
            }

            // Custom Transform function inspired by std::transform()
            template <typename InputIterator, typename OutputIterator, typename UnaryFunction>
            void Transform(InputIterator first, InputIterator last, OutputIterator out, UnaryFunction func) {
                while (first != last) {
                    (*out)++ = func((*first)++); // Apply function and copy the result
                }
            }

            // To convert an entire string to lowercase
            constexpr std::string ToLowerCase(std::string_view dataset) {
                std::string result;
  
                for (const auto& character : dataset) {
                    result += std::tolower(character);
                }

                return result;
            }

        private:
            virtual N       LinearSearch            (std::string_view, const T&, Criteria, SearchType) = 0;
            virtual T       LinearSearchAndCopy     (std::string_view, const T&, Criteria, SearchType) = 0;
            virtual void    LinearSearchAndDisplay  (std::string_view, const T&, Criteria, SearchType) = 0;
            
            virtual N       BinarySearch            (std::string_view, const T&, Criteria, SearchType) = 0;
            virtual T       BinarySearchAndCopy     (std::string_view, const T&, Criteria, SearchType) = 0;
            virtual void    BinarySearchAndDisplay  (std::string_view, const T&, Criteria, SearchType) = 0;
    };
} // namespace PerformanceEvaluation
