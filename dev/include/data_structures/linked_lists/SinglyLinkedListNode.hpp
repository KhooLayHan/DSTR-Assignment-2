// LinkedLists/SinglyLinkedListNode.hpp
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
        T& getData() override {
            if (!m_Data) {
                std::cerr << "Error: Attempted to access getData() on nullptr!\n";
                throw std::runtime_error("Null object access in getData()");
            }

            // if (m_Data)
                return m_Data;
            
            // return nullptr;
        }

        // /**
        //  * @brief Gets the data stored in the node.
        //  * 
        //  * @return T The data stored in the node.
        //  */
        T& getData() const {
            if (!m_Data) {
                std::cerr << "Error: Attempted to access getData() on nullptr!\n";
                throw std::runtime_error("Null object access in getData()");
            }

            // if (m_Data)
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

// #pragma once

// #include <memory>
// #include "LinkedListNode.hpp"

// namespace TCMS
// {
//     /**
//      * @brief Represents a node in a singly linked list using smart pointers.
//      *
//      * This class extends the `LinkedListNode` base class and provides
//      * functionality for storing data and linking to the next node in
//      * a singly linked list.
//      *
//      * @tparam T Type of data stored in the node.
//      */
//     template <typename T>
//     class SinglyLinkedListNode : public LinkedListNode<T, SinglyLinkedListNode<T>> {
//     public:
//         /**
//          * @brief Constructs a new SinglyLinkedListNode with given data.
//          *
//          * @param data The data to be stored in the node.
//          */
//         explicit SinglyLinkedListNode(T data)
//             : m_Data(std::move(data)), m_Next(nullptr) {
//         }

//         /**
//          * @brief Gets the data stored in the node.
//          *
//          * @return T The data stored in the node.
//          */
//         T getData() const override {
//             return m_Data;
//         }

//         /**
//          * @brief Sets the data stored in the node.
//          *
//          * @param data The new data to store in the node.
//          */
//         void setData(T data) override {
//             m_Data = std::move(data);
//         }

//         /**
//          * @brief Gets the next node in the list.
//          *
//          * @return std::unique_ptr<SinglyLinkedListNode<T>>& Reference to the unique pointer of the next node.
//          */
//         std::unique_ptr<SinglyLinkedListNode<T>>& getNext() {
//             return m_Next;
//         }

//         /**
//          * @brief Gets the next node in the list (const version).
//          *
//          * @return const std::unique_ptr<SinglyLinkedListNode<T>>& Reference to the unique pointer of the next node.
//          */
//         const std::unique_ptr<SinglyLinkedListNode<T>>& getNext() const {
//             return m_Next;
//         }

//         /**
//          * @brief Sets the next node in the list, transferring ownership.
//          *
//          * @param next Unique pointer to the new next node.
//          */
//         void setNext(std::unique_ptr<SinglyLinkedListNode<T>> next) {
//             m_Next = std::move(next);
//         }

//     private:
//         T m_Data;  // Data stored in the node.
//         std::unique_ptr<SinglyLinkedListNode<T>> m_Next; // Unique pointer to the next node.
//     };
// } // namespace TCMS

// #pragma once

// #include <memory>
// #include "LinkedListNode.hpp"

// namespace TCMS
// {
//     /**
//      * @brief Represents a node in a singly linked list using shared pointers.
//      *
//      * This class extends the `LinkedListNode` base class and provides
//      * functionality for storing data and linking to the next node in
//      * a singly linked list.
//      *
//      * @tparam T Type of data stored in the node.
//      */
//     template <typename T>
//     class SinglyLinkedListNode : public LinkedListNode<T, SinglyLinkedListNode<T>> {
//     public:
//         /**
//          * @brief Constructs a new SinglyLinkedListNode with given data.
//          *
//          * @param data The data to be stored in the node.
//          */
//         explicit SinglyLinkedListNode(T data)
//             : m_Data(std::move(data)), m_Next(nullptr) {
//         }

//         /**
//          * @brief Gets the data stored in the node.
//          *
//          * @return T The data stored in the node.
//          */
//         T getData() const override {
//             return m_Data;
//         }

//         /**
//          * @brief Sets the data stored in the node.
//          *
//          * @param data The new data to store in the node.
//          */
//         void setData(T data) override {
//             m_Data = std::move(data);
//         }

//         /**
//          * @brief Gets the next node in the list.
//          *
//          * @return std::shared_ptr<SinglyLinkedListNode<T>> Shared pointer to the next node.
//          */
//         std::shared_ptr<SinglyLinkedListNode<T>> getNext() const override {
//             return m_Next;
//         }

//         /**
//          * @brief Sets the next node in the list using a shared pointer.
//          *
//          * @param next Shared pointer to the new next node.
//          */
//         void setNext(std::shared_ptr<SinglyLinkedListNode<T>> next) override {
//             m_Next = std::move(next);
//         }

//     private:
//         T m_Data;  // Data stored in the node.
//         std::shared_ptr<SinglyLinkedListNode<T>> m_Next; // Shared pointer to the next node.
//     };
// } // namespace TCMS
