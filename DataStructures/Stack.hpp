#pragma once 

#include "../LinkedLists/SinglyLinkedList.hpp"

namespace TCMS 
{
    template <typename T>
    class Stack {
    public:
        void push(T data) {
            m_List.insertBegin(data);
        }

        T pop() {
            if (isEmpty()) 
                throw std::runtime_error("Stack is empty");

            T topData = m_List.getFirst();
            m_List.removeBegin();

            return topData;
        }

        T peek() const {
            if (isEmpty())
                throw std::runtime_error("Stack is empty");

            return m_List.getFirst();
        }

        bool isEmpty() const {
            return m_List.isEmpty(); 
        }

        void print() const {
            std::cout << "Stack (top -> bottom): ";
            m_List.print();
        }
    private:
        SinglyLinkedList<T> m_List;
    };
} // namespace TCMS