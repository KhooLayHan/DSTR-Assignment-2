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
        using Base::m_Tail;
        using Base::downcastFunc;

        SinglyCircularLinkedList() : Base() {

        }

        ~SinglyCircularLinkedList() override {
            if  (m_Head != nullptr)
                removeBegin();
            
            // if (m_Head == nullptr) {
            //     return; 
            // }
    
            // SinglyLinkedListNode<T>* current = downcastFunc(m_Head);
            // SinglyLinkedListNode<T>* temp = nullptr;
    
            // // Traverse the circular list and delete nodes
            // do {
            //     temp = current;
            //     current = current->getNext();
                
            //     delete temp;
            //     temp = nullptr;
            // } while (current != m_Head); // Stop when we loop back to the head
    
            // m_Head = nullptr; // Reset the head pointer
            std::cout << "SinglyCircularLinkedList destroyed.\n";
        }

        void insertBegin(T data) override {
            SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data);

            if (m_Head == nullptr) {
                m_Head = newNode;
                m_Tail = newNode;
                m_Tail->setNext(downcastFunc(m_Head));
            } else {
                // m_Tail->setNext(newNode);
                // m_Tail = newNode;
                // m_Tail->setNext(downcastFunc(m_Head));
                newNode->setNext(downcastFunc(m_Head));
                m_Tail->setNext(newNode);
                m_Head = newNode;
            }

            // if (m_Head == nullptr) {
            //     newNode->setNext(newNode);
            //     m_Tail = newNode;
            // } else {
            //     m_Tail->setNext(newNode);
            // }

            m_Head = newNode;
        };

        void insertPosition(T data, size_t position) override {
            if (position == 0) {
                insertBegin(data);
                return;
            }

            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);

            for (size_t i = 1; i < position && current->getNext() != m_Head; i++)
                current = current->getNext();

            // if (current == m_Tail && position > 0)
            //     throw std::out_of_range("Position out of range");
            
            SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data, current->getNext());
            current->setNext(newNode);

            if (current == m_Tail)
                m_Tail = newNode;
        }

        void insertEnd(T data) override {
            SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data, downcastFunc(m_Head));

            if (m_Head == nullptr) {
                m_Head = newNode;
                m_Tail = newNode;

                m_Tail->setNext(downcastFunc(m_Head));
            } else {
                m_Tail->setNext(newNode);
                m_Tail = newNode;
            }

            // if (m_Tail == nullptr) {
            //     m_Head = newNode;
            //     m_Tail = newNode;

            //     newNode->setNext(newNode);
            // } else {
            //     m_Tail->setNext(newNode);
            //     m_Tail = newNode;
            // }
        }

        void remove(T data) override {
            if (m_Head == nullptr)
                return;

            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);
            // SinglyLinkedListNode<T>* current = static_cast<SinglyLinkedListNode<T>*>(this->m_Head);
            // SinglyLinkedListNode<T>* previous = downcastFunc(m_Tail);
            SinglyLinkedListNode<T>* previous = nullptr;

            if (m_Head == m_Tail && m_Head->getData() == data) {
                delete m_Head;

                m_Head = nullptr;
                m_Tail = nullptr;

                return;
            }

            if (m_Head->getData() == data) {
                m_Tail->setNext(m_Head->getNext());

                SinglyLinkedListNode<T>* temp = downcastFunc(m_Head);
                m_Head = m_Head->getNext();

                delete temp;
                return;
            }

            do {
                previous = current;
                current = current->getNext();

                if (current->getData() == data) {
                    previous->setNext(current->getNext());

                    if (current == m_Tail)
                        m_Tail = previous;


                    delete current;
                    return;
                }
            } while (current != m_Head);

            // do {
            //     if (current->getData() == data) {
            //         if (current == m_Head) {
            //             m_Head = current->getNext();
            //             m_Tail->setNext(downcastFunc(m_Head));
            //         } else {
            //             previous->setNext(current->getNext());

            //             if (current == m_Tail)
            //                 m_Tail = previous;
            //         }

            //         // if (previous != nullptr) {
            //         //     previous->setNext(current->getNext());
            //         // } else {
            //         //     if (current->getNext() == m_Head) {
            //         //         m_Head = nullptr;
            //         //         m_Tail = nullptr;
            //         //     } else {
            //         //         m_Head = m_Head->getNext();
            //         //         m_Tail->setNext(downcastFunc(m_Head));
            //         //     }
            //         // }

            //         delete current;
            //         current = nullptr;

            //         return;
            //     }

            //     previous = current;
            //     current = current->getNext();
            // } while (current != m_Head);
        };
        
        void removeBegin() override {
            if (m_Head == nullptr)
                return;
            
            SinglyLinkedListNode<T>* temp = downcastFunc(m_Head);

            if (m_Head == m_Tail) {
                m_Head = nullptr;
                m_Tail = nullptr;
            } else {
                m_Tail->setNext(downcastFunc(m_Head)->getNext());
                m_Head = m_Head->getNext();
            }

            delete temp;
            // temp = nullptr;
        }

        void removeEnd() override {
            if (m_Tail == nullptr)
                return;
            
            if (m_Head == m_Tail) {
                delete m_Head;

                m_Tail = nullptr;
                m_Head = nullptr;

                return;
            }

            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);

            // while (current->getNext() != nullptr) 
            //     current = current->getNext();
            while (current->getNext() != m_Tail) 
                current = current->getNext();

            delete m_Tail;

            m_Tail = current;
            m_Tail->setNext(downcastFunc(m_Head));
        }

        void print() const override {
            if (m_Head == nullptr) 
                return;

            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);
            // SinglyLinkedListNode<T>* current = static_cast<SinglyLinkedListNode<T>*>(this->m_Head);

            do {
                std::cout << current->getData() << " -> ";
                current = current->getNext();
            } while (current != m_Head);

            // while (current != nullptr) {
            //     std::cout << current->getData() << "\n";
            //     current = current->getNext();
            // }

            std::cout << "[circular head]\n";
        };

        // LinkedList<T, SinglyCircularLinkedListNode<T>> getHead() const override {
        //     return m_Head;
        // }
    };
} // namespace TCMS