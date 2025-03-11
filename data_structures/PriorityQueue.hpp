#pragma once 

#include <iostream>
#include "../linked_lists/DoublyLinkedList.hpp"

namespace TCMS 
{
    /**
     * @brief A priority queue implementation using a doubly linked list.
     * 
     * @tparam T The type of data stored in the queue.
     */
    template <typename T>
    class PriorityQueue {
    private:
        /**
         * @brief Internal structure to store data along with its priority.
         */
        struct PriorityItem {
            T m_Data;           // The actual data value.
            int32_t m_Priority; // Priority level (higher values indicate higher priority).

            /**
             * @brief Compares two priority items for equality.
             * 
             * @param other The other priority item to compare against.
             * @return True if both data and priority are equal, otherwise false.
             */
            bool operator==(const PriorityItem& other) const {
                return m_Data == other.m_Data && m_Priority == other.m_Priority;
            } 

            /**
             * @brief Overloaded stream operator for printing a priority item.
             * 
             * @param output_stream The output stream.
             * @param item The priority item to print.
             * @return The modified output stream.
             */
            friend std::ostream& operator<<(std::ostream& output_stream, const PriorityItem& item) {
                output_stream << "(" << item.m_Data << ", " << item.m_Priority << ")"; 
                return output_stream;
            }
        };
    public:
        /**
         * @brief Inserts an element into the priority queue based on its priority.
         * 
         * @param data The value to be inserted.
         * @param priority The priority of the value (higher values indicate higher priority).
         */
        void enqueue(T data, int32_t priority) {
            PriorityItem newNode = { data, priority };

            // If queue is empty, insert the new item at the beginning.
            if (isEmpty()) {
                m_List.insertBegin(newNode);
                return;
            }

            size_t position = 0;
            DoublyLinkedListNode<PriorityItem>* current = 
                static_cast<DoublyLinkedListNode<PriorityItem>*>(m_List.getHeadBase());

            // Traverse the list to find the correct insertion position.
            while (current && current->getData().m_Priority <= priority) {
                position++;
                current = current->getNext();
            }

            // Insert the new node at the identified position.
            m_List.insertPosition(newNode, position);
        }

        /**
         * @brief Removes and returns the highest-priority element.
         * 
         * @return The highest-priority element.
         * @throws std::runtime_error If the queue is empty.
         */
        T dequeue() {
            if (isEmpty()) 
                throw std::runtime_error("PriorityQueue is empty");
            
            T highestPriorityData = m_List.getFirst().m_Data;
            m_List.removeBegin(); // Remove the element with the highest priority.
            return highestPriorityData;
        }

        /**
         * @brief Returns the highest-priority element without removing it.
         * 
         * @return The highest-priority element.
         * @throws std::runtime_error If the queue is empty.
         */
        T peekFront() const {
            if (isEmpty()) 
                throw std::runtime_error("PriorityQueue is empty");
            
            return m_List.getFirst().m_Data;
        }

        /**
         * @brief Returns the lowest-priority element without removing it.
         * 
         * @return The lowest-priority element.
         * @throws std::runtime_error If the queue is empty.
         */
        T peekBack() const {
            if (isEmpty()) 
                throw std::runtime_error("PriorityQueue is empty");
            
            return m_List.getLast().m_Data;
        }

        /**
         * @brief Checks if the priority queue is empty.
         * 
         * @return True if the queue is empty, otherwise false.
         */
        bool isEmpty() const {
            return m_List.isEmpty();
        }

        /**
         * @brief Prints the priority queue, showing data along with their priorities.
         */
        void print() const {
            DoublyLinkedListNode<PriorityItem>* current = 
                static_cast<DoublyLinkedListNode<PriorityItem>*>(m_List.getHeadBase());
            std::cout << "Priority Queue (Data, Priority): ";

            // Iterate through the list and print each element.
            while (current) {
                std::cout << "(" << current->getData().m_Data << ", "
                    << current->getData().m_Priority << ") -> ";
                current = current->getNext();
            }

            std::cout << "nullptr\n";
        }
    private:
        DoublyLinkedList<PriorityItem> m_List; // Internal storage using a doubly linked list.
    };
} // namespace TCMS  
