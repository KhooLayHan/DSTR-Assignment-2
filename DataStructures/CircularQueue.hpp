#pragma once

#include "../LinkedLists/SinglyCircularLinkedList.hpp"

namespace TCMS
{
    template <typename T>
    class CircularQueue {
    public:
        void enqueue(T data) {
            m_List.insertEnd(data);
        }

        T dequeue() {
            if (isEmpty())
                throw std::runtime_error("Queue is empty");
            
            T frontData = m_List.getFirst();
            m_List.removeBegin();
            
            return frontData;
        }

        T peekFront() const {
            if (isEmpty())
                throw std::runtime_error("Queue is empty");
            
            return m_List.getFirst();
        }

        T peekBack() const {
            if (isEmpty())
                throw std::runtime_error("Queue is empty");
            
            return m_List.getLast();
        }

        bool isEmpty() const {
            return m_List.isEmpty();
        }

        void print() const {
            std::cout << "Circular Queue (front -> back): ";
            m_List.print();
        }
    private:
        SinglyCircularLinkedList<T> m_List;
    };
} // namespace TCMS


// class CircularQueue : private CircularLinkedList {
// public:
//     void enqueue(int data) {
//         insert(data); // Insert at the tail
//     }

//     int dequeue() {
//         if (head == nullptr) throw std::runtime_error("CircularQueue is empty");
//         int data = head->getData();
//         remove(data); // Remove from the head
//         return data;
//     }

//     int peek() const {
//         if (head == nullptr) throw std::runtime_error("CircularQueue is empty");
//         return head->getData();
//     }

//     void print() const {
//         CircularLinkedList::print();
//     }
// };

// #endif // CIRCULARQUEUE_H