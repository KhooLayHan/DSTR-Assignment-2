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
                removeBegin();
            }

            std::cout << "SinglyLinkedList destroyed.\n";
        }

        void insertBegin(T data) override {
            SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data);
            
            newNode->setNext(downcastFunc(m_Head));
            m_Head = newNode;
            
            if (m_Head == nullptr)
                m_Tail = newNode;
        };

        void insertPosition(T data, size_t position) override {
            if (position == 0) {
                insertBegin(data);
                return;
            }

            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);

            for (size_t i = 0; i != position - 1 && current != nullptr; i++)
                current = current->getNext();

            if (current == nullptr)
                throw std::out_of_range("Position is out of range");
            
            // static_assert(current != nullptr, "Position is out or range");

            SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data);
            newNode->setNext(current->getNext());
            current->setNext(newNode);

            if (newNode->getNext() == nullptr)
                m_Tail = newNode;
        } 

        void insertEnd(T data) {    
            SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data);

            if (m_Tail == nullptr)
                m_Head = newNode;
            else    
                m_Tail->setNext(newNode);

            m_Tail = newNode;            
        };

        void remove(T data) override {
            if (m_Head == nullptr)
                return; 

            // if (m_Head->getData() == data) {
            //     SinglyLinkedListNode<T>* temp = downcastFunc(m_Head);
            //     m_Head = m_Head->getNext();

            //     delete temp;
            //     temp = nullptr;

            //     return;
            // }

            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);
            SinglyLinkedListNode<T>* previous = nullptr;

            while (current != nullptr) {
                if (current->getData() == data) {
                    if (previous == nullptr) {
                        m_Head = current->getNext();
                        
                        if (m_Head == nullptr)
                            m_Tail = nullptr;
                    } else {
                        previous->setNext(current->getNext());

                        if (current->getNext() == nullptr)
                            m_Tail = previous;
                    }

                    delete current;
                    // current = nullptr;
    
                    return;
                }

                previous = current;
                current = current->getNext();
            }

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
        }

        void removeBegin() override {
            if (m_Head == nullptr)
                return;

            SinglyLinkedListNode<T>* temp = downcastFunc(m_Head);
            m_Head = m_Head->getNext();

            if (m_Head == nullptr)
                m_Tail = nullptr;
                
            delete temp;
        };
        
        void removeEnd() override {
            if (m_Head == nullptr)
                return;

            if (m_Head == m_Tail) {
                delete m_Head;

                m_Head = nullptr;
                m_Tail = nullptr;

                return;
            }

            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);

            while (current->getNext() != m_Tail && current->getNext())
                current = current->getNext();

            delete m_Tail;

            m_Tail = current;
            m_Tail->setNext(nullptr);
        }

        void print() const override {
            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);

            while (current != nullptr) {
                std::cout << current->getData() << " -> ";
                current = current->getNext();
            }

            std::cout << "nullptr\n";
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