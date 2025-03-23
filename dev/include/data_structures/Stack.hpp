#pragma once  // Ensures the header file is included only once in a compilation unit

#include "./linked_lists/SinglyLinkedList.hpp"  // Includes the SinglyLinkedList class

#include "Vector.hpp"

namespace TCMS  // Defines a namespace to avoid name conflicts
{
    /**
     * @brief A stack data structure implemented using a singly linked list.
     * 
     * @tparam T The type of elements stored in the stack.
     */
    template <typename T>
    class Stack {
    public:
        Vector<T> getElements() const {
            Vector<T> elements;
            SinglyLinkedListNode<T>* current = static_cast<SinglyLinkedListNode<T>*>(m_List.getHeadBase());

            // Traverse the list and collect all elements
            while (current) {
                elements.emplaceBack(current->getData());
                current = current->getNext();
            }

            return elements;
        }

        ~Stack() {
        }

        /**
         * @brief Pushes an element onto the top of the stack.
         * 
         * @param data The element to be added.
         */
        void push(T data) {
            m_List.insertBegin(data);  // Insert at the beginning to maintain LIFO order
        }

        /**
         * @brief Removes and returns the top element from the stack.
         * 
         * @return The top element of the stack.
         * @throws std::runtime_error If the stack is empty.
         */
        T pop() {
            if (isEmpty())  // Check if the stack is empty before popping
                throw std::runtime_error("Stack is empty");

            T topData = m_List.getFirst();  // Retrieve the first element
            m_List.removeBegin();  // Remove the first element

            return topData;  // Return the removed element
        }

        // /**
        //  * @brief Detaches the first node from the linked list without deleting it.
        //  * 
        //  * @return Pointer to the detached node. If the list is empty, returns nullptr.
        //  */
        // SinglyLinkedListNode<T>* detachBegin() {
        //     if (!m_Head) return nullptr;  // If the list is empty, return nullptr

        //     SinglyLinkedListNode<T>* detachedNode = m_Head;  // Store the head node
        //     m_Head = m_Head->getNext();  // Move head to the next node

        //     if (!m_Head) m_Tail = nullptr;  // If list becomes empty, update tail as well

        //     detachedNode->setNext(nullptr);  // Disconnect the detached node
        //     return detachedNode;  // Return the detached node (caller must manage memory)
        // }

        /**
         * @brief Removes and returns a pointer to the top node of the stack without deleting it.
         * 
         * @return SinglyLinkedListNode<T>* Pointer to the detached top node.
         * @throws std::runtime_error If the stack is empty.
         */
        T popNoDelete() {
            if (isEmpty()) 
                throw std::runtime_error("Stack is empty");

            T topData = m_List.getFirst(); 
            m_List.detachBegin();  // Detach the first node without deleting it
            
            return topData;
        }

        /**
         * @brief Returns the top element without removing it.
         * 
         * @return The top element of the stack.
         * @throws std::runtime_error If the stack is empty.
         */
        T peek() const {
            if (isEmpty())  // Check if the stack is empty before peeking
                throw std::runtime_error("Stack is empty");

            return m_List.getFirst();  // Return the first element without removing it
        }

        /**
         * @brief Checks whether the stack is empty.
         * 
         * @return True if the stack is empty, otherwise false.
         */
        bool isEmpty() const {
            return m_List.isEmpty();  // Returns true if the linked list is empty
        }

        /**
         * @brief Prints the elements of the stack from top to bottom.
         */
        void print() const {
            std::cout << "Stack (top -> bottom): ";
            std::cout << m_List.getFirst() << "\n";
            m_List.print();  // Print elements in LIFO order
        }

        /**
         * @brief Returns the number of elements in the stack.
         * 
         * @return The length of the stack. 
         */
        size_t getLength() const {
            return m_List.getLength();
        }

          // Iterator-like functionality
        class Iterator {
        public:
            Iterator(SinglyLinkedListNode<T>* node) : current(node) {}

            // Dereference operator
            T& operator*() const {
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
        SinglyLinkedList<T> m_List;  // Internal linked list to store stack elements
    };
} // namespace TCMS

// #pragma once  // Ensures the header file is included only once in a compilation unit

// #include <memory>  // For smart pointers
// #include "./linked_lists/SinglyLinkedList.hpp"  // Includes the SinglyLinkedList class

// namespace TCMS  // Defines a namespace to avoid name conflicts
// {
//     /**
//      * @brief A stack data structure implemented using a singly linked list.
//      * 
//      * @tparam T The type of elements stored in the stack.
//      */
//     template <typename T>
//     class Stack {
//     public:
//         /**
//          * @brief Pushes an element onto the top of the stack.
//          * 
//          * @param data The element to be added.
//          */
//         void push(std::shared_ptr<T> data) {
//             m_List.insertBegin(data);  // Insert at the beginning to maintain LIFO order
//         }

//         /**
//          * @brief Removes and returns the top element from the stack.
//          * 
//          * @return The top element of the stack as a shared pointer.
//          * @throws std::runtime_error If the stack is empty.
//          */
//         std::shared_ptr<T> pop() {
//             if (isEmpty())  // Check if the stack is empty before popping
//                 throw std::runtime_error("Stack is empty");

//             std::shared_ptr<T> topData = m_List.getFirst();  // Retrieve the first element
//             m_List.removeBegin();  // Remove the first element

//             return topData;  // Return shared_ptr to the removed element
//         }

//         /**
//          * @brief Returns the top element without removing it.
//          * 
//          * @return The top element of the stack as a shared pointer.
//          * @throws std::runtime_error If the stack is empty.
//          */
//         std::shared_ptr<T> peek() const {
//             if (isEmpty())  // Check if the stack is empty before peeking
//                 throw std::runtime_error("Stack is empty");

//             return m_List.getFirst();  // Return shared_ptr to the first element
//         }

//         /**
//          * @brief Checks whether the stack is empty.
//          * 
//          * @return True if the stack is empty, otherwise false.
//          */
//         bool isEmpty() const {
//             return m_List.isEmpty();  // Returns true if the linked list is empty
//         }

//         /**
//          * @brief Prints the elements of the stack from top to bottom.
//          */
//         void print() const {
//             std::cout << "Stack (top -> bottom): ";
//             m_List.print();  // Print elements in LIFO order
//         }
//     private:
//         SinglyLinkedList<std::shared_ptr<T>> m_List;  // Store shared_ptr objects in the list
//     };
// } // namespace TCMS
