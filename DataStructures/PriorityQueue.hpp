#pragma once 

#include "../LinkedLists/DoublyLinkedList.hpp"

namespace TCMS 
{
    template <typename T>
    class PriorityQueue : private DoublyLinkedList<T> {
    public:
        using Base = LinkedListNode<T, DoublyLinkedListNode<T>>;
        using Base::m_Head;
        using Base::downcast;

        void insert(T data, int32_t priority) {
            DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(data, nullptr, nullptr);
            newNode->setData(priority);

            if (m_Head == nullptr || DowncastDoublyLinkedListNode(m_Head)->getData() < priority) {
                newNode->setNext(m_Head);

                if (m_Head != nullptr)
                    DowncastDoublyLinkedListNode(m_Head)->setPrevious(newNode);
                
                m_Head = newNode;
            } else {
                DoublyLinkedListNode<T>* current = DowncastDoublyLinkedListNode(m_Head);

                while (current->getNext() != nullptr && DowncastDoublyLinkedListNode(current->getNext())->getData() >= priority)
                    current = DowncastDoublyLinkedListNode(current->getNext());
                
                newNode->setNext(current->getNext());

                if (current->getNext() != nullptr) 
                    DowncastDoublyLinkedListNode(current->getNext())->setPrevious(newNode);
                
                current->setNext(newNode);
                newNode->setPrevious(current);
            }
        }

        T removeHighestPriority() {
            if (m_Head == nullptr)
                throw std::runtime_error("Priority Queue is empty");
            
            T data = m_Head->getData();
            remove(data);

            return data;
        }

        void print() const {
            DoublyLinkedList<T>::print();
        }
    private:
        SinglyLinkedListNode<T>* m_Tail;
    };
} // namepspace TCMS