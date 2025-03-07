#pragma once

#include "./DynamicArray.hpp"
#include "./Dataset.hpp"

#include "./Search.hpp"

namespace PerformanceEvaluation
{
    class SearchLinearDynamicArray {
        public:
            // Public API that copies to a new Dynamic Array
            static DynamicArray<Dataset>   LinearSearchAndCopy     (std::string_view, const DynamicArray<Dataset>&, Criteria, SearchType);

        protected:
            // Custom Transform function inspired by std::transform()
            template <typename InputIterator, typename OutputIterator, typename UnaryFunction>
            void Transform(InputIterator first, InputIterator last, OutputIterator out, UnaryFunction func) {
                while (first != last) {
                    (*out)++ = func((*first)++); // Apply function and copy the result
                }
            }

            static bool Contains(std::string_view, std::string_view, SearchType);
            static std::string ToLowerCase(std::string_view);
    };
} // namespace PerformanceEvaluation
