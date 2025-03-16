// LinkedLists/LinkedListNode.hpp
#pragma once

// Tennis Championship Management System
namespace TCMS
{
    /**
     * @brief Base class for linked list nodes.
     * 
     * @tparam T The data type stored in the node.
     * @tparam DerivedNode The derived node type (e.g., Singly or Doubly Linked List node).
     */
    template <typename T, typename DerivedNode>
    class LinkedListNode {
    public:
        /**
         * @brief Gets the data stored in the node.
         * @return The stored data.
         */
        virtual T getData() const = 0; 

        /**
         * @brief Sets the data for the node.
         * @param data The new data value.
         */
        virtual void setData(T data) = 0;

        /**
         * @brief Gets the next node in the list.
         * @return Pointer to the next node.
         */
        virtual DerivedNode* getNext() const = 0;

        /**
         * @brief Sets the next node in the list.
         * @param next Pointer to the next node.
         */
        virtual void setNext(DerivedNode* next) = 0; 

        /**
         * @brief Virtual destructor to ensure proper cleanup in derived classes.
         */
        virtual ~LinkedListNode() = default; 
    };
} // namespace TCMS
