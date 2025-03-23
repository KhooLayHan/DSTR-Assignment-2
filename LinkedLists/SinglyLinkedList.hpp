#pragma once

#include <iostream>

#include "LinkedList.hpp"
#include "SinglyLinkedListNode.hpp"

namespace TCMS
{
    /**
     * @brief Singly Linked List implementation
     * 
     * This class extends the `LinkedList` base class to provide functionality 
     * for a singly linked list. It supports basic operations such as insertion, 
     * deletion, and traversal.
     * 
     * @tparam T Type of data stored in the list nodes.
     */
    template <typename T>
    class SinglyLinkedList : public LinkedList<T, SinglyLinkedListNode<T>> {
    public:
        using Base = LinkedList<T, SinglyLinkedListNode<T>>;
        using Base::m_Head;
        using Base::m_Tail;
        using Base::downcastFunc;

        /**
         * @brief Destructor to deallocate all nodes in the list.
         * 
         * The destructor ensures that all allocated nodes are deleted 
         * to prevent memory leaks.
         */
        ~SinglyLinkedList() override {
            while (m_Head != nullptr) {
                removeBegin();
            }

            std::cout << "SinglyLinkedList destroyed.\n";
        }

        /**
         * @brief Inserts a new node at the beginning of the list.
         * 
         * @param data The data to be inserted.
         */
        void insertBegin(T data) override {
            SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data);
            
            newNode->setNext(downcastFunc(m_Head));
            m_Head = newNode;
            
            if (m_Tail == nullptr)
                m_Tail = newNode;
        }

        /**
         * @brief Inserts a new node at a specific position in the list.
         * 
         * @param data The data to be inserted.
         * @param position The position (zero-based index) where the new node should be inserted.
         * @throws std::out_of_range if the position is invalid.
         */
        void insertPosition(T data, size_t position) override {
            if (position == 0) {
                insertBegin(data);
                return;
            }

            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);

            for (size_t i = 0; i < position - 1 && current != nullptr; i++)
                current = current->getNext();

            if (current == nullptr)
                throw std::out_of_range("Position is out of range");

            SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data);
            newNode->setNext(current->getNext());
            current->setNext(newNode);

            if (newNode->getNext() == nullptr)
                m_Tail = newNode;
        }

        /**
         * @brief Inserts a new node at the end of the list.
         * 
         * @param data The data to be inserted.
         */
        void insertEnd(T data) {    
            SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data);

            if (m_Tail == nullptr)
                m_Head = newNode;
            else    
                m_Tail->setNext(newNode);

            m_Tail = newNode;            
        }

        /**
         * @brief Removes the first occurrence of a node containing the given data.
         * 
         * @param data The data to be removed.
         */
        void remove(T data) override {
            if (m_Head == nullptr)
                return; 

            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);
            SinglyLinkedListNode<T>* previous = nullptr;

            while (current != nullptr) {
                if (current->getData() == data) {
                    if (previous == nullptr) {  // Removing head node
                        m_Head = current->getNext();
                        
                        if (m_Head == nullptr)
                            m_Tail = nullptr;
                    } else {  // Removing a node in between or at the end
                        previous->setNext(current->getNext());

                        if (current->getNext() == nullptr)
                            m_Tail = previous;
                    }

                    delete current;
                    return;
                }

                previous = current;
                current = current->getNext();
            }
        }

        /**
         * @brief Removes the first node from the list.
         */
        void removeBegin() override {
            if (m_Head == nullptr)
                return;

            SinglyLinkedListNode<T>* temp = downcastFunc(m_Head);
            m_Head = m_Head->getNext();

            if (m_Head == nullptr)
                m_Tail = nullptr;
                
            delete temp;
        }

        /**
         * @brief Removes the last node from the list.
         */
        void removeEnd() override {
            if (m_Head == nullptr)
                return;

            if (m_Head == m_Tail) {  // If only one node exists
                delete m_Head;
                m_Head = nullptr;
                m_Tail = nullptr;
                return;
            }

            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);

            while (current->getNext() != m_Tail)
                current = current->getNext();

            delete m_Tail;
            m_Tail = current;
            m_Tail->setNext(nullptr);
        }

        /**
         * @brief Prints the elements of the list to the console.
         */
        void print() const override {
            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);

            while (current != nullptr) {
                std::cout << current->getData() << " -> ";
                current = current->getNext();
            }
            std::cout << "nullptr\n";
        }
            // ! Sally Added this
        /**
         * @brief Returns the head node of the list.
         * 
         * This method provides direct access to the head of the list.
         * 
         * @return Pointer to the head node.
         */
        SinglyLinkedListNode<T>* getHead() const
        {
            return downcastFunc(m_Head);
        }

        /**
         * @brief Returns the front element of the list without removing it.
         * 
         * @throws std::runtime_error if the list is empty.
         * @return The data stored in the head node.
         */
        T peekFront() const
        {
            if (!m_Head)
                throw std::runtime_error("List is empty!");
            return m_Head->getData();
        }

        /**
         * @brief Removes the first element from the list.
         * 
         * This function functions as a queue's dequeue operation.
         */
        void dequeue()
        {
            if (m_Head == nullptr)
                return;
            removeBegin();
        }
    };
} // namespace TCMS
