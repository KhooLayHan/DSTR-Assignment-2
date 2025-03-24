#pragma once

#include "./linked_lists/SinglyLinkedList.hpp"
#include "Vector.hpp"

namespace TCMS
{
    /**
     * @brief A stack data structure implemented using a singly linked list.
     * 
     * @tparam T The type of elements stored in the stack.
     */
    template <typename T>
    class Stack {
    public:
        /**
         * @brief Returns a vector containing all elements in the stack.
         * 
         * @return Vector<T> A vector with all stack elements.
         */
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

        /**
         * @brief Destructor. Cleans up the stack.
         */
        ~Stack() {
            // No explicit cleanup needed as SinglyLinkedList handles it
        }

        /**
         * @brief Pushes an element onto the top of the stack.
         * 
         * @param data The element to be added.
         */
        void push(T data) {
            m_List.insertBegin(data);  // Insert at the beginning to maintain LIFO order
            m_Length++;
        }

        /**
         * @brief Removes and returns the top element from the stack.
         * 
         * @return T The top element of the stack.
         * @throws std::runtime_error If the stack is empty.
         */
        T pop() {
            if (isEmpty())  // Check if the stack is empty before popping
                throw std::runtime_error("Stack is empty");

            T topData = m_List.getFirst();  // Retrieve the first element
            m_List.removeBegin();  // Remove the first element

            m_Length--;
            return topData;  // Return the removed element
        }

        /**
         * @brief Removes and returns a pointer to the top node of the stack without deleting it.
         * 
         * @return T The top element of the stack.
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
         * @return T The top element of the stack.
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
         * @return true If the stack is empty.
         * @return false If the stack is not empty.
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
         * @return size_t The length of the stack.
         */
        size_t getLength() const {
            return m_Length;
        }

        /**
         * @brief Iterator class for the stack.
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
            T& operator*() const {
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
         * @brief Returns an iterator to the beginning of the stack.
         * 
         * @return Iterator An iterator to the top of the stack.
         */
        Iterator begin() const {
            return Iterator(static_cast<SinglyLinkedListNode<T>*>(m_List.getHeadBase()));
        }

        /**
         * @brief Returns an iterator to the end of the stack.
         * 
         * @return Iterator An iterator to the end of the stack.
         */
        Iterator end() const {
            return Iterator(nullptr);
        }

    private:
        SinglyLinkedList<T> m_List;  // Internal linked list to store stack elements
        size_t m_Length = 0;
    };
} // namespace TCMS