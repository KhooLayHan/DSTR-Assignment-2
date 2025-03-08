#pragma once

#include <iostream>

#include "LinkedList.hpp"
#include "SinglyLinkedListNode.hpp"

namespace TCMS
{
    template <typename T>
    class SinglyCircularLinkedList : public LinkedList<T, SinglyLinkedListNode<T>> {
    public:
        using Base = LinkedList<T, SinglyLinkedListNode<T>>;
        using Base::m_Head;
        using Base::downcast;

        SinglyCircularLinkedList() : LinkedList<T,SinglyLinkedListNode<T>>(), m_Tail(nullptr) {

        }

        ~SinglyCircularLinkedList() override {
            if (m_Head == nullptr) {
                return; 
            }
    
            SinglyLinkedListNode<T>* current = downcast(m_Head);
            SinglyLinkedListNode<T>* temp = nullptr;
    
            // Traverse the circular list and delete nodes
            do {
                temp = current;
                current = current->getNext();
                
                delete temp;
                temp = nullptr;
            } while (current != m_Head); // Stop when we loop back to the head
    
            m_Head = nullptr; // Reset the head pointer
            std::cout << "SinglyCircularLinkedList destroyed.\n";
        }

        void insert(T data) override {
            SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data);

            if (m_Head == nullptr) {
                m_Head = newNode;
                m_Tail = newNode;
                m_Tail->setNext(downcast(m_Head));
            } else {
                m_Tail->setNext(newNode);
                m_Tail = newNode;
                m_Tail->setNext(downcast(m_Head));
            }
        };

        void remove(T data) override {
            if (m_Head == nullptr)
                return;

            SinglyLinkedListNode<T>* current = downcast(m_Head);
            // SinglyLinkedListNode<T>* current = static_cast<SinglyLinkedListNode<T>*>(this->m_Head);
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
                            m_Tail->setNext(downcast(m_Head));
                        }
                    }

                    delete current;
                    current = nullptr;

                    return;
                }

                previous = current;
                current = current->getNext();
            } while (current !=m_Head);
        };
        
        void print() const override {
            if (m_Head == nullptr) 
                return;

            SinglyLinkedListNode<T>* current = downcast(m_Head);
            // SinglyLinkedListNode<T>* current = static_cast<SinglyLinkedListNode<T>*>(this->m_Head);

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