#include <iostream>

#include "./SearchLinearDynamicArray.hpp"

#include "./SimpleConsoleLogger.hpp"
#include "./SimpleLoggingService.hpp"

namespace PerformanceEvaluation
{
    // Public API that copies to a new Linked List
    DynamicArray<Dataset> SearchLinearDynamicArray::LinearSearchAndCopy(std::string_view target, const DynamicArray<Dataset>& array, Criteria criteria, SearchType type) {
        DynamicArray<Dataset> new_array;
        
        for (size_t i = 0; i < array.GetLength(); ++i) {
            const Dataset& dataset = array[i];
    
            auto is_found = [&](std::string_view target, std::string_view dataset_str) -> bool {
                if (dataset_str.empty()) {
                    // SimpleConsoleLogger console;
                    // SimpleLoggingService::UseWarnLogger(console, "Criteria to search for target dataset was not specified, defaulted to empty string.");
                } 
                
                return Contains(target, dataset_str, type);
            };
    
            switch (criteria) {
                case Criteria::TITLE:   if (is_found(target, ToLowerCase(dataset.m_Title))) new_array.Insert(new_array.GetLength(), dataset); break;
                case Criteria::TEXT:    if (is_found(target, ToLowerCase(dataset.m_Text))) new_array.Insert(new_array.GetLength(), dataset); break;
                case Criteria::SUBJECT: if (is_found(target, ToLowerCase(dataset.m_Subject))) new_array.Insert(new_array.GetLength(), dataset); break;
                case Criteria::DATE:    if (is_found(target, ToLowerCase(dataset.m_Date))) new_array.Insert(new_array.GetLength(), dataset); break;
                default:                if (is_found(target, "")) new_array.Insert(new_array.GetLength(), dataset); break;
            }
        }
    
        return new_array;
    }

    // // Public API that copies to a new Linked List
    // DynamicArray<std::string> SearchLinearDynamicArray::LinearSearchAndCopy(std::string_view target, const DynamicArray<std::string>& array, Criteria criteria, SearchType type) {
    //     DynamicArray<std::string> new_array;
        
    //     for (size_t i = 0; i < array.GetLength(); ++i) {
    //         const Dataset& dataset = array[i];
    
    //         auto is_found = [&](std::string_view target, std::string_view dataset_str) -> bool {
    //             if (dataset_str.empty()) {
    //                 SimpleConsoleLogger console;
    //                 SimpleLoggingService::UseWarnLogger(console, "Criteria to search for target dataset was not specified, defaulted to empty string.");
    //             } 
                
    //             return Contains(target, dataset_str, type);
    //         };
    
    //         switch (criteria) {
    //             case Criteria::TITLE:   if (is_found(target, ToLowerCase(dataset.m_Title))) new_array.Insert(new_array.GetLength(), dataset); break;
    //             case Criteria::TEXT:    if (is_found(target, ToLowerCase(dataset.m_Text))) new_array.Insert(new_array.GetLength(), dataset); break;
    //             case Criteria::SUBJECT: if (is_found(target, ToLowerCase(dataset.m_Subject))) new_array.Insert(new_array.GetLength(), dataset); break;
    //             case Criteria::DATE:    if (is_found(target, ToLowerCase(dataset.m_Date))) new_array.Insert(new_array.GetLength(), dataset); break;
    //             default:                if (is_found(target, "")) new_array.Insert(new_array.GetLength(), dataset); break;
    //         }
    //     }
    
    //     return new_array;
    // }

    bool SearchLinearDynamicArray::Contains(std::string_view target, std::string_view dataset_str, SearchType type) {
        switch (type) {
            case SearchType::IMPARTIAL: return dataset_str.find(target) != std::string::npos;
            case SearchType::PARTIAL:   return dataset_str == target;
            default:                    return false; 
        };

        return false;
    }

    // To convert an entire string to lowercase
    std::string SearchLinearDynamicArray::ToLowerCase(std::string_view dataset) {
        std::string result;

        for (const auto& character : dataset) {
            result += std::tolower(character);
        }

        return result;
    }
} // namespace PerformanceEvaluation
