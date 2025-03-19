//LinkedLists/LinkedList.hpp
#pragma once

#include <iostream>
#include "LinkedListNode.hpp"

namespace TCMS
{
    /**
     * @brief Template base class for LinkedList.
     * 
     * @tparam T The data type stored in the list.
     * @tparam DerivedNode The derived node type (e.g., Singly or Doubly Linked List node).
     */
    template <typename T, typename DerivedNode>
    class LinkedList {
    public:
        /**
         * @brief Default constructor initializes an empty list.
         */
        LinkedList() : m_Head(nullptr), m_Tail(nullptr), m_Length(0) {}

        /**
         * @brief Virtual destructor to allow proper cleanup in derived classes.
         */
        virtual ~LinkedList() = default;

        /**
         * @brief Inserts a new node at the beginning of the list.
         * @param data The value to insert.
         */
        virtual void insertBegin(T data) = 0;

        /**
         * @brief Inserts a new node at a specific position.
         * @param data The value to insert.
         * @param position The index where the node should be inserted.
         */
        virtual void insertPosition(T data, size_t position) = 0;

        /**
         * @brief Inserts a new node at the end of the list.
         * @param data The value to insert.
         */
        virtual void insertEnd(T data) = 0;
        
        /**
         * @brief Removes a node containing the specified data.
         * @param data The value to remove.
         */
        virtual void remove(T data) = 0;

        /**
         * @brief Removes the first node from the list.
         */
        virtual void removeBegin() = 0;

        /**
         * @brief Removes the last node from the list.
         */
        virtual void removeEnd() = 0;

        /**
         * @brief Prints the contents of the list.
         */
        virtual void print() const = 0;

        /**
         * @brief Gets the base class pointer to the head node.
         * @return Pointer to the head node.
         */
        LinkedListNode<T, DerivedNode>* getHeadBase() const {
            return m_Head;
        }

        /**
         * @brief Gets the base class pointer to the tail node.
         * @return Pointer to the tail node.
         */
        LinkedListNode<T, DerivedNode>* getTailBase() const {
            return m_Tail;
        }

        /**
         * @brief Gets the data from the first node.
         * @return The first node's data.
         * @throws std::runtime_error if the list is empty.
         */
        T getFirst() const {
            // if (isEmpty()) {
            //     throw std::runtime_error("List is empty");
            // }
            
            // std::cout << "[DEBUG] getFirst() returning: " << getHeadBase()->getData() << "\n";
            // return getHeadBase()->getData();

            if (isEmpty() || !m_Head) {
                throw std::runtime_error("List is empty");
            }
        
            LinkedListNode<T, DerivedNode>* headNode = getHeadBase();
            if (!headNode) {
                throw std::runtime_error("Corrupted list: Head is nullptr");
            }
        
            // std::cout << "[DEBUG] getFirst() returning: " << headNode->getData() << "\n";
            return headNode->getData();
        }

        /**
         * @brief Gets the data from the last node.
         * @return The last node's data.
         * @throws std::runtime_error if the list is empty.
         */
        T getLast() const {
            if (isEmpty()) {
                throw std::runtime_error("List is empty");
            }
            return getTailBase()->getData();
        }

        /**
         * @brief Checks if the list is empty.
         * @return True if the list is empty, otherwise false.
         */
        bool isEmpty() const {
            return m_Head == nullptr;
        }

        /**
         * @brief Returns the length of the list in O(1) time.
         * @return The number of nodes in the list.
         */
        size_t getLength() const {
            return m_Length;
        }
    protected:
        LinkedListNode<T, DerivedNode>* m_Head; // Pointer to the first node in the list.
        LinkedListNode<T, DerivedNode>* m_Tail; // Pointer to the last node in the list.
        size_t m_Length; // Stores the number of nodes in the list.

        /**
         * @brief Upcasts a DerivedNode pointer to LinkedListNode<T, DerivedNode>*.
         * @param node Pointer to the derived node.
         * @return Upcasted pointer as LinkedListNode<T, DerivedNode>*.
         */
        LinkedListNode<T, DerivedNode>* upcastFunc(DerivedNode* node) {
            return static_cast<LinkedListNode<T, DerivedNode>*>(node);
        }

        /**
         * @brief Downcasts a LinkedListNode<T, DerivedNode>* pointer to DerivedNode*.
         * @param node Pointer to the base class node.
         * @return Downcasted pointer as DerivedNode*.
         */
        DerivedNode* downcastFunc(LinkedListNode<T, DerivedNode>* node) const {
            return static_cast<DerivedNode*>(node);
        }
    };
} // namespace TCMS


// #pragma once

// #include <iostream>
// #include <memory>
// #include "LinkedListNode.hpp"

// namespace TCMS
// {
//     /**
//      * @brief Template base class for LinkedList.
//      * 
//      * @tparam T The data type stored in the list.
//      * @tparam DerivedNode The derived node type (e.g., Singly or Doubly Linked List node).
//      */
//     template <typename T, typename DerivedNode>
//     class LinkedList {
//     public:
//         /**
//          * @brief Default constructor initializes an empty list.
//          */
//         LinkedList() : m_Head(nullptr), m_Tail(nullptr), m_Length(0) {}

//         /**
//          * @brief Virtual destructor to allow proper cleanup in derived classes.
//          */
//         virtual ~LinkedList() = default;

//         /**
//          * @brief Inserts a new node at the beginning of the list.
//          * @param data The value to insert.
//          */
//         virtual void insertBegin(T data) = 0;

//         /**
//          * @brief Inserts a new node at a specific position.
//          * @param data The value to insert.
//          * @param position The index where the node should be inserted.
//          */
//         virtual void insertPosition(T data, size_t position) = 0;

//         /**
//          * @brief Inserts a new node at the end of the list.
//          * @param data The value to insert.
//          */
//         virtual void insertEnd(T data) = 0;
        
//         /**
//          * @brief Removes a node containing the specified data.
//          * @param data The value to remove.
//          */
//         virtual void remove(T data) = 0;

//         /**
//          * @brief Removes the first node from the list.
//          */
//         virtual void removeBegin() = 0;

//         /**
//          * @brief Removes the last node from the list.
//          */
//         virtual void removeEnd() = 0;

//         /**
//          * @brief Prints the contents of the list.
//          */
//         virtual void print() const = 0;

//         /**
//          * @brief Gets the base class pointer to the head node.
//          * @return Shared pointer to the head node.
//          */
//         std::shared_ptr<LinkedListNode<T, DerivedNode>> getHeadBase() const {
//             return m_Head;
//         }

//         /**
//          * @brief Gets the base class pointer to the tail node.
//          * @return Shared pointer to the tail node.
//          */
//         std::shared_ptr<LinkedListNode<T, DerivedNode>> getTailBase() const {
//             return m_Tail;
//         }

//         /**
//          * @brief Gets the data from the first node.
//          * @return The first node's data.
//          * @throws std::runtime_error if the list is empty.
//          */
//         T getFirst() const {
//             if (isEmpty()) {
//                 throw std::runtime_error("List is empty");
//             }
//             std::cout << "[DEBUG] getFirst() returning: " << m_Head->getData() << "\n";
//             return m_Head->getData();
//         }

//         /**
//          * @brief Gets the data from the last node.
//          * @return The last node's data.
//          * @throws std::runtime_error if the list is empty.
//          */
//         T getLast() const {
//             if (isEmpty()) {
//                 throw std::runtime_error("List is empty");
//             }
//             return m_Tail->getData();
//         }

//         /**
//          * @brief Checks if the list is empty.
//          * @return True if the list is empty, otherwise false.
//          */
//         bool isEmpty() const {
//             return m_Head == nullptr;
//         }

//         /**
//          * @brief Returns the length of the list in O(1) time.
//          * @return The number of nodes in the list.
//          */
//         size_t getLength() const {
//             return m_Length;
//         }

//     protected:
//         std::shared_ptr<LinkedListNode<T, DerivedNode>> m_Head; // Shared pointer to the first node in the list.
//         std::shared_ptr<LinkedListNode<T, DerivedNode>> m_Tail; // Shared pointer to the last node in the list.
//         size_t m_Length; // Stores the number of nodes in the list.

//         /**
//          * @brief Upcasts a `std::shared_ptr<DerivedNode>` to `std::shared_ptr<LinkedListNode<T, DerivedNode>>`.
//          * @param node Shared pointer to the derived node.
//          * @return Upcasted shared pointer.
//          */
//         std::shared_ptr<LinkedListNode<T, DerivedNode>> upcastFunc(std::shared_ptr<DerivedNode> node) {
//             return std::static_pointer_cast<LinkedListNode<T, DerivedNode>>(node);
//         }

//         /**
//          * @brief Downcasts a `std::shared_ptr<LinkedListNode<T, DerivedNode>>` to `std::shared_ptr<DerivedNode>`.
//          * @param node Shared pointer to the base class node.
//          * @return Downcasted shared pointer.
//          */
//         std::shared_ptr<DerivedNode> downcastFunc(std::shared_ptr<LinkedListNode<T, DerivedNode>> node) const {
//             return std::static_pointer_cast<DerivedNode>(node);
//         }
//     };
// } // namespace TCMS
