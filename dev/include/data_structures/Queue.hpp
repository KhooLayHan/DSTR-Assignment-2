// DataStructures/Queue.hpp
#pragma once  // Ensures the header file is included only once in a compilation unit

#include "Vector.hpp"
#include "./linked_lists/SinglyLinkedList.hpp"  // Includes the SinglyLinkedList class

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
         * @brief Returns a vector of all elements in the priority queue without modifying the priority queue.
         * 
         * @return Vector<T> A vector containing all elements in the priority queue.
         */
        Vector<T> getElements() const {
            Vector<T> elements;
            SinglyLinkedListNode<T>* current = static_cast<SinglyLinkedListNode<T>*>(m_List.getHeadBase());

            // Traverse the list and collect all elements
            while (current) {
                elements.pushBack(current->getData().m_Data);
                current = current->getNext();
            }

            return elements;
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

        ~Queue() {
            while (!isEmpty()) {
                dequeue(); // Delete each Player object
                std::cout << "Queue destructor called.\n";
            }
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
                
            // T frontData = std::move(m_List.getFirst());  // MOVE instead of COPY
            T frontData = m_List.getFirst();  // Retrieve the front element
            m_List.removeBegin();  // Remove the front element from the list

            m_Length--;
            return frontData;  // Return the removed element
        }

        // std::shared_ptr<T> dequeue() {
        //     if (isEmpty()) 
        //         throw std::runtime_error("Queue is empty");
            
        //     // Remove and return the first element
        //     // std::shared_ptr<T> data = /* remove and return the first element */;
        //     std::shared_ptr<T> data = m_List.getFirst();
        //     // m_List.
        //     return data;
        // }

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

        /**
         * @brief Returns the number of elements in the queue.
         * 
         * @return The length of the queue. 
         */
        size_t getLength() const {
            return m_List.getLength();
        }

        // Iterator-like functionality
        class Iterator {
        public:
            Iterator(SinglyLinkedListNode<T>* node) : current(node) {}

            // Dereference operator
            T& operator*() {
                return current->getData();
            }

            // Pre-increment operator
            Iterator& operator++() {
                if (current) {
                    current = static_cast<SinglyLinkedListNode<T>*>(current->getNext());
                }
                return *this;
            }

            // Inequality operator
            bool operator!=(const Iterator& other) const {
                return current != other.current;
            }

        private:
            SinglyLinkedListNode<T>* current;
        };

        // Begin iterator
        Iterator begin() const {
            return Iterator(static_cast<SinglyLinkedListNode<T>*>(m_List.getHeadBase()));
        }

        // End iterator
        Iterator end() const {
            return Iterator(nullptr);
        }
    private:
        SinglyLinkedList<T> m_List;  // Internal linked list to store queue elements
        int32_t m_Length = 0;
    };
} // namespace TCMS