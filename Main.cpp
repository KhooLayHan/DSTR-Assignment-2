#include <iostream>
#include <string>

#include "LinkedLists/SinglyLinkedList.hpp"
#include "LinkedLists/DoublyLinkedList.hpp"
#include "LinkedLists/SinglyCircularLinkedList.hpp"

#include "DataStructures/Stack.hpp"
#include "DataStructures/Queue.hpp"
#include "DataStructures/PriorityQueue.hpp"
#include "DataStructures/CircularQueue.hpp"

int main() {
    using namespace TCMS;

    TCMS::SinglyLinkedList<int> ff;
    TCMS::DoublyLinkedList<int> ff_;
    TCMS::SinglyCircularLinkedList<int> ff_2;

    // ff.insert(10);
    // ff.insert(20);
    // ff.insert(30);

    // ff_.insert(10);
    // ff_.insert(20);
    // ff_.insert(30);
    
    // ff_2.insert(40);
    // ff_2.insert(50);
    // ff_2.insert(60);

    // ff.remove(10);
    // ff_.remove(10);
    // ff_2.remove(10);

    // ff.print();
    // ff_2.print();


    Stack<int> s1;
    s1.push(20);
    s1.push(30);
    s1.push(240);
    // s1.push(20);

    // s1.print();
    // std::cout << s1.peek() << "\n";
    s1.print();
    std::cout << s1.pop() << "\n\n";
    // s1.print();

    Queue<std::string> q1;
    q1.enqueue("10");
    q1.enqueue("20");
    q1.enqueue("30");

    q1.print();
}