#pragma once 

#include <iostream>
#include "./linked_lists/DoublyLinkedList.hpp"

#include "Vector.hpp"

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
            bool operator==(const PriorityItem& other) {
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
         * @brief Returns a vector of all elements in the priority queue without modifying the priority queue.
         * 
         * @return Vector<T> A vector containing all elements in the priority queue.
         */
        Vector<T> getElements() const {
            Vector<T> elements;
            DoublyLinkedListNode<PriorityItem>* current = 
                static_cast<DoublyLinkedListNode<PriorityItem>*>(m_List.getHeadBase());

            // Traverse the list and collect all elements
            while (current) {
                elements.pushBack(current->getData().m_Data);
                current = current->getNext();
            }

            return elements;
        }

        /**
         * @brief Creates a deep copy of the priority queue.
         * 
         * @return PriorityQueue<T> A new priority queue with the same elements and priorities.
         */
        PriorityQueue<T> deepCopy() const {
            PriorityQueue<T> newQueue;
            newQueue.m_List = this->m_List.deepCopy(); // Calls deep copy of DoublyLinkedList
            return newQueue;
        }

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
            
            // auto first = m_List.getFirst();
            // if (first != nullptr) {
            //     std::cout << "[DEBUG] getFirst() returning: " << first << "\n";
            // }
            // m_List.getFirst();
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

        /**
         * @brief Returns the number of elements in the priority queue.
         * 
         * @return The length of the priority queue. 
         */
        size_t getLength() const {
            return m_List.getLength();
        }

        ~PriorityQueue() {
            while (!isEmpty()) {
                dequeue(); // Delete each Player object
            }
        }
    private:
        DoublyLinkedList<PriorityItem> m_List; // Internal storage using a doubly linked list.
    };
} // namespace TCMS  


// #pragma once 

// #include <iostream>
// #include <memory>  // For smart pointers
// #include "./linked_lists/DoublyLinkedList.hpp"

// namespace TCMS 
// {
//     /**
//      * @brief A priority queue implementation using a doubly linked list.
//      * 
//      * @tparam T The type of data stored in the queue.
//      */
//     template <typename T>
//     class PriorityQueue {
//     private:
//         /**
//          * @brief Internal structure to store data along with its priority.
//          */
//         struct PriorityItem {
//             std::shared_ptr<T> m_Data;  // Use shared_ptr for safe memory management.
//             int32_t m_Priority;  // Priority level (higher values indicate higher priority).

//             /**
//              * @brief Compares two priority items for equality.
//              * 
//              * @param other The other priority item to compare against.
//              * @return True if both data and priority are equal, otherwise false.
//              */
//             bool operator==(const PriorityItem& other) const {
//                 return m_Data == other.m_Data && m_Priority == other.m_Priority;
//             } 

//             /**
//              * @brief Overloaded stream operator for printing a priority item.
//              * 
//              * @param output_stream The output stream.
//              * @param item The priority item to print.
//              * @return The modified output stream.
//              */
//             friend std::ostream& operator<<(std::ostream& output_stream, const PriorityItem& item) {
//                 output_stream << "(" << (item.m_Data ? item.m_Data->getName() : "nullptr") 
//                               << ", " << item.m_Priority << ")"; 
//                 return output_stream;
//             }
//         };
//     public:
//         /**
//          * @brief Inserts an element into the priority queue based on its priority.
//          * 
//          * @param data The value to be inserted.
//          * @param priority The priority of the value (higher values indicate higher priority).
//          */
//         void enqueue(T data, int32_t priority) {
//             PriorityItem newNode = { data, priority };

//             // If queue is empty, insert the new item at the beginning.
//             if (isEmpty()) {
//                 m_List.insertBegin(newNode);
//                 return;
//             }

//             size_t position = 0;
//             auto* current = static_cast<DoublyLinkedListNode<PriorityItem>*>(m_List.getHeadBase());

//             // Traverse the list to find the correct insertion position.
//             while (current && current->getData().m_Priority <= priority) {
//                 position++;
//                 current = current->getNext();
//             }

//             // Insert the new node at the identified position.
//             m_List.insertPosition(newNode, position);
//         }

//         /**
//          * @brief Removes and returns the highest-priority element.
//          * 
//          * @return The highest-priority element as a shared pointer.
//          * @throws std::runtime_error If the queue is empty.
//          */
//         std::shared_ptr<T> dequeue() {
//             if (isEmpty()) 
//                 throw std::runtime_error("PriorityQueue is empty");
            
//             std::shared_ptr<T> highestPriorityData = m_List.getFirst().m_Data;
//             m_List.removeBegin(); // Remove the element with the highest priority.
//             return highestPriorityData;
//         }

//         /**
//          * @brief Returns the highest-priority element without removing it.
//          * 
//          * @return The highest-priority element as a shared pointer.
//          * @throws std::runtime_error If the queue is empty.
//          */
//         std::shared_ptr<T> peekFront() const {
//             if (isEmpty()) 
//                 throw std::runtime_error("PriorityQueue is empty");
            
//             return m_List.getFirst().m_Data;
//         }

//         /**
//          * @brief Returns the lowest-priority element without removing it.
//          * 
//          * @return The lowest-priority element as a shared pointer.
//          * @throws std::runtime_error If the queue is empty.
//          */
//         std::shared_ptr<T> peekBack() const {
//             if (isEmpty()) 
//                 throw std::runtime_error("PriorityQueue is empty");
            
//             return m_List.getLast().m_Data;
//         }

//         /**
//          * @brief Checks if the priority queue is empty.
//          * 
//          * @return True if the queue is empty, otherwise false.
//          */
//         bool isEmpty() const {
//             return m_List.isEmpty();
//         }

//         /**
//          * @brief Prints the priority queue, showing data along with their priorities.
//          */
//         void print() const {
//             auto* current = static_cast<DoublyLinkedListNode<PriorityItem>*>(m_List.getHeadBase());
//             std::cout << "Priority Queue (Data, Priority): ";

//             // Iterate through the list and print each element.
//             while (current) {
//                 std::cout << "(" << (current->getData().m_Data ? current->getData().m_Data->getName() : "nullptr") 
//                           << ", " << current->getData().m_Priority << ") -> ";
//                 current = current->getNext();
//             }

//             std::cout << "nullptr\n";
//         }
//     private:
//         DoublyLinkedList<PriorityItem> m_List; // Internal storage using a doubly linked list.
//     };
// } // namespace TCMS  
