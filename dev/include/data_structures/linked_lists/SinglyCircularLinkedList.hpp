#pragma once

#include <iostream>

#include "LinkedList.hpp"
#include "SinglyLinkedListNode.hpp"

namespace TCMS
{
    /**
     * @class SinglyCircularLinkedList
     * @brief Implements a singly circular linked list.
     * 
     * @tparam T The type of data stored in the list.
     * 
     * This class provides methods to insert, remove, and traverse 
     * elements in a singly circular linked list.
     */
    template <typename T>
    class SinglyCircularLinkedList : public LinkedList<T, SinglyLinkedListNode<T>> {
    public:
        using Base = LinkedList<T, SinglyLinkedListNode<T>>;
        using Base::m_Head;
        using Base::m_Tail;
        using Base::m_Length;
        using Base::downcastFunc;

        /**
         * @brief Default constructor for an empty circular linked list.
         */
        SinglyCircularLinkedList() : Base() {}

        /**
         * @brief Destructor for the circular linked list.
         * 
         * This function removes all nodes from the list to prevent memory leaks.
         */
        ~SinglyCircularLinkedList() override {
            if (m_Head != nullptr)  // Ensure the list is not empty
                removeBegin();      // Calls removeBegin() until all nodes are deleted
            
            std::cout << "SinglyCircularLinkedList destroyed.\n";
        }

        /**
         * @brief Inserts a new node at the beginning of the list.
         * 
         * @param data The data to be inserted.
         * 
         * If the list is empty, the new node becomes both the head and tail.
         * Otherwise, it is added before the current head, and the circular 
         * connection is maintained.
         */
        void insertBegin(T data) override {
            SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data);

            if (m_Head == nullptr) { // If the list is empty
                m_Head = newNode;
                m_Tail = newNode;
                m_Tail->setNext(downcastFunc(m_Head));  // Circular link
            } else {
                newNode->setNext(downcastFunc(m_Head)); // New node points to old head
                m_Tail->setNext(newNode);  // Update tail to point to new node
                m_Head = newNode;  // New node becomes the head
            }

            ++m_Length;
        };

        /**
         * @brief Inserts a new node at a specific position in the list.
         * 
         * @param data The data to be inserted.
         * @param position The index where the new node should be inserted.
         * 
         * If the position is 0, the node is inserted at the beginning.
         * If the position is greater than the list size, the node is inserted at the end.
         */
        void insertPosition(T data, size_t position) override {
            if (position == 0) { // If inserting at the beginning
                insertBegin(data);
                return;
            }

            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);

            // Traverse the list up to the given position
            for (size_t i = 1; i < position && current->getNext() != m_Head; i++)
                current = current->getNext();
            
            SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data, current->getNext());
            current->setNext(newNode);

            if (current == m_Tail)  // If inserted at the last position, update tail
                m_Tail = newNode;
            
            ++m_Length;
        }

        /**
         * @brief Inserts a new node at the end of the list.
         * 
         * @param data The data to be inserted.
         * 
         * If the list is empty, the new node becomes both the head and tail.
         * Otherwise, it is added after the current tail, and the circular 
         * connection is maintained.
         */
        void insertEnd(T data) override {
            SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(data, downcastFunc(m_Head));

            if (m_Head == nullptr) {  // If the list is empty
                m_Head = newNode;
                m_Tail = newNode;
                m_Tail->setNext(downcastFunc(m_Head));  // Circular link
            } else {
                m_Tail->setNext(newNode); // Link old tail to new node
                m_Tail = newNode; // Update tail to new node
            }

            ++m_Length;
        }

        /**
         * @brief Removes a node containing the specified data.
         * 
         * @param data The data to be removed.
         * 
         * Handles different cases:
         * - If the node to remove is the head.
         * - If the node to remove is in the middle.
         * - If the node to remove is the tail.
         */
        void remove(T data) override {
            if (m_Head == nullptr)  // If list is empty, return
                return;

            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);
            SinglyLinkedListNode<T>* previous = nullptr;

            // Case: Only one node in the list
            if (m_Head == m_Tail && m_Head->getData() == data) {
                delete m_Head;
                --m_Length;

                m_Head = nullptr;
                m_Tail = nullptr;
                
                return;
            }

            // Case: Removing the head
            if (m_Head->getData() == data) {
                m_Tail->setNext(m_Head->getNext()); // Update tail's next pointer
                SinglyLinkedListNode<T>* temp = downcastFunc(m_Head);
                m_Head = m_Head->getNext();
                
                delete temp;
                --m_Length;
                
                return;
            }

            // Traverse the list to find the node
            do {
                previous = current;
                current = current->getNext();

                if (current->getData() == data) {
                    previous->setNext(current->getNext());

                    if (current == m_Tail)  // If removing tail, update tail pointer
                        m_Tail = previous;

                    delete current;
                    --m_Length;
                
                    return;
                }
            } while (current != m_Head);
        };

        /**
         * @brief Removes the first node (head) of the list.
         */
        void removeBegin() override {
            if (m_Head == nullptr)  // If list is empty, return
                return;
            
            SinglyLinkedListNode<T>* temp = downcastFunc(m_Head);

            if (m_Head == m_Tail) { // If only one node exists
                m_Head = nullptr;
                m_Tail = nullptr;
            } else {
                m_Tail->setNext(downcastFunc(m_Head)->getNext()); // Update tail's next pointer
                m_Head = m_Head->getNext(); // Move head forward
            }

            delete temp;
            temp = nullptr;

            --m_Length;
        }

        /**
         * @brief Removes the last node (tail) of the list.
         */
        void removeEnd() override {
            if (m_Tail == nullptr) // If list is empty, return
                return;
            
            if (m_Head == m_Tail) { // If only one node exists
                delete m_Head;
                --m_Length;

                m_Tail = nullptr;
                m_Head = nullptr;
                return;
            }

            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);

            // Traverse until the second last node
            while (current->getNext() != m_Tail) 
                current = current->getNext();

            delete m_Tail;
            --m_Length;

            m_Tail = current;
            m_Tail->setNext(downcastFunc(m_Head)); // Maintain circular link
        }

        /**
         * @brief Prints all elements in the list.
         */
        void print() const override {
            if (m_Head == nullptr)  // If list is empty, return
                return;

            SinglyLinkedListNode<T>* current = downcastFunc(m_Head);

            do {
                std::cout << current->getData() << " -> ";
                current = current->getNext();
            } while (current != m_Head);

            std::cout << "[circular head]\n";
        }
    };
} // namespace TCMS

// #pragma once

// #include <iostream>
// #include <memory>
// #include "LinkedList.hpp"
// #include "SinglyLinkedListNode.hpp"

// namespace TCMS
// {
//     /**
//      * @class SinglyCircularLinkedList
//      * @brief Implements a singly circular linked list using shared pointers.
//      *
//      * @tparam T The type of data stored in the list.
//      */
//     template <typename T>
//     class SinglyCircularLinkedList : public LinkedList<T, SinglyLinkedListNode<T>>
//     {
//     public:
//         using Base = LinkedList<T, SinglyLinkedListNode<T>>;
//         using Base::m_Head;
//         using Base::m_Tail;
//         using Base::m_Length;
//         using Base::downcastFunc;

//         /**
//          * @brief Default constructor for an empty circular linked list.
//          */
//         SinglyCircularLinkedList() : Base() {}

//         /**
//          * @brief Destructor for the circular linked list.
//          * Automatically clears all nodes.
//          */
//         ~SinglyCircularLinkedList() override
//         {
//             while (m_Head) // Remove all nodes
//                 removeBegin();
//             std::cout << "SinglyCircularLinkedList destroyed.\n";
//         }

//         /**
//          * @brief Inserts a new node at the beginning of the list.
//          *
//          * @param data The data to be inserted.
//          */
//         void insertBegin(T data) override
//         {
//             auto newNode = std::make_shared<SinglyLinkedListNode<T>>(data);

//             if (!m_Head) // If list is empty
//             {
//                 m_Head = newNode;
//                 m_Tail = newNode;
//                 m_Tail->setNext(m_Head); // Circular link
//             }
//             else
//             {
//                 newNode->setNext(m_Head); // New node points to old head
//                 m_Tail->setNext(newNode); // Tail points to new node
//                 m_Head = newNode;         // Update head
//             }

//             ++m_Length;
//         }

//         /**
//          * @brief Inserts a new node at the specified position.
//          *
//          * @param data The data to be inserted.
//          * @param position The index where the new node should be inserted.
//          */
//         void insertPosition(T data, size_t position) override
//         {
//             if (position == 0) // Insert at beginning
//             {
//                 insertBegin(data);
//                 return;
//             }

//             auto current = m_Head;
//             for (size_t i = 1; i < position && current->getNext() != m_Head; i++)
//                 current = current->getNext();

//             auto newNode = std::make_shared<SinglyLinkedListNode<T>>(data);
//             newNode->setNext(current->getNext());
//             current->setNext(newNode);

//             if (current == m_Tail) // If inserted at last position, update tail
//                 m_Tail = newNode;

//             ++m_Length;
//         }

//         /**
//          * @brief Inserts a new node at the end of the list.
//          *
//          * @param data The data to be inserted.
//          */
//         void insertEnd(T data) override
//         {
//             auto newNode = std::make_shared<SinglyLinkedListNode<T>>(data);

//             if (!m_Head) // If list is empty
//             {
//                 m_Head = newNode;
//                 m_Tail = newNode;
//                 m_Tail->setNext(m_Head); // Circular link
//             }
//             else
//             {
//                 m_Tail->setNext(newNode);
//                 m_Tail = newNode;
//                 m_Tail->setNext(m_Head); // Maintain circular link
//             }

//             ++m_Length;
//         }

//         /**
//          * @brief Removes the first node of the list.
//          */
//         void removeBegin() override
//         {
//             if (!m_Head)
//                 return;

//             if (m_Head == m_Tail) // If only one node exists
//             {
//                 m_Head.reset();
//                 m_Tail.reset();
//             }
//             else
//             {
//                 m_Tail->setNext(m_Head->getNext()); // Update tail's next pointer
//                 m_Head = m_Head->getNext();         // Move head forward
//             }

//             --m_Length;
//         }

//         /**
//          * @brief Removes the last node of the list.
//          */
//         void removeEnd() override
//         {
//             if (!m_Tail)
//                 return;

//             if (m_Head == m_Tail) // If only one node exists
//             {
//                 m_Head.reset();
//                 m_Tail.reset();
//                 --m_Length;
//                 return;
//             }

//             auto current = m_Head;
//             while (current->getNext() != m_Tail) // Traverse to second last node
//                 current = current->getNext();

//             current->setNext(m_Head); // Maintain circular link
//             m_Tail.reset();
//             m_Tail = current;
//             --m_Length;
//         }

//         /**
//          * @brief Removes a node containing the specified data.
//          *
//          * @param data The data to be removed.
//          */
//         void remove(T data) override
//         {
//             if (!m_Head)
//                 return;

//             if (m_Head == m_Tail && m_Head->getData() == data) // Single node case
//             {
//                 m_Head.reset();
//                 m_Tail.reset();
//                 --m_Length;
//                 return;
//             }

//             if (m_Head->getData() == data) // Removing head
//             {
//                 m_Tail->setNext(m_Head->getNext());
//                 m_Head = m_Head->getNext();
//                 --m_Length;
//                 return;
//             }

//             auto current = m_Head;
//             std::shared_ptr<SinglyLinkedListNode<T>> previous = nullptr;

//             do
//             {
//                 previous = current;
//                 current = current->getNext();

//                 if (current->getData() == data)
//                 {
//                     previous->setNext(current->getNext());

//                     if (current == m_Tail) // If removing tail, update tail pointer
//                         m_Tail = previous;

//                     --m_Length;
//                     return;
//                 }
//             } while (current != m_Head);
//         }

//         /**
//          * @brief Prints all elements in the list.
//          */
//         void print() const override
//         {
//             if (!m_Head)
//                 return;

//             auto current = m_Head;

//             do
//             {
//                 std::cout << current->getData() << " -> ";
//                 current = current->getNext();
//             } while (current != m_Head);

//             std::cout << "[circular head]\n";
//         }
//     };
// } // namespace TCMS
