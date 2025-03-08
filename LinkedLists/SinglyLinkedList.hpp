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
        using Base::downcastFunc;
        
        ~SinglyLinkedList() override {
            while (m_Head != nullptr) {
                SinglyLinkedListNode<T>* temp = downcastFunc(m_Head);
                // auto temp = m_Head;
                m_Head = m_Head->getNext();

                delete temp;
                temp = nullptr;
            }

            std::cout << "SinglyLinkedList destroyed.\n";
        }

        void insert(T data) override {
            SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data, downcastFunc(m_Head));
            
            newNode->setNext(m_Head);
            m_Head = newNode;
        };

        void insertEnd(T data) {
            SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data, nullptr);

            if (m_Head == nullptr) {
                m_Head = newNode;
                
                return;
            }

            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);

            while (current->getNext() != nullptr)
                current = current->getNext();
                
            current->setNext(newNode);
        };

        void remove(T data) override {
            if (m_Head == nullptr)
                return;

            if (m_Head->getData() == data) {
                SinglyLinkedListNode<T>* temp = downcastFunc(m_Head);
                m_Head = m_Head->getNext();

                delete temp;
                temp = nullptr;

                return;
            }

            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);

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
            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);

            while (current != nullptr) {
                std::cout << current->getData() << "\n";
                current = current->getNext();
            }

            std::cout << "\n";
        };

        T getFirst() const {
            if (m_Head == nullptr) {
                throw std::runtime_error("List is empty");
            }

            return m_Head->getData();
        }

        T getLast() const {
            if (m_Head == nullptr) {
                throw std::runtime_error("List is empty");
            }

            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);
            
            while (current->getNext() != nullptr) 
                current = current->getNext();
            
            return current->getData();
        }

        bool isEmpty() const {
            return m_Head == nullptr;
        }

        // LinkedList<T, SinglyLinkedListNode<T>> getHead() const override {
        //     return m_Head;
        // }
    };
} // namespace TCMS