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
        using Base::m_Tail;
        using Base::downcastFunc;

        DoublyLinkedList() : Base() {

        }

        ~DoublyLinkedList() override {
            while (m_Head != nullptr)
                removeBegin();
            
            // DoublyLinkedListNode<T>* current = downcastFunc(m_Head);
            // DoublyLinkedListNode<T>* temp = nullptr;

            // while (current != nullptr) {
            //     temp = current;
            //     current = current->getNext();

            //     delete temp;
            //     temp = nullptr;
            // }

            std::cout << "DoublyLinkedList destroyed.\n";
        }

        void insertBegin(T data) override {
            DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(data);
            // DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(data);

            newNode->setNext(downcastFunc(m_Head));

            if (m_Head)
                downcastFunc(m_Head)->setPrevious(newNode);

            m_Head = newNode;

            if (!m_Tail)    
                m_Tail = newNode;

            // if (m_Head != nullptr) {
            //     downcastFunc(m_Head)->setPrevious(newNode);
            // } else {
            //     m_Tail = newNode;
            // }
            
            // m_Head = newNode;
            // newNode->setNext(downcastFunc(m_Head));
        };

        void insertPosition(T data, size_t position) override {
            if (position == 0) {
                insertBegin(data);
                return;
            }

            DoublyLinkedListNode<T>* current = downcastFunc(m_Head);

            for (size_t i = 0; i < position - 1 && current != nullptr; i++)                 
                current = current->getNext();

            if (!current)
                throw std::out_of_range("Position is out of range");
        
            DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(data);

            newNode->setNext(current->getNext());
            if (current->getNext())
                current->getNext()->setPrevious(newNode);
            
            current->setNext(newNode);
            newNode->setPrevious(current);

            if (!newNode->getNext())
                m_Tail = newNode;

            // DoublyLinkedListNode<T>* current = downcastFunc(m_Head);

            // for (size_t i = 0; i < position - 1 && current != nullptr; i++) {
            //     if (current == nullptr)
            //         throw std::out_of_range("Position is out of range");
                
            //     current = current->getNext();
            // }

            // DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(data, current, current->getNext());

            // if (current->getNext() != nullptr)
            //     current->getNext()->setPrevious(newNode);

            // current->setNext(newNode);

            // if (newNode->getNext() == nullptr)
            //     m_Tail = newNode;
        }

        void insertEnd(T data) override {
            DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(data);

            if (m_Tail) {
                downcastFunc(m_Tail)->setNext(newNode);
                newNode->setPrevious(downcastFunc(m_Tail));
            } else {
                m_Head = newNode;
            }

            // if (m_Tail == nullptr) {
            //     m_Head = newNode;
            // } else {
            //     downcastFunc(m_Tail)->setPrevious(newNode);
            // }

            // if (m_Tail != nullptr) {
            //     m_Tail->setNext(newNode);
            //     // m_Head = newNode;
            // } else {
                // DoublyLinkedListNode<T>* current = downcastFunc(m_Head);
                
                // while (current->getNext() != nullptr)
                //     current = current->getNext();
                
                // current->setNext(newNode);
                // newNode->setPrevious(current);

            //     m_Head = newNode;
            // }

            m_Tail = newNode;
        }

        void remove(T data) override {
            if (m_Head == nullptr)
                return;

            DoublyLinkedListNode<T>* current = downcastFunc(m_Head);

            // Removing the head node
            if (m_Head->getData() == data) {
                m_Head = downcastFunc(m_Head)->getNext();

                if (m_Head)
                    downcastFunc(m_Head)->setPrevious(nullptr);
                else    
                    m_Tail = nullptr;

                delete current;
                // current = nullptr;

                return;
            }

            while (current != nullptr) {
                if (current->getData() == data) {
                    if (current->getNext())
                        current->getNext()->setPrevious(current->getPrevious());
                    else    
                        m_Tail = current->getPrevious();

                    if (current->getPrevious())
                        current->getPrevious()->setNext(current->getNext());


                    delete current;
                    return;
                }

                current = current->getNext();
            }

            // while (current != nullptr) {
            //     if (current->getData() == data) {
            //         if (current->getPrevious() != nullptr) {
            //             current->getPrevious()->setNext(current->getNext());
            //         } else {
            //             m_Head = current->getNext();
            //         }

            //         if (current->getNext() != nullptr) {
            //             downcastFunc(current->getNext())->setPrevious(current->getPrevious());
            //         } else {
            //             m_Tail = current->getPrevious();
            //         }

            //         delete current;
            //         // current = nullptr;

            //         return;
            //     }

            //     current = current->getNext();
            // }
        }

        void removeBegin() override {
            if (m_Head) {
                DoublyLinkedListNode<T>* temp = downcastFunc(m_Head);
                m_Head = m_Head->getNext();
                
                if (m_Head)
                    downcastFunc(m_Head)->setPrevious(nullptr);
                else    
                    m_Tail = nullptr;

                delete temp;
            }

            // if (m_Head == nullptr)
            //     return;

            // DoublyLinkedListNode<T>* temp = downcastFunc(m_Head);
            // m_Head = m_Head->getNext();

            // if (m_Head != nullptr)
            //     downcastFunc(m_Head)->setPrevious(nullptr);
            // else 
            //     m_Tail = nullptr;

            // delete temp;
        }
        
        void removeEnd() override {
            if (m_Tail == nullptr)
                return;

            DoublyLinkedListNode<T>* temp = downcastFunc(m_Tail);
            m_Tail = downcastFunc(m_Tail)->getPrevious();

            if (m_Tail)
                m_Tail->setNext(nullptr);
            else    
                m_Head = nullptr;

            delete temp;
            // if (m_Tail == nullptr)
            //     return;

            // DoublyLinkedListNode<T>* temp = downcastFunc(m_Tail);
            // m_Tail = temp->getPrevious();

            // if (m_Tail != nullptr)
            //     m_Tail->setNext(nullptr);
            // else 
            //     m_Head = nullptr;

            // delete temp;
        }

        void print() const override {
            DoublyLinkedListNode<T>* current = downcastFunc(m_Head);

            while (current != nullptr) {
                std::cout << current->getData() << " <-> ";
                current = current->getNext();
            }

            std::cout << "nullptr\n";
        }

        // T getFirst() const {
        //     if (m_Head == nullptr)
        //         throw std::runtime_error("List is empty!");

        //     return downcastFunc(m_Head)->getData();
        // }

        // static DoublyLinkedListNode<T>* downcast(LinkedListNode<T, DoublyLinkedListNode<T>>* node) {
        //     return static_cast<DoublyLinkedListNode<T>*>(node);
        // }
    };
} // namespace TCMS

        
            // while (current != nullptr) {
            //     if (current->getData() == data) {
            //         if (current->getPrevious() != nullptr) {
            //             current->getPrevious()->setNext(current->getNext());
            //             // static_cast<DoublyLinkedListNode<T>*>(current->getPrevious())->setNext(current->getNext());
            //         } else {
            //             m_Head = current->getNext();
            //         }

            //         if (current->getNext() != nullptr) {
            //             current->getNext()->setPrevious(current->getPrevious());
            //             // static_cast<DoublyLinkedListNode<T>*>(current->getNext())->setPrevious(current->getPrevious());
            //         }

            //         delete current;
            //         current = nullptr;

            //         return;
            //     }

            //     current = current->getNext();