#pragma once

#include "Vector.hpp"
#include "./linked_lists/SinglyLinkedList.hpp"

namespace TCMS
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
         * @brief Returns a vector of all elements in the queue without modifying the queue.
         * 
         * @return Vector<T> A vector containing all elements in the queue.
         */
        Vector<T> getElements() const {
            Vector<T> elements;
            SinglyLinkedListNode<T>* current = static_cast<SinglyLinkedListNode<T>*>(m_List.getHeadBase());

            // Traverse the list and collect all elements
            while (current) {
                elements.pushBack(current->getData());
                current = current->getNext();
            }

            return elements;
        }

        /**
         * @brief Destructor. Cleans up the queue by dequeuing all elements.
         */
        ~Queue() {
            // while (!isEmpty()) {
                // dequeue(); // Delete each element
                // std::cout << "Queue destructor called.\n";
            // }
        }

        /**
         * @brief Adds an element to the back (end) of the queue.
         * 
         * @param data The element to be enqueued.
         */
        void enqueue(T data) {
            m_List.insertEnd(data);  // Inserts the new element at the end of the list
            m_Length++;
        }

        /**
         * @brief Removes and returns the front element of the queue.
         * 
         * @return T The front element of the queue.
         * @throws std::runtime_error If the queue is empty.
         */
        T dequeue() {
            if (isEmpty())  // Check if the queue is empty before attempting to dequeue
                throw std::runtime_error("Queue is empty");

            T frontData = m_List.getFirst();  // Retrieve the front element
            m_List.removeBegin();  // Remove the front element from the list

            m_Length--;
            return frontData;  // Return the removed element
        }

        /**
         * @brief Returns the front element without removing it.
         * 
         * @return T The front element of the queue.
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
         * @return T The back element of the queue.
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
         * @return true If the queue is empty.
         * @return false If the queue is not empty.
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

        /**
         * @brief Returns the number of elements in the queue.
         * 
         * @return size_t The length of the queue.
         */
        size_t getLength() const {
            return m_Length;
        }

        /**
         * @brief Iterator class for the queue.
         */
        class Iterator {
        public:
            /**
             * @brief Constructs an iterator starting at the given node.
             * 
             * @param node The starting node for the iterator.
             */
            Iterator(SinglyLinkedListNode<T>* node) : current(node) {}

            /**
             * @brief Dereference operator. Returns the data at the current node.
             * 
             * @return T& A reference to the data at the current node.
             */
            T& operator*() {
                return current->getData();
            }

            /**
             * @brief Pre-increment operator. Moves the iterator to the next node.
             * 
             * @return Iterator& A reference to the updated iterator.
             */
            Iterator& operator++() {
                if (current) {
                    current = static_cast<SinglyLinkedListNode<T>*>(current->getNext());
                }
                return *this;
            }

            /**
             * @brief Inequality operator. Checks if two iterators are not equal.
             * 
             * @param other The iterator to compare with.
             * @return true If the iterators are not equal.
             * @return false If the iterators are equal.
             */
            bool operator!=(const Iterator& other) const {
                return current != other.current;
            }

        private:
            SinglyLinkedListNode<T>* current;  // Pointer to the current node
        };

        /**
         * @brief Returns an iterator to the beginning of the queue.
         * 
         * @return Iterator An iterator to the front of the queue.
         */
        Iterator begin() const {
            return Iterator(static_cast<SinglyLinkedListNode<T>*>(m_List.getHeadBase()));
        }

        /**
         * @brief Returns an iterator to the end of the queue.
         * 
         * @return Iterator An iterator to the end of the queue.
         */
        Iterator end() const {
            return Iterator(nullptr);
        }

    private:
        SinglyLinkedList<T> m_List;  // Internal linked list to store queue elements
        int32_t m_Length = 0;        // Number of elements in the queue
    };
} // namespace TCMS