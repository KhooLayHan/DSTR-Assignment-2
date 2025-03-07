#pragma once 

#include "../LinkedList/SinglyLinkedList.hpp"

namespace TCMS {
    template <typename T>
    class Queue : private SinglyLinkedList<T> {
    public:
        Queue() : SinglyLinkedList<T>(), m_Tail(nullptr) {

        }

        void enqueue(T data) {
            SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data);

            if (m_Head == nullptr) {
                m_Head = newNode;
                m_Tail = newNode;
            } else {
                m_Tail->setNext(newNode);
                m_Tail = newNode;
            }
        }

        T dequeue() {
            if (m_Head == nullptr) 
                throw std::runtime_error("Queue is empty");

            T data = m_Head->getData();
            remove(data);

            return data;
        }

        T peek() const {
            if (m_Head == nullptr)
                throw std::runtime_error("Queue is empty");
            
            return m_Head->getData();
        }

        void print() const {
            SinglyLinkedList<T>::print();
        }
    private:
        SinglyLinkedListNode<T>* m_Tail;
    };
} // namepspace TCMS