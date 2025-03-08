#pragma once

#include <iostream>

#include "LinkedList.hpp"
#include "DoublyLinkedListNode.hpp"

namespace TCMS
{
    template <typename T>
    class DoublyLinkedList : public LinkedList<T, DoublyLinkedListNode<T>> {
    public:
        using Base = LinkedList<T, DoublyLinkedListNode<T>>;
        using Base::m_Head;
        using Base::downcastFunc;

        ~DoublyLinkedList() override {
            DoublyLinkedListNode<T>* current = downcastFunc(m_Head);
            DoublyLinkedListNode<T>* temp = nullptr;

            while (current != nullptr) {
                temp = current;
                current = current->getNext();

                delete temp;
                temp = nullptr;
            }

            std::cout << "DoublyLinkedList destroyed.\n";
        }

        void insert(T data) override {
            DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(data, downcastFunc(m_Head), nullptr);

            if (m_Head != nullptr) {
                downcastFunc(m_Head)->setPrevious(newNode);
            }

            m_Head = newNode;
        };

        void remove(T data) override {
            if (m_Head == nullptr)
                return;

            DoublyLinkedListNode<T>* current = downcastFunc(m_Head);

            while (current != nullptr) {
                if (current->getData() == data) {
                    if (current->getPrevious() != nullptr) {
                        current->getPrevious()->setNext(current->getNext());
                        // static_cast<DoublyLinkedListNode<T>*>(current->getPrevious())->setNext(current->getNext());
                    } else {
                        m_Head = current->getNext();
                    }

                    if (current->getNext() != nullptr) {
                        current->getNext()->setPrevious(current->getPrevious());
                        // static_cast<DoublyLinkedListNode<T>*>(current->getNext())->setPrevious(current->getPrevious());
                    }

                    delete current;
                    current = nullptr;

                    return;
                }

                current = current->getNext();
            }
        };
        
        void print() const override {
            DoublyLinkedListNode<T>* current = downcastFunc(m_Head);

            while (current != nullptr) {
                std::cout << current->getData() << "\n";
                current = current->getNext();
            }

            std::cout << "\n";
        };

        // static DoublyLinkedListNode<T>* downcast(LinkedListNode<T, DoublyLinkedListNode<T>>* node) {
        //     return static_cast<DoublyLinkedListNode<T>*>(node);
        // }
    };
} // namespace TCMS