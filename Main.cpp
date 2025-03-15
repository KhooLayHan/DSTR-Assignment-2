// #include <iostream>
// #include <string>

// #include "dev/include/data_structures/linked_lists/SinglyLinkedList.hpp"
// #include "dev/include/data_structures/linked_lists/DoublyLinkedList.hpp"
// #include "dev/include/data_structures/linked_lists/SinglyCircularLinkedList.hpp"

// #include "dev/include/data_structures/Stack.hpp"
// #include "dev/include/data_structures/Queue.hpp"
// #include "dev/include/data_structures/PriorityQueue.hpp"
// #include "dev/include/data_structures/CircularQueue.hpp"

// #include "dev/include/core/UUID.hpp"

// #include "dev/include/data_structures/Vector.hpp"

// #include "dev/include/data_structures/iterators/Iterator.hpp"
// #include "dev/include/data_structures/iterators/ForwardIterator.hpp"
// #include "dev/include/data_structures/iterators/BidirectionalIterator.hpp"
// #include "dev/include/data_structures/iterators/RandomAccessIterator.hpp"

// #include "dev/include/models/Player.hpp"
// #include "dev/include/models/Match.hpp"
// #include "dev/include/controllers/MatchScheduler.hpp"
// #include "dev/include/controllers/SeedingQueue.hpp"

// // void runKnockOutTournament(Queue<Player>& players) {
// //     MatchScheduler matchScheduler;
// //     Queue<Player> winnersQueue;

// //     while (players.getSize()) {}

// // }

// void generateKnockoutMatches(Queue<Player>& advancingPlayers, MatchScheduler& scheduler) {
//     std::cout << "\n--- Knockout Rounds Begins ---\n" ;

//     while (advancingPlayers.getLength() >= 2) {
//         Player
//     }
// }

// int main() {
//     using namespace TCMS;

//     Vector<int32_t> v1;
    
//     v1.reserve(10);
//     v1.resize(100);

//     // v1.popBack();
//     // v1.print();
    
//     v1.emplaceBack(1);
//     v1.emplaceBack(2);
//     v1.emplaceBack(3);
//     // v1.print();
    
//     // v1.popBack();
//     // v1.print();

//     v1.pushBack(4);
//     v1.pushBack(5);
//     v1.pushBack(6);
    
//     // v1.popBack();
//     v1.print();

//     // for (auto i = v1.begin(); i != v1.end(); i++) {
//     //     std::cout << *i << "\n"; 
//     // }

//     for (const auto& v : v1) 
//         std::cout << v << "\n";

//     // v1.begin();
//     // v1.end();

//     // UUID uuid;
//     // std::cout << uuid.toString() << "\n";

//     // TCMS::SinglyLinkedList<int> sll_1, sll_2, sll_3;
  
//     // sll_1.insertBegin(10);
//     // sll_1.insertBegin(20);
//     // sll_1.insertBegin(30);
//     // sll_1.print();
    
//     // sll_2.insertEnd(10);
//     // sll_2.insertEnd(20);
//     // sll_2.insertEnd(30);
//     // sll_2.print();
    
//     // sll_1.remove(20);
//     // sll_1.remove(30);
//     // sll_1.remove(10);

//     // sll_1.removeBegin();
//     // sll_1.removeEnd();

//     // sll_2.print();
    
//     // sll_3.insertPosition(10, 0);
//     // sll_3.insertPosition(20, 0);
//     // sll_3.insertPosition(30, 0);
//     // sll_3.print();

//     // sll.insertPosition(20, 1);
//     // sll.insertPosition(10, 0);
//     // sll.insertPosition(30, 2);
//     // sll.print();

//     // TCMS::DoublyLinkedList<int> dll_1, dll_2, dll_3;

//     // dll_1.insertBegin(10);
//     // dll_1.insertBegin(20);
//     // dll_1.insertBegin(30);
//     // dll_1.print();
    
//     // dll_2.insertEnd(10);
//     // dll_2.insertEnd(20);
//     // dll_2.insertEnd(30);
//     // dll_2.print();

//     // dll_3.insertPosition(10, 0);
//     // dll_3.insertPosition(20, 1);
//     // dll_3.insertPosition(30, 2);
//     // dll_3.print();

//     // dll_1.removeBegin();
//     // dll_1.removeBegin();
//     // dll_1.removeBegin();
//     // dll_1.print();

//     // dll_2.removeEnd();
//     // dll_2.removeEnd();
//     // dll_2.removeEnd();
//     // dll_2.print();

//     // dll_3.remove(10);
//     // dll_3.remove(20);
//     // dll_3.remove(30);
//     // dll_3.print();

//     // TCMS::SinglyCircularLinkedList<int> scll_1, scll_2, scll_3;

//     // scll_1.insertBegin(10);
//     // scll_1.insertBegin(20);
//     // scll_1.insertBegin(30);
//     // scll_1.print();

//     // scll_1.removeBegin();
//     // scll_1.removeBegin();
//     // scll_1.removeBegin();
//     // scll_1.print();

//     // scll_2.insertEnd(10);
//     // scll_2.insertEnd(20);
//     // scll_2.insertEnd(30);
//     // scll_2.print();

//     // scll_2.removeEnd();
//     // scll_2.removeEnd();
//     // scll_2.removeEnd();
//     // scll_2.print();
    
//     // scll_3.insertPosition(10, 0);
//     // scll_3.insertPosition(20, 1);
//     // scll_3.insertPosition(30, 3);
//     // scll_3.print();
    
//     // scll_3.remove(30);
//     // scll_3.remove(10);
//     // scll_3.remove(20);
//     // scll_3.print();

//     // std::cout << "\n\n\n";

//     // Stack<int> s1;

//     // s1.push(10);
//     // s1.push(20);
//     // s1.push(30);
//     // s1.push(50);
//     // s1.print();

//     // std::cout << s1.peek() << "\n";
//     // s1.print();

//     // std::cout << s1.pop() << "\n";
//     // s1.print();

//     // Queue<std::string> q1;

//     // q1.enqueue("10");
//     // q1.enqueue("20");
//     // q1.enqueue("30");
//     // q1.enqueue("100");
//     // q1.print();
    
//     // std::cout << q1.peekFront() << "\n";
//     // q1.print();
//     // std::cout << q1.peekBack() << "\n";
//     // q1.print();
    
//     // std::cout << q1.dequeue() << "\n";
//     // q1.print();
    
//     // std::cout << q1.dequeue() << "\n";
//     // std::cout << q1.dequeue() << "\n";
//     // q1.print();

//     // PriorityQueue<std::string> pq_1;

//     // pq_1.enqueue("World", 1);
//     // pq_1.enqueue("C++", 2);
//     // pq_1.enqueue("Hello", 0);
//     // pq_1.print();
    
//     // std::cout << pq_1.peekFront() << "\n";
//     // pq_1.print();
//     // std::cout << pq_1.peekBack() << "\n";
//     // pq_1.print();
    
//     // pq_1.dequeue();
//     // pq_1.print();
    
//     // pq_1.dequeue();
//     // pq_1.dequeue();
//     // pq_1.print();
    
//     // CircularQueue<std::string> cq_1;

//     // cq_1.enqueue("20");
//     // cq_1.enqueue("10");
//     // cq_1.enqueue("30");
//     // cq_1.enqueue("100");
//     // cq_1.print();
    
//     // std::cout << cq_1.peekFront() << "\n";
//     // cq_1.print();
//     // std::cout << cq_1.peekBack() << "\n";
//     // cq_1.print();
    
//     // std::cout << cq_1.dequeue() << "\n";
//     // cq_1.print();
    
//     // std::cout << cq_1.dequeue() << "\n";
//     // std::cout << cq_1.dequeue() << "\n";
//     // cq_1.print();

//     // std::cout << "\n\n\n";
// }