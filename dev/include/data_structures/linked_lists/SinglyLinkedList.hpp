// LinkedLists/SinglyLinkedList.hpp
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
        using Base::m_Length;
        using Base::downcastFunc;

        /**
         * @brief Detaches the first node from the linked list without deleting it.
         * 
         * @return Pointer to the detached node. If the list is empty, returns nullptr.
         */
        SinglyLinkedListNode<T>* detachBegin() {
            if (!m_Head) return nullptr;  // If the list is empty, return nullptr

            SinglyLinkedListNode<T>* detachedNode = downcastFunc(m_Head);  // Store the head node
            m_Head = m_Head->getNext();  // Move head to the next node

            if (!m_Head) m_Tail = nullptr;  // If list becomes empty, update tail as well

            detachedNode->setNext(nullptr);  // Disconnect the detached node
            return detachedNode;  // Return the detached node (caller must manage memory)
        }

        /**
         * @brief Destructor to deallocate all nodes in the list.
         * 
         * The destructor ensures that all allocated nodes are deleted 
         * to prevent memory leaks.
         */
        ~SinglyLinkedList() override {
            while (m_Head != nullptr) {
                std::cout << "HHHHH\n";
                removeBegin();
            //     if (m_Head == nullptr)
            }
            //     return;

            // SinglyLinkedListNode<T>* temp = downcastFunc(m_Head);
            // m_Head = m_Head->getNext();

            // if (m_Head == nullptr)
            //     m_Tail = nullptr;
                
            // if (temp->getData()) {
            //     std::cout << temp->getData() << "\n";
            //     delete temp;
            //     temp = nullptr;
            // }

            // --m_Length;
            //     std::cout << "SinglyLinkedList destroyed.\n";
            // }

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

            ++m_Length;
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
            
            ++m_Length;
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
            ++m_Length;            
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
            if (m_Head == nullptr)
                return;

            SinglyLinkedListNode<T>* temp = downcastFunc(m_Head);
            m_Head = m_Head->getNext();

            if (m_Head == nullptr)
                m_Tail = nullptr;
                
            if (temp->getData()) {
                std::cout << temp->getData() << "\n";
                delete temp;
                temp = nullptr;
            }

            --m_Length;
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
            --m_Length;

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
    };
} // namespace TCMS
#pragma once

// #include <iostream>
// #include <memory> // For std::shared_ptr

// #include "LinkedList.hpp"
// #include "SinglyLinkedListNode.hpp"

// namespace TCMS
// {
//     template <typename T>
//     class SinglyLinkedList : public LinkedList<T, SinglyLinkedListNode<T>> {
//     public:
//         using Base = LinkedList<T, SinglyLinkedListNode<T>>;
//         using Base::m_Head;
//         using Base::m_Tail;
//         using Base::m_Length;
//         using Base::downcastFunc;

//         ~SinglyLinkedList() override = default; // Smart pointers handle cleanup

//         void insertBegin(T data) override {
//             auto newNode = std::make_shared<SinglyLinkedListNode<T>>(data);
//             newNode->setNext(m_Head);
//             m_Head = newNode;

//             if (!m_Tail) 
//                 m_Tail = downcastFunc(m_Head.get());

//             ++m_Length;
//         }

//         void insertPosition(T data, size_t position) override {
//             if (position == 0) {
//                 insertBegin(data);
//                 return;
//             }

//             auto current = downcastFunc(m_Head.get());
//             for (size_t i = 0; i < position - 1 && current; i++) 
//                 current = current->getNext().get();

//             if (!current)
//                 throw std::out_of_range("Position is out of range");

//             auto newNode = std::make_shared<SinglyLinkedListNode<T>>(data);
//             newNode->setNext(current->getNext());
//             current->setNext(newNode);

//             if (!newNode->getNext()) 
//                 m_Tail = newNode.get();

//             ++m_Length;
//         }

//         void insertEnd(T data) override {    
//             auto newNode = std::make_shared<SinglyLinkedListNode<T>>(data);

//             if (!m_Tail)
//                 m_Head = newNode;
//             else
//                 m_Tail->setNext(newNode);

//             m_Tail = newNode.get();
//             ++m_Length;
//         }

//         void remove(T data) override {
//             if (!m_Head)
//                 return;

//             if (m_Head->getData() == data) {
//                 removeBegin();
//                 return;
//             }

//             auto current = downcastFunc(m_Head.get());

//             while (current->getNext() && current->getNext()->getData() != data) 
//                 current = current->getNext().get();

//             if (current->getNext()) {
//                 if (!current->getNext()->getNext()) 
//                     m_Tail = current;

//                 current->setNext(current->getNext()->getNext());
//                 --m_Length;
//             }
//         }

//         void removeBegin() override {
//             if (!m_Head)
//                 return;

//             m_Head = m_Head->getNext();

//             if (!m_Head) 
//                 m_Tail = nullptr;

//             --m_Length;
//         }

//         void removeEnd() override {
//             if (!m_Head)
//                 return;

//             if (!m_Head->getNext()) {
//                 m_Head.reset();
//                 m_Tail = nullptr;
//                 m_Length = 0;
//                 return;
//             }

//             auto current = downcastFunc(m_Head.get());
//             while (current->getNext()->getNext()) 
//                 current = current->getNext().get();

//             current->setNext(nullptr);
//             m_Tail = current;
//             --m_Length;
//         }

//         void print() const override {
//             auto current = downcastFunc(m_Head.get());

//             while (current) {
//                 std::cout << current->getData() << " -> ";
//                 current = current->getNext().get();
//             }

//             std::cout << "nullptr\n";
//         }
//     };
// } // namespace TCMS
