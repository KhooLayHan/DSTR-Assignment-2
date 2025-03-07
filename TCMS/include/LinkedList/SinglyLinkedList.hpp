#pragma once

#include <iostream>

#include "LinkedList.hpp"
#include "SinglyLinkedListNode.hpp"

namespace TCMS
{
    template <typename T>
    class SinglyLinkedList : public LinkedList<T> {
    public:
        void insert(T data) override {
            LinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data, m_Head);
            m_Head = newNode;
        };

        void remove(T data) override {
            if (m_Head == nullptr)
                return;

            if (m_Head->getData() == data) {
                LinkedListNode<T> temp = m_Head;
                m_Head = m_Head->getNext();

                delete temp;
                temp = nullptr;

                return;
            }

            LinkedListNode<T>* current = m_Head;

            while (current->getNext() != nullptr) {
                if (current->getNext()->getData() == data) {
                    LinkedListNode<T>* temp = current->getNext();
                    current->setNext(current->getNext()->getNext());

                    delete temp;
                    temp = nullptr;

                    return;
                }

                current = current->getNext();
            }
        };
        
        void print() const override {
            LinkedListNode<T>* current = m_Head;

            while (current != nullptr) {
                std::cout << current->getData() << "\n";
                current = current->getNext();
            }

            std::cout << "\n";
        };
    };
} // namespace TCMS


