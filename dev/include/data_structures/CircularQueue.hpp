#pragma once

#include "./linked_lists/SinglyCircularLinkedList.hpp"

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
         * @brief Adds an element to the back of the queue.
         * 
         * @param data The value to be added.
         */
        void enqueue(T data) {
            m_List.insertEnd(data);
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
         * @brief Prints the contents of the circular queue from front to back.
         */
        void print() const {
            std::cout << "Circular Queue (front -> back): ";
            m_List.print();
        }

        /**
         * @brief Returns the number of elements in the circular queue.
         * 
         * @return The length of the circular queue. 
         */
        size_t getLength() const {
            return m_List.getLength();
        }
    private:
        SinglyCircularLinkedList<T> m_List; ///< Internal storage using a singly circular linked list.
    };
} // namespace TCMS

// #pragma once

// #include <memory>  // For smart pointers
// #include "./linked_lists/SinglyCircularLinkedList.hpp"

// namespace TCMS
// {
//     /**
//      * @brief A circular queue implementation using a singly circular linked list.
//      * 
//      * @tparam T The type of data stored in the queue.
//      */
//     template <typename T>
//     class CircularQueue {
//     public:
//         /**
//          * @brief Adds an element to the back of the queue.
//          * 
//          * @param data The value to be added.
//          */
//         void enqueue(std::shared_ptr<T> data) {
//             m_List.insertEnd(data);
//         }

//         /**
//          * @brief Removes and returns the front element of the queue.
//          * 
//          * @return The front element of the queue as a shared pointer.
//          * @throws std::runtime_error If the queue is empty.
//          */
//         std::shared_ptr<T> dequeue() {
//             if (isEmpty())
//                 throw std::runtime_error("Queue is empty");
            
//             std::shared_ptr<T> frontData = m_List.getFirst();
//             m_List.removeBegin(); // Remove the front element.
            
//             return frontData;
//         }

//         /**
//          * @brief Retrieves the front element without removing it.
//          * 
//          * @return The front element of the queue as a shared pointer.
//          * @throws std::runtime_error If the queue is empty.
//          */
//         std::shared_ptr<T> peekFront() const {
//             if (isEmpty())
//                 throw std::runtime_error("Queue is empty");
            
//             return m_List.getFirst();
//         }

//         /**
//          * @brief Retrieves the back element without removing it.
//          * 
//          * @return The back element of the queue as a shared pointer.
//          * @throws std::runtime_error If the queue is empty.
//          */
//         std::shared_ptr<T> peekBack() const {
//             if (isEmpty())
//                 throw std::runtime_error("Queue is empty");
            
//             return m_List.getLast();
//         }

//         /**
//          * @brief Checks if the queue is empty.
//          * 
//          * @return True if the queue is empty, otherwise false.
//          */
//         bool isEmpty() const {
//             return m_List.isEmpty();
//         }

//         /**
//          * @brief Prints the contents of the circular queue from front to back.
//          */
//         void print() const {
//             std::cout << "Circular Queue (front -> back): ";
//             m_List.print();
//         }
//     private:
//         SinglyCircularLinkedList<std::shared_ptr<T>> m_List; ///< Internal storage using a singly circular linked list.
//     };
// } // namespace TCMS
