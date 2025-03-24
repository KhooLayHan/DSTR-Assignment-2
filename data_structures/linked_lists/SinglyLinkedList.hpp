#pragma once

#include <iostream>
#include "LinkedList.hpp"
#include "SinglyLinkedListNode.hpp"

namespace TCMS
{
    /**
     * @brief A singly linked list implementation.
     * @tparam T The type of data stored in the list.
     * 
     * This class provides methods to insert, remove, and traverse elements in a singly linked list.
     */
    template <typename T>
    class SinglyLinkedList : public LinkedList<T, SinglyLinkedListNode<T>> {
    public:
        using Base = LinkedList<T, SinglyLinkedListNode<T>>;
        using Base::m_Head;
        using Base::m_Tail;
        using Base::m_Length;
        using Base::downcastFunc;

        /**
         * @brief Default constructor initializes an empty singly linked list.
         */
        SinglyLinkedList() : Base() {}

        /**
         * @brief Destructor ensures proper deletion of all nodes.
         */
        ~SinglyLinkedList() override {
            while (m_Head != nullptr) {
                removeBegin(); // Remove nodes until the list is empty
                // std::cout << "SinglyLinkedList destroyed.\n";
            }
        }

        /**
         * @brief Inserts a new node at the beginning of the list.
         * @param data The data to insert.
         */
        void insertBegin(T data) override {
            SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data);
            newNode->setNext(downcastFunc(m_Head));
            m_Head = newNode;

            if (m_Tail == nullptr) { // If the list was empty, update tail
                m_Tail = newNode;
            }

            ++m_Length;
        }

        /**
         * @brief Inserts a new node at a specific position in the list.
         * @param data The data to insert.
         * @param position The index where the new node should be inserted.
         * @throws std::out_of_range If the position is out of range.
         */
        void insertPosition(T data, size_t position) override {
            if (position == 0) { // If inserting at the beginning
                insertBegin(data);
                return;
            }

            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);

            // Traverse to the position before insertion
            for (size_t i = 0; i < position - 1 && current != nullptr; i++) {
                current = current->getNext();
            }

            if (current == nullptr) { // If position is out of range
                throw std::out_of_range("Position is out of range");
            }

            SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data);
            newNode->setNext(current->getNext());
            current->setNext(newNode);

            if (newNode->getNext() == nullptr) { // If inserted at the last position, update tail
                m_Tail = newNode;
            }

            ++m_Length;
        }

        /**
         * @brief Inserts a new node at the end of the list.
         * @param data The data to insert.
         */
        void insertEnd(T data) override {
            SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data);

            if (m_Tail == nullptr) { // If the list is empty
                m_Head = newNode;
            } else {
                m_Tail->setNext(newNode); // Link old tail to new node
            }

            m_Tail = newNode; // Update tail to new node
            ++m_Length;
        }

        /**
         * @brief Removes the first occurrence of a node containing the specified data.
         * @param data The data to remove.
         */
        void remove(T data) override {
            if (m_Head == nullptr) { // If list is empty, return
                return;
            }

            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);
            SinglyLinkedListNode<T>* previous = nullptr;

            while (current != nullptr) {
                if (current->getData() == data) {
                    if (previous == nullptr) { // Removing head node
                        m_Head = current->getNext();

                        if (m_Head == nullptr) { // If list becomes empty, update tail
                            m_Tail = nullptr;
                        }
                    } else { // Removing a node in between or at the end
                        previous->setNext(current->getNext());

                        if (current->getNext() == nullptr) { // If removing tail, update tail
                            m_Tail = previous;
                        }
                    }

                    delete current;
                    --m_Length;
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
            if (m_Head == nullptr) { // If list is empty, return
                return;
            }

            SinglyLinkedListNode<T>* temp = downcastFunc(m_Head);
            m_Head = m_Head->getNext();

            if (m_Head == nullptr) { // If list becomes empty, update tail
                m_Tail = nullptr;
            }

            delete temp;
            --m_Length;
        }

        /**
         * @brief Removes the last node from the list.
         */
        void removeEnd() override {
            if (m_Head == nullptr) { // If list is empty, return
                return;
            }

            if (m_Head == m_Tail) { // If only one node exists
                delete m_Head;
                m_Head = nullptr;
                m_Tail = nullptr;
                --m_Length;
                return;
            }

            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);

            // Traverse until the second last node
            while (current->getNext() != m_Tail) {
                current = current->getNext();
            }

            delete m_Tail;
            m_Tail = current;
            m_Tail->setNext(nullptr);
            --m_Length;
        }

        /**
         * @brief Prints all elements in the list.
         */
        void print() const override {
            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);

            while (current != nullptr) {
                std::cout << current->getData() << " -> ";
                current = current->getNext();
            }

            std::cout << "nullptr\n";
        }

        // ! Courtesy of Sally 

        /**
         * @brief Returns the head node of the list.
         * @return Pointer to the head node.
         */
        SinglyLinkedListNode<T>* getHead() const {
            return downcastFunc(m_Head);
        }

        /**
         * @brief Returns the front element of the list without removing it.
         * @return The data stored in the head node.
         * @throws std::runtime_error If the list is empty.
         */
        T peekFront() const {
            if (!m_Head) {
                throw std::runtime_error("List is empty!");
            }
            return m_Head->getData();
        }

        /**
         * @brief Removes the first element from the list (dequeue operation).
         */
        void dequeue() {
            if (m_Head == nullptr) { // If list is empty, return
                return;
            }
            removeBegin();
        }
    };
} // namespace TCMS