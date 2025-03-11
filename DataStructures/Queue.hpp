#pragma once 

#include "../LinkedLists/SinglyLinkedList.hpp"

namespace TCMS 
{
    template <typename T>
    class Queue {
    public:
        void enqueue(T data) {
            m_List.insertEnd(data);
            
            // SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data);

            // if (m_Head == nullptr) {
            //     m_Head = newNode;
            //     m_Tail = newNode;
            // } else {
            //     m_Tail->setNext(newNode);
            //     m_Tail = newNode;
            // }
        }

        T dequeue() {
            if (isEmpty()) 
                throw std::runtime_error("Queue is empty");

            T frontData = m_List.getFirst();
            m_List.removeBegin();

            return frontData;
        }

        T peekFront() const {
            if (isEmpty())
                throw std::runtime_error("Queue is empty");
            
            return m_List.getFirst();
        }

        T peekBack() const {
            if (isEmpty())
                throw std::runtime_error("Queue is empty");
            
            return m_List.getLast();
        }

        bool isEmpty() const {
            return m_List.isEmpty();
        }

        void print() const {
            std::cout << "Queue (front -> back): ";
            m_List.print();
        }
    private:
        SinglyLinkedList<T> m_List;
    };
} // namepspace TCMS