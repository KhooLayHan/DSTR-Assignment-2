#pragma once // Ensures the header file is included only once in a compilation unit

#include "./linked_lists/SinglyLinkedList.hpp" // Includes the SinglyLinkedList class

namespace TCMS // Defines a namespace to avoid name conflicts
{
    /**
     * @brief A stack data structure implemented using a singly linked list.
     *
     * @tparam T The type of elements stored in the stack.
     */
    template <typename T>
    class Stack
    {
    public:
        /**
         * @brief Pushes an element onto the top of the stack.
         *
         * @param data The element to be added.
         */
        void push(T data)
        {
            m_List.insertBegin(data); // Insert at the beginning to maintain LIFO order
            m_Length++;
        }

        /**
         * @brief Removes and returns the top element from the stack.
         *
         * @return The top element of the stack.
         * @throws std::runtime_error If the stack is empty.
         */
        T pop()
        {
            if (isEmpty()) // Check if the stack is empty before popping
                throw std::runtime_error("Stack is empty");

            T topData = m_List.getFirst(); // Retrieve the first element (copy)
            m_List.removeBegin();          // Remove the first element

            m_Length--;
            return topData; // Return the removed element
        }

        /**
         * @brief Returns the top element without removing it.
         *
         * @return The top element of the stack.
         * @throws std::runtime_error If the stack is empty.
         */
        T peek() const
        {
            if (isEmpty()) // Check if the stack is empty before peeking
                throw std::runtime_error("Stack is empty");

            return m_List.getFirst(); // Return the first element without removing it
        }

        /**
         * @brief Checks whether the stack is empty.
         *
         * @return True if the stack is empty, otherwise false.
         */
        bool isEmpty() const
        {
            return m_List.isEmpty(); // Returns true if the linked list is empty
        }

        /**
         * @brief Returns the length of the queue.
         *
         * @return The length of the queue.
         */
        size_t getLength() const
        {
            return m_Length;
        }

        /**
         * @brief Prints the elements of the stack from top to bottom.
         */
        void print() const
        {
            std::cout << "Stack (top -> bottom): ";
            m_List.print(); // Print elements in LIFO order
        }

    private:
        SinglyLinkedList<T> m_List; // Internal linked list to store stack elements
        int32_t m_Length = 0;
    };
} // namespace TCMS
