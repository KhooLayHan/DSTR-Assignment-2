// #ifndef CIRCULARQUEUE_H
// #define CIRCULARQUEUE_H

// #include "../LinkedLists/SinglyCircularLinkedList.hpp"

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