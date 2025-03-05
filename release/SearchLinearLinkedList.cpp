#include <iostream>

#include "./SearchLinearLinkedList.hpp"

#include "./SimpleConsoleLogger.hpp"
#include "./SimpleLoggingService.hpp"

namespace PerformanceEvaluation
{
    // Public API that returns a LinkedListNode object
    LinkedListNode* SearchLinearLinkedList::LinearSearch(std::string_view target, const LinkedList& linked_list, Criteria criteria, SearchType type) {
        LinkedListNode* temp = linked_list.GetHead();
        
        while (temp) {
            const Dataset& dataset = temp->m_Data;

            auto is_found = [&, temp](std::string_view target, std::string_view dataset_str) {
                if (dataset_str.empty()) {
                    // SimpleConsoleLogger console;
                    // SimpleLoggingService::UseWarnLogger(console, "Criteria to search for target node was not specified, defaulted to empty string.");
                } 
                
                return Contains(target, dataset_str, type) ? temp : nullptr;
            };

            switch (criteria) {
                case Criteria::TITLE:   is_found(target, ToLowerCase(dataset.m_Title));      break;
                case Criteria::TEXT:    is_found(target, ToLowerCase(dataset.m_Text));       break;
                case Criteria::SUBJECT: is_found(target, ToLowerCase(dataset.m_Subject));    break;
                case Criteria::DATE:    is_found(target, ToLowerCase(dataset.m_Date));       break;
                default:                is_found(target, "");
            }

            temp = temp->m_Next;
        }

        return nullptr;
    } 

    // Public API that copies to a new Linked List
    LinkedList SearchLinearLinkedList::LinearSearchAndCopy(std::string_view target, const LinkedList& linked_list, Criteria criteria, SearchType type) {
        LinkedList new_list;
        LinkedListNode* new_tail = nullptr;
        LinkedListNode* temp = linked_list.GetHead();

        while (temp) {
            const Dataset& dataset = temp->m_Data;
                
            auto is_found_and_copy = [&, temp](std::string_view target, std::string_view dataset_str) {
                if (dataset_str.empty()) {
                    // SimpleConsoleLogger console;
                    // SimpleLoggingService::UseWarnLogger(console, "Criteria to search for target node was not specified, defaulted to empty string.");
                }
                
                if (Contains(target, dataset_str, type)) {
                    LinkedListNode* new_node = new LinkedListNode(temp->m_Data); // Deep copy
                    
                    if (!new_list.GetHead()) {
                        new_list.InsertEnd(new_node->m_Data);
                        new_tail = new_list.GetHead();
                    } else {
                        new_tail->m_Next = new_node;
                        new_tail = new_node;
                        
                        // new_list.setLength(++i);
                    }
                }
            };

            switch (criteria) {
                case Criteria::TITLE:   is_found_and_copy(target, ToLowerCase(dataset.m_Title));   break;
                case Criteria::TEXT:    is_found_and_copy(target, ToLowerCase(dataset.m_Text));    break;
                case Criteria::SUBJECT: is_found_and_copy(target, ToLowerCase(dataset.m_Subject)); break;
                case Criteria::DATE:    is_found_and_copy(target, ToLowerCase(dataset.m_Date));    break;
                default:                is_found_and_copy(target, "");
            }

            temp = temp->m_Next;
        }

        return new_list;
    }

    // Public function to perform linear search and display results
    void SearchLinearLinkedList::LinearSearchAndDisplay(std::string_view target, const LinkedList& linked_list, Criteria criteria, SearchType type) {
        LinkedListNode* temp = linked_list.GetHead();
                
        while (temp) {
            const Dataset& dataset = temp->m_Data;
                
            auto is_found_and_display = [&, temp](std::string_view target, std::string_view dataset_str) {
                if (dataset_str.empty()) {
                    // SimpleConsoleLogger console;
                    // SimpleLoggingService::UseWarnLogger(console, "Criteria to search for target node was not specified, defaulted to empty string.");
                }
                
                if (Contains(target, dataset_str, type)) {
                    dataset.Display();
                }
            };

            switch (criteria) {
                case Criteria::TITLE:   is_found_and_display(target, ToLowerCase(dataset.m_Title));   break;
                case Criteria::TEXT:    is_found_and_display(target, ToLowerCase(dataset.m_Text));    break;
                case Criteria::SUBJECT: is_found_and_display(target, ToLowerCase(dataset.m_Subject)); break;
                case Criteria::DATE:    is_found_and_display(target, ToLowerCase(dataset.m_Date));    break;
                default:                is_found_and_display(target, "");
            }

            temp = temp->m_Next;
        }
    }
} // namespace PerformanceEvaluation
