#pragma once 

#include "../LinkedLists/SinglyLinkedList.hpp"

namespace TCMS 
{
    template <typename T>
    class Stack {
    public:
        void push(T data) {
            list.insert(data);
        }

        T pop() {
            if (isEmpty()) 
                throw std::runtime_error("Stack is empty");

            T data = list.getFirst();
            list.remove(data);

            return data;
        }

        T peek() const {
            if (isEmpty())
                throw std::runtime_error("Stack is empty");

            return list.getFirst();
        }

        bool isEmpty() const {
            return list.isEmpty(); 
        }

        void print() const {
            list.print();
        }
    private:
        SinglyLinkedList<T> list;
    };
} // namespace TCMS