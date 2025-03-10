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
        using Base::m_Tail;
        using Base::downcastFunc;
        
        ~SinglyLinkedList() override {
            while (m_Head != nullptr) {
                SinglyLinkedListNode<T>* temp = downcastFunc(m_Head);
                m_Head = m_Head->getNext();

                delete temp;
                temp = nullptr;
            }

            std::cout << "SinglyLinkedList destroyed.\n";
        }

        void insertBegin(T data) override {
            SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data, downcastFunc(m_Head));
            
            if (m_Head == nullptr)
                m_Tail = newNode;

            m_Head = newNode;
        };

        void insertEnd(T data) {    
            SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data, nullptr);

            if (m_Tail == nullptr)
                m_Head = newNode;
            else    
                m_Tail->setNext(newNode);

            m_Tail = newNode;            

            // SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data, nullptr);

            // if (m_Head == nullptr) {
            //     m_Head = newNode;
                
            //     return;
            // }

            // SinglyLinkedListNode<T>* current = downcastFunc(m_Head);

            // while (current->getNext() != nullptr)
            //     current = current->getNext();
                
            // current->setNext(newNode);
        };

        void removeBegin(T data) override {
            if (m_Head == nullptr)
                return;

            SinglyLinkedListNode<T>* temp = downcastFunc(m_Head);
            m_Head = m_Head->getNext();

            if (m_Head == nullptr)
                m_Tail = nullptr;
                // return;

            delete temp;

            // if (m_Head->getData() == data) {
            //     SinglyLinkedListNode<T>* temp = downcastFunc(m_Head);
            //     m_Head = m_Head->getNext();

            //     delete temp;
            //     temp = nullptr;

            //     return;
            // }

            // SinglyLinkedListNode<T>* current = downcastFunc(m_Head);

            // while (current->getNext() != nullptr) {
            //     if (current->getNext()->getData() == data) {
            //         SinglyLinkedListNode<T>* temp = current->getNext();
            //         current->setNext(current->getNext()->getNext());

            //         delete temp;
            //         temp = nullptr;

            //         return;
            //     }

            //     current = current->getNext();
            // }
        };
        
        void print() const override {
            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);

            while (current != nullptr) {
                std::cout << current->getData() << " -> ";
                current = current->getNext();
            }

            std::cout << " nullptr\n";
        };

        // T getFirst() const {
        //     if (m_Head == nullptr) {
        //         throw std::runtime_error("List is empty");
        //     }

        //     return m_Head->getData();
        // }

        // T getLast() const {
        //     if (m_Head == nullptr) {
        //         throw std::runtime_error("List is empty");
        //     }

        //     SinglyLinkedListNode<T>* current = downcastFunc(m_Head);
            
        //     while (current->getNext() != nullptr) 
        //         current = current->getNext();
            
        //     return current->getData();
        // }

        // bool isEmpty() const {
        //     return m_Head == nullptr;
        // }
    };
} // namespace TCMS