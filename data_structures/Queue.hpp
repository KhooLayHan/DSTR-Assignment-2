#pragma once  // Ensures the header file is included only once in a compilation unit

#include "../linked_lists/SinglyLinkedList.hpp"  // Includes the SinglyLinkedList class

namespace TCMS  // Defines a namespace to prevent naming conflicts
{
    /**
     * @brief A queue data structure implemented using a singly linked list.
     * 
     * @tparam T The type of elements stored in the queue.
     */
    template <typename T>
    class Queue {
    public:
        /**
         * @brief Adds an element to the back (end) of the queue.
         * 
         * @param data The element to be enqueued.
         */
        void enqueue(T data) {
            m_List.insertEnd(data);  // Inserts the new element at the end of the list
        }

        /**
         * @brief Removes and returns the front element of the queue.
         * 
         * @return The front element of the queue.
         * @throws std::runtime_error If the queue is empty.
         */
        T dequeue() {
            if (isEmpty())  // Check if the queue is empty before attempting to dequeue
                throw std::runtime_error("Queue is empty");

            T frontData = m_List.getFirst();  // Retrieve the front element
            m_List.removeBegin();  // Remove the front element from the list

            return frontData;  // Return the removed element
        }

        /**
         * @brief Returns the front element without removing it.
         * 
         * @return The front element of the queue.
         * @throws std::runtime_error If the queue is empty.
         */
        T peekFront() const {
            if (isEmpty())  // Check if the queue is empty before peeking
                throw std::runtime_error("Queue is empty");
            
            return m_List.getFirst();  // Return the first element
        }

        /**
         * @brief Returns the back (rear) element without removing it.
         * 
         * @return The back element of the queue.
         * @throws std::runtime_error If the queue is empty.
         */
        T peekBack() const {
            if (isEmpty())  // Check if the queue is empty before peeking
                throw std::runtime_error("Queue is empty");
            
            return m_List.getLast();  // Return the last element
        }

        /**
         * @brief Checks whether the queue is empty.
         * 
         * @return True if the queue is empty, otherwise false.
         */
        bool isEmpty() const {
            return m_List.isEmpty();  // Returns true if the linked list is empty
        }

        /**
         * @brief Prints the elements of the queue from front to back.
         */
        void print() const {
            std::cout << "Queue (front -> back): ";
            m_List.print();  // Print elements in FIFO order
        }
    private:
        SinglyLinkedList<T> m_List;  // Internal linked list to store queue elements
    };
} // namespace TCMS
