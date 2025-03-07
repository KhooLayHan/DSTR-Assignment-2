#pragma once

#ifndef LINKED_LIST_CLONER_HPP
#define LINKED_LIST_CLONER_HPP

namespace PerformanceEvaluation {
    // Sourced from ChatGPT

    // Generic LinkedListNode structure to ensure compatibility with Singly, Doubly, and Circular Linked List
    template <typename T>
    struct LinkedListNode {
        T m_Data;
        LinkedListNode* m_Next;
        LinkedListNode* m_Previous; // Is used for Doubly Linked List (can be ignored for Singly)
        
        LinkedListNode(T data) : m_Data(data), m_Next(nullptr), m_Previous(nullptr) {

        }
    };

    template <typename T>
    class LinkedListCloner {
        // To clone or deep copy a Linked List from a given node 
        static LinkedListNode<T>* Copy(LinkedListNode<T>* start_node) {
            if (!start_node)
                return nullptr;

            LinkedListNode<T>* new_head = new LinkedListNode<T>(start_node->m_Data);
            LinkedListNode<T>* current = new_head;
            LinkedListNode*<T>* original = start_node->m_Next;

            while (original) {
                LinkedListNode<T>* new_node = new LinkedListNode<T>(original->m_Data);
                current->m_Next = new_node;
                new_node->m_Previous = current; // Maintains "previous" links for double linked list
                current = new_node;
                original = original->m_Next;
            }

            return new_head;
        }

        static ListNode<T>* CopyCircular(ListNode<T>* start_node) {
            if (!start_node)
                return nullptr;

            ListNode<T>* new_head = new ListNode<T>(start_node->m_Data);
            ListNode<T>* current = new_head;
            ListNode<T>* original = start_node->m_Next;

            while (original && original != start_node) {
                ListNode<T>* new_node = new ListNode<T>(original->m_Data);
                current->m_Next = new_node;
                new_node->m_Previous = current;
                current = new_node;
                original = original->m_Next;
            }

            current->m_Next = new_head; // Making it circular
            new_head->m_Previous = current;
            
            return new_head;
        }
    };
}

#endif