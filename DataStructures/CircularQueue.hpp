// DataStructures/CircularQueue.hpp
#pragma once

#include <iostream>
#include "../LinkedLists/SinglyCircularLinkedList.hpp"

namespace TCMS
{
    /**
     * @brief A circular queue implementation using a singly circular linked list.
     * 
     * @tparam T The type of data stored in the queue.
     */
    template <typename T>
    class CircularQueue {
    public:

        /**
         * @brief Default constructor for an empty circular queue.
         */
        CircularQueue() : m_Length(0) {}


        /**
         * @brief Adds an element to the back of the queue.
         * 
         * @param data The value to be added.
         */
        void enqueue(T data) {
            m_List.insertEnd(data);
            m_Length++;
        }

        /**
         * @brief Removes and returns the front element of the queue.
         * 
         * @return The front element of the queue.
         * @throws std::runtime_error If the queue is empty.
         */
        T dequeue() {
            if (isEmpty())
                throw std::runtime_error("Queue is empty");
            
            T frontData = m_List.getFirst();
            m_List.removeBegin(); // Remove the front element.
            
            m_Length--;
            return frontData;
        }

        /**
         * @brief Retrieves the front element without removing it.
         * 
         * @return The front element of the queue.
         * @throws std::runtime_error If the queue is empty.
         */
        T peekFront() const {
            if (isEmpty())
                throw std::runtime_error("Queue is empty");
            
            return m_List.getFirst();
        }

        /**
         * @brief Retrieves the back element without removing it.
         * 
         * @return The back element of the queue.
         * @throws std::runtime_error If the queue is empty.
         */
        T peekBack() const {
            if (isEmpty())
                throw std::runtime_error("Queue is empty");
            
            return m_List.getLast();
        }

        /**
         * @brief Checks if the queue is empty.
         * 
         * @return True if the queue is empty, otherwise false.
         */
        bool isEmpty() const {
            return m_List.isEmpty();
        }

        /**
         * @brief Gets the current number of elements in the queue.
         * 
         * @return The number of elements.
         */
        size_t getSize() const {
            return m_Length;
        }

        /**
         * @brief Rotates the queue by moving the front element to the rear
         */
        void rotate() {
            if (isEmpty())
                throw std::runtime_error("Cannot rotate an empty CircularQueue");
            
            T frontItem = dequeue();
            enqueue(frontItem);
        }


        /**
         * @brief Prints the contents of the circular queue from front to back.
         */
        void print() const {
            std::cout << "Circular Queue (front -> back): ";
            m_List.print();
        }

    private:
        SinglyCircularLinkedList<T> m_List; ///< Internal storage using a singly circular linked list.
        int32_t m_Length;
    };
} // namespace TCMS