#pragma once

#include "LinkedListNode.hpp"

namespace TCMS
{
    /**
     * @brief Represents a node in a singly linked list.
     * 
     * This class extends the `LinkedListNode` base class and provides
     * functionality for storing data and linking to the next node in
     * a singly linked list.
     * 
     * @tparam T Type of data stored in the node.
     */
    template <typename T>
    class SinglyLinkedListNode : public LinkedListNode<T, SinglyLinkedListNode<T>> {
    public:
        /**
         * @brief Constructs a new SinglyLinkedListNode with given data and optional next node.
         * 
         * @param data The data to be stored in the node.
         * @param next Pointer to the next node (default is nullptr).
         */
        SinglyLinkedListNode(T data, SinglyLinkedListNode<T>* next = nullptr)
            : m_Data(data), m_Next(next) {
        }

        /**
         * @brief Gets the data stored in the node.
         * 
         * @return T The data stored in the node.
         */
        T getData() const override {
            if (this == nullptr) {
                std::cerr << "Error: Attempted to access getData() on nullptr!\n";
                throw std::runtime_error("Null object access in getData()");
            }

            return m_Data;
        }

        /**
         * @brief Sets the data stored in the node.
         * 
         * @param data The new data to store in the node.
         */
        void setData(T data) override {
            m_Data = data;
        }

        /**
         * @brief Gets the next node in the list.
         * 
         * @return Pointer to the next node.
         */
        SinglyLinkedListNode<T>* getNext() const override {
            return m_Next;
        }

        /**
         * @brief Sets the next node in the list.
         * 
         * @param next Pointer to the new next node.
         */
        void setNext(SinglyLinkedListNode<T>* next) override {
            m_Next = next;
        }

    private:
        T m_Data;  // Data stored in the node.
        SinglyLinkedListNode<T>* m_Next; // Pointer to the next node in the list.
    };
} // namespace TCMS
