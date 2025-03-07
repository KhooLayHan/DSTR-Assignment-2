#pragma once

#include <iostream>

#include "LinkedList.hpp"
#include "SinglyLinkedListNode.hpp"

namespace TCMS
{
    template <typename T>
    class SinglyCircularLinkedList : public LinkedList<T> {
    public:
        SinglyCircularLinkedList() : LinkedList<T, SinglyCircularLinkedList<T>>(), m_Tail(nullptr) {

        }

        void insert(T data) override {
            SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data);

            if (m_Head == nullptr) {
                m_Head = newNode;
                m_Tail = newNode;
                m_Tail->setNext(m_Head);
            } else {
                m_Tail->setNext(newNode);
                m_Tail = newNode;
                m_Tail->setNext(m_Head);
            }
        };

        void remove(T data) override {
            if (m_Head == nullptr)
                return;

            SinglyLinkedListNode<T>* current = m_Head;
            // SinglyLinkedListNode<T>* current = static_cast<SinglyLinkedListNode<T>*>(m_Head);
            SinglyLinkedListNode<T>* previous = nullptr;

            do {
                if (current->getData() == data) {
                    if (previous != nullptr) {
                        previous->setNext(current->getNext());
                    } else {
                        if (current->getNext() == m_Head) {
                            m_Head = nullptr;
                            m_Tail = nullptr;
                        } else {
                            m_Head = m_Head->getNext();
                            m_Tail->setNext(m_Head);
                        }
                    }

                    delete current;
                    current = nullptr;

                    return;
                }

                previous = current;
                current = current->getNext();
            } while (current != m_Head);
        };
        
        void print() const override {
            if (m_Head == nullptr) 
                return;

            SinglyLinkedListNode<T>* current = m_Head;
            // SinglyLinkedListNode<T>* current = static_cast<SinglyLinkedListNode<T>*>(m_Head);

            do {
                std::cout << current->getData() << "\n";
                current = current->getNext();
            } while (current != m_Head);

            // while (current != nullptr) {
            //     std::cout << current->getData() << "\n";
            //     current = current->getNext();
            // }

            std::cout << "\n";
        };
    private:
        SinglyLinkedListNode<T>* m_Tail;
    };
} // namespace TCMS