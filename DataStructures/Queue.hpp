#pragma once 

#include "../LinkedLists/SinglyLinkedList.hpp"

namespace TCMS 
{
    template <typename T>
    class Queue {
    public:
        void enqueue(T data) {
            list.insert(data);
            
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

            T data = list.getLast();
            list.remove(data);

            return data;
        }

        T front() const {
            if (isEmpty())
                throw std::runtime_error("Queue is empty");
            
            return list.getLast();
        }

        T rear() const {
            if (isEmpty())
                throw std::runtime_error("Queue is empty");
            
            return list.getFirst();
        }

        bool isEmpty() const {
            return list.isEmpty();
        }

        void print() const {
            list.print();
        }
    private:
        SinglyLinkedList<T> list;
    };
} // namepspace TCMS