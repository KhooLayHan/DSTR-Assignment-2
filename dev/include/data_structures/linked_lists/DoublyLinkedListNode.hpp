// LinkedLists/DoublyLinkedListNode.hpp
#pragma once

#include "LinkedListNode.hpp"

// Tennis Championship Management System
namespace TCMS
{
    /**
     * @brief DoublyLinkedListNode class, extending LinkedListNode<T, DoublyLinkedListNode<T>>.
     *        This node structure supports bidirectional traversal.
     */
    template <typename T>
    class DoublyLinkedListNode : public LinkedListNode<T, DoublyLinkedListNode<T>> {
    public:
        /**
         * @brief Constructs a new DoublyLinkedListNode.
         * @param data The value to store in the node.
         * @param next Pointer to the next node (default: nullptr).
         * @param previous Pointer to the previous node (default: nullptr).
         */
        DoublyLinkedListNode(T data, DoublyLinkedListNode<T>* next = nullptr, DoublyLinkedListNode<T>* previous = nullptr)
            : m_Data(data), m_Next(next), m_Previous(previous) {}

        /**
         * @brief Gets the data stored in the node.
         * @return The data of the node.
         */
        T& getData() override {
            // if (this == nullptr) {
            //     std::cerr << "Error: Attempted to access getData() on nullptr!\n";
            //     throw std::runtime_error("Null object access in getData()");
            // }
            return m_Data;
        }

        /**
         * @brief Sets the data stored in the node.
         * @param data The new value to assign.
         */
        void setData(T data) override {
            m_Data = data;
        }

        /**
         * @brief Gets the pointer to the next node.
         * @return Pointer to the next node.
         */
        DoublyLinkedListNode<T>* getNext() const override {
            return m_Next;
        }

        /**
         * @brief Sets the pointer to the next node.
         * @param next Pointer to the new next node.
         */
        void setNext(DoublyLinkedListNode<T>* next) override {
            m_Next = next;
        }

        /**
         * @brief Gets the pointer to the previous node.
         * @return Pointer to the previous node.
         */
        DoublyLinkedListNode<T>* getPrevious() const {
            return m_Previous;
        }

        /**
         * @brief Sets the pointer to the previous node.
         * @param previous Pointer to the new previous node.
         */
        void setPrevious(DoublyLinkedListNode<T>* previous) {
            m_Previous = previous;
        }

    private:
        T m_Data; // The data stored in the node.
        DoublyLinkedListNode<T>* m_Next; // Pointer to the next node.
        DoublyLinkedListNode<T>* m_Previous; // Pointer to the previous node.
    };
} // namespace TCMS

// #pragma once

// #include "LinkedListNode.hpp"
// #include <memory>  // For smart pointers

// // Tennis Championship Management System
// namespace TCMS
// {
//     template <typename T>
//     class DoublyLinkedListNode : public LinkedListNode<T, DoublyLinkedListNode<T>> {
//     public:
//         explicit DoublyLinkedListNode(T data)
//             : m_Data(std::move(data)), m_Next(nullptr), m_Previous() {}

//         T getData() const override {
//             return m_Data;
//         }

//         void setData(T data) override {
//             m_Data = std::move(data);
//         }

//         std::shared_ptr<DoublyLinkedListNode<T>> getNext() const override {
//             return m_Next;
//         }

//         void setNext(std::shared_ptr<DoublyLinkedListNode<T>> next) override {
//             m_Next = std::move(next);
//         }

//         std::shared_ptr<DoublyLinkedListNode<T>> getPrevious() const {
//             return m_Previous.lock(); // Convert weak_ptr to shared_ptr
//         }

//         void setPrevious(const std::shared_ptr<DoublyLinkedListNode<T>>& previous) {
//             m_Previous = previous;
//         }

//     private:
//         T m_Data;
//         std::shared_ptr<DoublyLinkedListNode<T>> m_Next; // Shared ownership for next node
//         std::weak_ptr<DoublyLinkedListNode<T>> m_Previous; // Non-owning reference to avoid cycles
//     };
// } // namespace TCMS
