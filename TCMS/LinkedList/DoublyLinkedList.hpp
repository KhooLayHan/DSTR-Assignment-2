#pragma once

#include <iostream>

#include "LinkedList.hpp"
#include "DoublyLinkedListNode.hpp"

namespace TCMS
{
    template <typename T>
    class DoublyLinkedList : public LinkedList<T> {
    public:
        void insert(T data) override {
            LinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(data, m_Head, nullptr);

            if (m_Head != nullptr) {
                static_cast<DoublyLinkedListNode<T>*>(m_Head)->setPrevious(newNode);
            }

            this->m_Head = newNode;
        };

        void remove(T data) override {
            if (m_Head == nullptr)
                return;

            LinkedListNode<T>* current = m_Head;

            while (current != nullptr) {
                if (current->getData() == data) {
                    if (current->getPrevious() != nullptr) {
                        static_cast<DoublyLinkedListNode<T>*>(current->getPrevious())->setNext(current->getNext());
                    } else {
                        m_Head = current->getNext();
                    }

                    if (current->getNext() != nullptr) {
                        static_cast<DoublyLinkedListNode<T>*>(current->getNext())->setPrevious(current->getPrevious());
                    }

                    delete current;
                    current = nullptr;

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