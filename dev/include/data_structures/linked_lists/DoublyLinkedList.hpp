// LinkedLists/DoublyLinkedList.hpp
#pragma once

#include <iostream>
#include "LinkedList.hpp"
#include "DoublyLinkedListNode.hpp"

namespace TCMS
{
    /**
     * @brief DoublyLinkedList class inheriting from LinkedList<T, DoublyLinkedListNode<T>>.
     *        It allows bidirectional traversal and efficient insertions/removals at both ends.
     */
    template <typename T>
    class DoublyLinkedList : public LinkedList<T, DoublyLinkedListNode<T>> {
    public:
        using Base = LinkedList<T, DoublyLinkedListNode<T>>;
        using Base::m_Head;
        using Base::m_Tail;
        using Base::m_Length;
        using Base::downcastFunc;

        /**
         * @brief Default constructor initializes an empty doubly linked list.
         */
        DoublyLinkedList() : Base() {}

        /**
         * @brief Destructor ensures proper deletion of all nodes.
         */
        ~DoublyLinkedList() override {
            while (m_Head != nullptr){
                if (m_Head) {
                    DoublyLinkedListNode<T>* temp = downcastFunc(m_Head);
                    m_Head = m_Head->getNext();
                    
                    if (m_Head)
                        downcastFunc(m_Head)->setPrevious(nullptr);
                    else    
                        m_Tail = nullptr; // List is now empty.
    
                    temp->setNext(nullptr); // Prevent accidental access
                    delete temp;
                    --m_Length; // Update length
                }
            }
                // removeBegin();

            std::cout << "DoublyLinkedList destroyed.\n";
        }

        DoublyLinkedList<T> deepCopy() const {
            DoublyLinkedList<T> newList;
            
            DoublyLinkedListNode<T>* current = downcastFunc(m_Head);
            while (current != nullptr) {
                newList.insertEnd(current->getData()); // Copies actual data
                current = current->getNext();
            }
        
            return newList;
        }
        
        /**
         * @brief Inserts a new node at the beginning of the list.
         * @param data The data to insert.
         */
        void insertBegin(T data) override {
            DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(data);
            newNode->setNext(downcastFunc(m_Head));

            if (m_Head)
                downcastFunc(m_Head)->setPrevious(newNode);

            m_Head = newNode;

            // If the list was empty, update tail as well.
            if (!m_Tail)    
                m_Tail = newNode;

            ++m_Length; // Update length
        }

        /**
         * @brief Inserts a node at a specific position.
         * @param data The data to insert.
         * @param position The position (0-based index).
         * @throws std::out_of_range If the position is out of range.
         */
        void insertPosition(T data, size_t position) override {
            if (position == 0) {
                insertBegin(data);
                return;
            }

            DoublyLinkedListNode<T>* current = downcastFunc(m_Head);

            // Traverse to the position before insertion.
            for (size_t i = 0; i < position - 1 && current != nullptr; i++)                 
                current = current->getNext();

            if (!current)
                throw std::out_of_range("Position is out of range");
        
            DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(data);

            // Link new node into the list.
            newNode->setNext(current->getNext());
            if (current->getNext())
                current->getNext()->setPrevious(newNode);
            
            current->setNext(newNode);
            newNode->setPrevious(current);

            // If inserted at the last position, update tail.
            if (!newNode->getNext())
                m_Tail = newNode;
            
            ++m_Length; // Update length
        }

        /**
         * @brief Inserts a node at the end of the list.
         * @param data The data to insert.
         */
        void insertEnd(T data) override {
            DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(data);

            if (m_Tail) {
                downcastFunc(m_Tail)->setNext(newNode);
                newNode->setPrevious(downcastFunc(m_Tail));
            } else {
                // If list was empty, update head as well.
                m_Head = newNode;
            }

            m_Tail = newNode;
            ++m_Length; // Update length
        }

        /**
         * @brief Removes a node with the specified data.
         * @param data The data to remove.
         */
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
                    m_Tail = nullptr; // List is now empty.

                delete current;
                --m_Length; // Update length

                return;
            }

            // Traverse to find the node to remove.
            while (current != nullptr) {
                if (current->getData() == data) {
                    if (current->getNext())
                        current->getNext()->setPrevious(current->getPrevious());
                    else    
                        m_Tail = current->getPrevious(); // Update tail if last node is removed.

                    if (current->getPrevious())
                        current->getPrevious()->setNext(current->getNext());

                    delete current;
                    --m_Length; // Update length

                    return;
                }

                current = current->getNext();
            }
        }

        /**
         * @brief Removes the first node in the list.
         */
        void removeBegin() override {
            if (m_Head) {
                DoublyLinkedListNode<T>* temp = downcastFunc(m_Head);
                m_Head = m_Head->getNext();
                
                if (m_Head)
                    downcastFunc(m_Head)->setPrevious(nullptr);
                else    
                    m_Tail = nullptr; // List is now empty.

                temp->setNext(nullptr); // Prevent accidental access
                delete temp;
                --m_Length; // Update length
            }
        }

        /**
         * @brief Removes the last node in the list.
         */
        void removeEnd() override {
            if (m_Tail == nullptr)
                return;

            DoublyLinkedListNode<T>* temp = downcastFunc(m_Tail);
            m_Tail = downcastFunc(m_Tail)->getPrevious();

            if (m_Tail)
                m_Tail->setNext(nullptr);
            else    
                m_Head = nullptr; // List is now empty.

            delete temp;
            --m_Length; // Update length
        }

        /**
         * @brief Prints the list elements in forward order.
         */
        void print() const override {
            DoublyLinkedListNode<T>* current = downcastFunc(m_Head);

            while (current != nullptr) {
                std::cout << current->getData() << " <-> ";
                current = current->getNext();
            }

            std::cout << "nullptr\n";
        }
    };
} // namespace TCMS

// #pragma once

// #include <iostream>
// #include <memory>
// #include "LinkedList.hpp"
// #include "DoublyLinkedListNode.hpp"

// namespace TCMS
// {
//     template <typename T>
//     class DoublyLinkedList : public LinkedList<T, std::shared_ptr<DoublyLinkedListNode<T>>> {
//     public:
//         // using NodePtr = std::shared_ptr<DoublyLinkedListNode<T>>;
//         using Base = LinkedList<T, NodePtr>;
//         using Base::m_Head;
//         using Base::m_Tail;
//         using Base::m_Length;
//         using Base::downcastFunc;

//         DoublyLinkedList() : Base() {}

//         ~DoublyLinkedList() override {
//             clear();
//             std::cout << "DoublyLinkedList destroyed.\n";
//         }

//         void clear() {
//             while (m_Head) {
//                 removeBegin();
//             }
//         }

//         DoublyLinkedList<T> deepCopy() const {
//             DoublyLinkedList<T> newList;
//             auto current = m_Head;

//             while (current) {
//                 newList.insertEnd(current->getData());
//                 current = current->getNext();
//             }

//             return newList;
//         }

//         void insertBegin(T data) override {
//             auto newNode = std::make_shared<DoublyLinkedListNode<T>>(data);
//             newNode->setNext(m_Head);

//             if (m_Head)
//                 downcastFunc(m_Head)->setPrevious(newNode);

//             m_Head = newNode;

//             if (!m_Tail)
//                 m_Tail = newNode;

//             ++m_Length;
//         }

//         void insertPosition(T data, size_t position) override {
//             if (position == 0) {
//                 insertBegin(data);
//                 return;
//             }

//             auto current = m_Head;
//             for (size_t i = 0; i < position - 1 && current; i++) {
//                 current = current->getNext();
//             }

//             if (!current)
//                 throw std::out_of_range("Position is out of range");

//             auto newNode = std::make_shared<DoublyLinkedListNode<T>>(data);
//             newNode->setNext(current->getNext());

//             if (current->getNext())
//                 current->getNext()->setPrevious(newNode);

//             current->setNext(newNode);
//             newNode->setPrevious(current);

//             if (!newNode->getNext())
//                 m_Tail = newNode;

//             ++m_Length;
//         }

//         void insertEnd(T data) override {
//             auto newNode = std::make_shared<DoublyLinkedListNode<T>>(data);

//             if (m_Tail) {
//                 downcastFunc(m_Tail)->setNext(newNode);
//                 newNode->setPrevious(m_Tail);
//             } else {
//                 m_Head = newNode;
//             }

//             m_Tail = newNode;
//             ++m_Length;
//         }

//         void remove(T data) override {
//             if (!m_Head)
//                 return;

//             auto current = m_Head;

//             if (m_Head->getData() == data) {
//                 m_Head = m_Head->getNext();

//                 if (m_Head)
//                     downcastFunc(m_Head)->setPrevious(nullptr);
//                 else
//                     m_Tail.reset(); 

//                 current.reset(); 
//                 --m_Length;
//                 return;
//             }

//             while (current) {
//                 if (current->getData() == data) {
//                     if (current->getNext())
//                         current->getNext()->setPrevious(current->getPrevious());
//                     else
//                         m_Tail = current->getPrevious(); 

//                     if (auto prev = current->getPrevious().lock()) 
//                         prev->setNext(current->getNext());

//                     current.reset(); 
//                     --m_Length;
//                     return;
//                 }

//                 current = current->getNext();
//             }
//         }

//         void removeBegin() override {
//             if (!m_Head)
//                 return;

//             auto temp = m_Head;
//             m_Head = m_Head->getNext();

//             if (m_Head)
//                 m_Head->setPrevious(nullptr);
//             else
//                 m_Tail.reset();

//             temp.reset();
//             --m_Length;
//         }

//         void removeEnd() override {
//             if (!m_Tail)
//                 return;

//             auto temp = m_Tail;
//             m_Tail = temp->getPrevious().lock();

//             if (m_Tail)
//                 m_Tail->setNext(nullptr);
//             else
//                 m_Head.reset();

//             temp.reset();
//             --m_Length;
//         }

//         void print() const override {
//             auto current = m_Head;
//             while (current) {
//                 std::cout << current->getData() << " <-> ";
//                 current = current->getNext();
//             }
//             std::cout << "nullptr\n";
//         }
//     };
// } // namespace TCMS
