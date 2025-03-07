#pragma once 

#include "../LinkedList/SinglyLinkedList.hpp"

namespace TCMS 
{
    template <typename T>
    class Stack : private SinglyLinkedList<T> {
    public:
        void push(T data) {
            insert(data);
        }

        T pop() {
            if (m_Head == nullptr) 
                throw std::runtime_error("Stack is empty");

            T data = m_Head->getData();
            remove(data);

            return data;
        }

        T peek() const {
            if (m_Head == nullptr)
                throw std::runtime_error("Stack is empty");

            return m_Head->getData();
        }

        void print() const {
            SinglyLinkedList<T>::print();
        }
    };
} // namespace TCMS