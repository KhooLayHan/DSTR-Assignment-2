#pragma once

#include <iostream>

#include "LinkedList.hpp"
#include "SinglyLinkedListNode.hpp"

namespace TCMS
{
    template <typename T>
    class SinglyLinkedList : public LinkedList<T, SinglyLinkedListNode<T>> {
    public:
        using Base = LinkedList<T, SinglyLinkedListNode<T>>;
        using Base::m_Head;
        using Base::downcast;
        
        ~SinglyLinkedList() override {
            while (m_Head != nullptr) {
                SinglyLinkedListNode<T>* temp = downcast(m_Head);
                // auto temp = m_Head;
                m_Head = m_Head->getNext();

                delete temp;
                temp = nullptr;
            }

            std::cout << "SinglyLinkedList destroyed.\n";
        }

        void insert(T data) override {
            SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data, downcast(m_Head));
            m_Head = newNode;
        };

        void remove(T data) override {
            if (m_Head == nullptr)
                return;

            if (m_Head->getData() == data) {
                SinglyLinkedListNode<T>* temp = downcast(m_Head);
                m_Head = m_Head->getNext();

                delete temp;
                temp = nullptr;

                return;
            }

            SinglyLinkedListNode<T>* current = downcast(m_Head);

            while (current->getNext() != nullptr) {
                if (current->getNext()->getData() == data) {
                    SinglyLinkedListNode<T>* temp = current->getNext();
                    current->setNext(current->getNext()->getNext());

                    delete temp;
                    temp = nullptr;

                    return;
                }

                current = current->getNext();
            }
        };
        
        void print() const override {
            SinglyLinkedListNode<T>* current = downcast(m_Head);

            while (current != nullptr) {
                std::cout << current->getData() << "\n";
                current = current->getNext();
            }

            std::cout << "\n";
        };
    };
} // namespace TCMS