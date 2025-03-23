#include <iostream>
#include <string>

#include "../include/data_structures/linked_lists/SinglyLinkedList.hpp"
#include "../include/data_structures/linked_lists/DoublyLinkedList.hpp"
#include "../include/data_structures/linked_lists/SinglyCircularLinkedList.hpp"

#include "../include/data_structures/Stack.hpp"
#include "../include/data_structures/Queue.hpp"
#include "../include/data_structures/PriorityQueue.hpp"
#include "../include/data_structures/CircularQueue.hpp"

#include "../include/core/UUID.hpp"

#include "../include/data_structures/Vector.hpp"

// #include "../include/data_structures/iterators/Iterator.hpp"
// #include "../include/data_structures/iterators/ForwardIterator.hpp"
// #include "../include/data_structures/iterators/BidirectionalIterator.hpp"
// #include "../include/data_structures/iterators/RandomAccessIterator.hpp"

#include "../include/models/Tournament.hpp"
#include "../include/models/Player.hpp"

#include "../include/controllers/TicketingSystem.hpp"
#include "../include/models/Ticket.hpp"
#include "../include/models/Spectator.hpp"

#include "../include/data_structures/hash_map/HashMap.hpp"

#include "../include/controllers/PlayerManager.hpp"

int main() {
    using namespace TCMS;
    std::cout << "Running...\n"; 

    // HashMap<std::string, Players> players;
    // auto player1 = std::make_shared<Player>("Roger Federez", 56, "Spain", 5, "Male", 1);
    // players[player1->getUID()] = player1;
    // auto player = std::make_shared<Player>("Alcarez", 56, "Spain", 5, "Male", 1);
    // players[player->getUID()] = player;
    // map.insert("GG", );
    // map.insert("one", 1);
    // map.insert("two", 2);
    // map.insert("something", 3);
    // map.printAll();
    // // map.
    // map.
    // std::cout << map.bucketCount() << '\n';
    // std::cout << map.getLength() << '\n';
    // std::cout << map.remove("ee") << '\n';
    // map.clear();
    // std::cout << map. << '\n';

    // std::cout << map["ff"] << "\n\n";

    // for (const auto& pair : players) {
    //     std::cout << pair.first << ": " << pair.second->getName() << std::endl;
    // }

    PlayerManager pp;
    // pp.listPlayers();
    // pp.createPlayer("Roger Federez", 56, "Spain", 5, "Male", 1);
    // pp.createPlayer("John Federez", 56, "Spain", 5, "Male", 1);
    // pp.createPlayer("Gfgg", 56, "Spain", 5, "Male", 1);
    // pp.createPlayer("Jamie", 56, "Spain", 5, "Male", 1);
    // pp.listPlayers();
    
    // pp.listPlayers();
    pp.deletePlayer("2");
    // pp.deletePlayer("1");
    // pp.deletePlayer("3");
    // pp.deletePlayer("4");
    // pp.updatePlayer("1", "ROGGHT", 32, "Germany", 5, "Fe", 1);
    // std::cout << pp.getPlayer("1")->getName();
// pp.listPlayers();
    Vector<Players> players = {
        std::make_shared<Player>("Roger Federer",         95, "Germany", 45, "M", 1),
        std::make_shared<Player>("Rafael Nadal",          90, "Germany", 45, "M", 1),
        std::make_shared<Player>("Novak Djokovic",        92, "Germany", 45, "M", 1),
        std::make_shared<Player>("Andy Murray",           85, "Germany", 45, "M", 1),
        std::make_shared<Player>("Alexander Zverev",      87, "Germany", 45, "M", 1),
        std::make_shared<Player>("Daniil Medvedev",       88, "Germany", 45, "M", 1),
        std::make_shared<Player>("Stefanos Tsitsipas",    86, "Germany", 45, "M", 1),
        std::make_shared<Player>("Carlos Alcaraz",        89, "Germany", 45, "M", 1),
    };
    // Vector<std::unique_ptr<Player>> players = {
    //     std::make_unique<Player>("Roger Federer",         95),
    //     std::make_unique<Player>("Rafael Nadal",          90),
    //     std::make_unique<Player>("Novak Djokovic",        92),
    //     std::make_unique<Player>("Andy Murray",           85),
    //     std::make_unique<Player>("Alexander Zverev",      87),
    //     std::make_unique<Player>("Daniil Medvedev",       88),
    //     std::make_unique<Player>("Stefanos Tsitsipas",    86),
    //     std::make_unique<Player>("Carlos Alcaraz",        89),
    // };
    // Vector<Players> players = {
    //     new Player("Roger Federer",         95),
    //     new Player("Rafael Nadal",          90),
    //     new Player("Novak Djokovic",        92),
    //     new Player("Andy Murray",           85),
    //     new Player("Alexander Zverev",      87),
    //     new Player("Daniil Medvedev",       88),
    //     new Player("Stefanos Tsitsipas",    86),
    //     new Player("Carlos Alcaraz",        89),
    // };

    Tournament tournament;
    tournament.runTournament(players);

    // // Clean up players in the qualifier queue
    // while (!m_QualifierQueue.isEmpty()) {
    //     delete m_QualifierQueue.dequeue();
    // }

    // // Clean up players in the advancing players queue
    // while (!m_AdvancingPlayers->isEmpty()) {
    //     delete m_AdvancingPlayers->dequeue();
    // }

    // // Delete the advancing players queue itself
    // delete m_AdvancingPlayers;
}


  
    // std::vector<int> vec = {4, 2, 5, 1, 3};

    // TCMS::RandomAccessIterator<int> begin(vec.data(), vec.data(), vec.data() + vec.size());
    // TCMS::RandomAccessIterator<int> end(vec.data() + vec.size(), vec.data(), vec.data() + vec.size());

    // static_assert(std::random_access_iterator<TCMS::RandomAccessIterator<int>>, "Iterator does not satisfy RandomAccessIterator requirements!");

    // std::sort(begin, end);  // Check for errors

    // for (auto it = begin; it != end; ++it) {
    //     std::cout << *it << " ";
    // }


// Vector<int32_t> v1;
    
    // v1.reserve(10);
    // v1.resize(100);

    // v1.popBack();
    // v1.print();
    
    // v1.emplaceBack(1);
    // v1.emplaceBack(2);
    // v1.emplaceBack(3);
    // v1.print();
    
    // v1.popBack();
    // v1.print();

    // v1.pushBack(4);
    // v1.pushBack(5);
    // v1.pushBack(6);
    
    // v1.popBack();
    // v1.print();

    // for (auto i = v1.begin(); i != v1.end(); i++) {
    //     std::cout << *i << "\n"; 
    // }

    // for (const auto& v : v1) 
    //     std::cout << v << "\n";

    // v1.begin();
    // v1.end();

    // UUID uuid;
    // std::cout << uuid.toString() << "\n";

    // TCMS::SinglyLinkedList<int> sll_1, sll_2, sll_3;
  
    // sll_1.insertBegin(10);
    // sll_1.insertBegin(20);
    // sll_1.insertBegin(30);
    // sll_1.print();
    
    // sll_2.insertEnd(10);
    // sll_2.insertEnd(20);
    // sll_2.insertEnd(30);
    // sll_2.print();
    
    // sll_1.remove(20);
    // sll_1.remove(30);
    // sll_1.remove(10);

    // sll_1.removeBegin();
    // sll_1.removeEnd();

    // sll_2.print();
    
    // sll_3.insertPosition(10, 0);
    // sll_3.insertPosition(20, 0);
    // sll_3.insertPosition(30, 0);
    // sll_3.print();

    // sll.insertPosition(20, 1);
    // sll.insertPosition(10, 0);
    // sll.insertPosition(30, 2);
    // sll.print();

    // TCMS::DoublyLinkedList<int> dll_1, dll_2, dll_3;

    // dll_1.insertBegin(10);
    // dll_1.insertBegin(20);
    // dll_1.insertBegin(30);
    // dll_1.print();
    
    // dll_2.insertEnd(10);
    // dll_2.insertEnd(20);
    // dll_2.insertEnd(30);
    // dll_2.print();

    // dll_3.insertPosition(10, 0);
    // dll_3.insertPosition(20, 1);
    // dll_3.insertPosition(30, 2);
    // dll_3.print();

    // dll_1.removeBegin();
    // dll_1.removeBegin();
    // dll_1.removeBegin();
    // dll_1.print();

    // dll_2.removeEnd();
    // dll_2.removeEnd();
    // dll_2.removeEnd();
    // dll_2.print();

    // dll_3.remove(10);
    // dll_3.remove(20);
    // dll_3.remove(30);
    // dll_3.print();

    // TCMS::SinglyCircularLinkedList<int> scll_1, scll_2, scll_3;

    // scll_1.insertBegin(10);
    // scll_1.insertBegin(20);
    // scll_1.insertBegin(30);
    // scll_1.print();

    // scll_1.removeBegin();
    // scll_1.removeBegin();
    // scll_1.removeBegin();
    // scll_1.print();

    // scll_2.insertEnd(10);
    // scll_2.insertEnd(20);
    // scll_2.insertEnd(30);
    // scll_2.print();

    // scll_2.removeEnd();
    // scll_2.removeEnd();
    // scll_2.removeEnd();
    // scll_2.print();
    
    // scll_3.insertPosition(10, 0);
    // scll_3.insertPosition(20, 1);
    // scll_3.insertPosition(30, 3);
    // scll_3.print();
    
    // scll_3.remove(30);
    // scll_3.remove(10);
    // scll_3.remove(20);
    // scll_3.print();

    // std::cout << "\n\n\n";

    // Stack<int> s1;

    // s1.push(10);
    // s1.push(20);
    // s1.push(30);
    // s1.push(50);
    // s1.print();

    // std::cout << s1.peek() << "\n";
    // s1.print();

    // std::cout << s1.pop() << "\n";
    // s1.print();

    // Queue<std::string> q1;

    // q1.enqueue("10");
    // q1.enqueue("20");
    // q1.enqueue("30");
    // q1.enqueue("100");
    // q1.print();
    
    // std::cout << q1.peekFront() << "\n";
    // q1.print();
    // std::cout << q1.peekBack() << "\n";
    // q1.print();
    
    // std::cout << q1.dequeue() << "\n";
    // q1.print();
    
    // std::cout << q1.dequeue() << "\n";
    // std::cout << q1.dequeue() << "\n";
    // q1.print();

    // PriorityQueue<std::string> pq_1;

    // pq_1.enqueue("World", 1);
    // pq_1.enqueue("C++", 2);
    // pq_1.enqueue("Hello", 0);
    // pq_1.print();
    
    // std::cout << pq_1.peekFront() << "\n";
    // pq_1.print();
    // std::cout << pq_1.peekBack() << "\n";
    // pq_1.print();
    
    // pq_1.dequeue();
    // pq_1.print();
    
    // pq_1.dequeue();
    // pq_1.dequeue();
    // pq_1.print();
    
    // CircularQueue<std::string> cq_1;

    // cq_1.enqueue("20");
    // cq_1.enqueue("10");
    // cq_1.enqueue("30");
    // cq_1.enqueue("100");
    // cq_1.print();
    
    // std::cout << cq_1.peekFront() << "\n";
    // cq_1.print();
    // std::cout << cq_1.peekBack() << "\n";
    // cq_1.print();
    
    // std::cout << cq_1.dequeue() << "\n";
    // cq_1.print();
    
    // std::cout << cq_1.dequeue() << "\n";
    // std::cout << cq_1.dequeue() << "\n";
    // cq_1.print();