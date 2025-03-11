#pragma once 

#include <iostream>

#include "../LinkedLists/DoublyLinkedList.hpp"

namespace TCMS 
{
    template <typename T>
    class PriorityQueue {
    private:
        struct PriorityItem {
            T m_Data;
            int32_t m_Priority;

            bool operator==(const PriorityItem& other) const {
                return m_Data == other.m_Data && m_Priority == other.m_Priority;
            } 

            friend std::ostream& operator<<(std::ostream& output_stream, const PriorityItem& item) {
                output_stream << "(" << item.m_Data << ", " << item.m_Priority << ")"; 
                return output_stream;
            }
        };
    public:
        void enqueue(T data, int32_t priority) {
            PriorityItem newNode = { data, priority };

            if (isEmpty()) {
                m_List.insertBegin(newNode);
                return;
            }

            size_t position = 0;
            DoublyLinkedListNode<PriorityItem>* current = 
                static_cast<DoublyLinkedListNode<PriorityItem>*>(m_List.getHeadBase());

            while (current != nullptr && current->getData().m_Priority <= priority) {
                position++;
                current = current->getNext();
            }

            m_List.insertPosition(newNode, position);
        }

        T dequeue() {
            if (isEmpty()) 
                throw std::runtime_error("PriorityQueue is empty");
            
            T highestPriorityData = m_List.getFirst().m_Data;
            m_List.removeBegin();

            return highestPriorityData;
        }

        T peekFront() const {
            if (isEmpty()) 
                throw std::runtime_error("PriorityQueue is empty");
            
            return m_List.getFirst().m_Data;
        }

        T peekBack() const {
            if (isEmpty()) 
                throw std::runtime_error("PriorityQueue is empty");
            
            return m_List.getLast().m_Data;
        }

        // void insert(T data, int32_t priority) {
        //     DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(data, nullptr, nullptr);
        //     newNode->setData(priority);

        //     if (m_Head == nullptr || DowncastDoublyLinkedListNode(m_Head)->getData() < priority) {
        //         newNode->setNext(m_Head);

        //         if (m_Head != nullptr)
        //             DowncastDoublyLinkedListNode(m_Head)->setPrevious(newNode);
                
        //         m_Head = newNode;
        //     } else {
        //         DoublyLinkedListNode<T>* current = DowncastDoublyLinkedListNode(m_Head);

        //         while (current->getNext() != nullptr && DowncastDoublyLinkedListNode(current->getNext())->getData() >= priority)
        //             current = DowncastDoublyLinkedListNode(current->getNext());
                
        //         newNode->setNext(current->getNext());

        //         if (current->getNext() != nullptr) 
        //             DowncastDoublyLinkedListNode(current->getNext())->setPrevious(newNode);
                
        //         current->setNext(newNode);
        //         newNode->setPrevious(current);
        //     }
        // }

        // T removeHighestPriority() {
        //     if (m_Head == nullptr)
        //         throw std::runtime_error("Priority Queue is empty");
            
        //     T data = m_Head->getData();
        //     remove(data);

        //     return data;
        // }

        bool isEmpty() const {
            return m_List.isEmpty();
        }

        void print() const {
            // DoublyLinkedList<T>::print();

            DoublyLinkedListNode<PriorityItem>* current = 
                static_cast<DoublyLinkedListNode<PriorityItem>*>(m_List.getHeadBase());
            std::cout << "Priority Queue (Data, Priority): ";

            while (current != nullptr) {
                std::cout << "(" << current->getData().m_Data << ", "
                    << current->getData().m_Priority << ") -> ";

                current = current->getNext();
            }

            std::cout << "nullptr\n";

        }
    private:
        DoublyLinkedList<PriorityItem> m_List;
    };
} // namepspace TCMS