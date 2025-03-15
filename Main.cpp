// Main.cpp
#include <iostream>
#include <string>

#include "controllers/TicketingSystem.hpp"
#include "models/Ticket.hpp"
#include "models/Spectator.hpp"


#include "DataStructures/CircularQueue.hpp"
#include "DataStructures/Stack.hpp"


using namespace std;

int main() {
    using namespace TCMS;
    TicketingSystem ticketingSystem;

    // Create some tickets.  Use different Match IDs for variety.
    Ticket* ticket1 = new Ticket(TicketType::VIP, 100.0, "A1", "M1"); // Match 1
    Ticket* ticket2 = new Ticket(TicketType::EARLY_BIRD, 75.0, "B2", "M1");
    Ticket* ticket3 = new Ticket(TicketType::GENERAL, 50.0, "C3", "M2"); // Match 2
    Ticket* ticket4 = new Ticket(TicketType::GENERAL, 50.0, "C4", "M2");
    Ticket* ticket5 = new Ticket(TicketType::VIP, 110.0, "A2", "M1"); // Another VIP
    Ticket* ticket6 = new Ticket(TicketType::GENERAL, 60.0, "D5", "M3"); // Match 3

    ticketingSystem.addTicket(ticket1);
    ticketingSystem.addTicket(ticket2);
    ticketingSystem.addTicket(ticket3);
    ticketingSystem.addTicket(ticket4);
    ticketingSystem.addTicket(ticket5);
    ticketingSystem.addTicket(ticket6);


    // Create some spectators
    Spectator* spectator1 = new Spectator("Alice", 65); // VIP
    Spectator* spectator2 = new Spectator("Bob", 45);   // Early Bird
    Spectator* spectator3 = new Spectator("Charlie", 25); // General
    Spectator* spectator4 = new Spectator("David", 30); // General
    Spectator* spectator5 = new Spectator("Eve", 70);   // VIP

    // Add spectators to the queue (correct priorities are assigned in addBuyerToQueue)
    ticketingSystem.addBuyerToQueue(spectator1, TicketType::VIP); // Pass the type!
    ticketingSystem.addBuyerToQueue(spectator2, TicketType::EARLY_BIRD); // Pass the type!
    ticketingSystem.addBuyerToQueue(spectator3, TicketType::GENERAL); // Pass the type!
    ticketingSystem.addBuyerToQueue(spectator4, TicketType::GENERAL);
    ticketingSystem.addBuyerToQueue(spectator5, TicketType::VIP);
    // Sell tickets
    ticketingSystem.sellTickets();

    // Display available and sold tickets
    cout << "\n--- Available Tickets After Selling ---" << endl;
    ticketingSystem.displayAvailableTickets();
    cout << "\n--- Sold Tickets ---" << endl;
    ticketingSystem.displaySoldTickets();

    // Process entry queue (check-in)
    ticketingSystem.processEntryQueue();

    // Spectator Exit
    ticketingSystem.spectatorExit(spectator1); // Spectator 1 exits

    // Cancel a ticket (using the *actual* ticket ID, not just "T123")
    cout << "\n--- Cancelling Ticket " << ticket2->getTicketId() << " ---" << endl;
    ticketingSystem.cancelTicket(ticket2->getTicketId()); // Cancel Bob's ticket

    //Try to Cancel an exiting ticket
    cout << "\n--- Cancelling Ticket " << ticket1->getTicketId() << " ---" << endl;
    ticketingSystem.cancelTicket(ticket1->getTicketId());

    // Show available tickets after cancellation
    cout << "\n--- Available Tickets After Cancellation ---" << endl;
    ticketingSystem.displayAvailableTickets();

    //Test revenue
    cout << "\n--- Total Revenue ---" << endl;
    cout << "Total Revenue: " << ticketingSystem.getTotalRevenue() << endl;

    // --- Clean up remaining spectators ---  VERY IMPORTANT
    // Spectators 2 and 3 are still in the entry queue.  Spectator 4 never got a ticket.
    // We *must* delete them to avoid memory leaks.

    ticketingSystem.spectatorExit(spectator5); //Spectator 5 exists
    ticketingSystem.spectatorExit(spectator3); //Spectator 3 exists
    ticketingSystem.processEntryQueue();
    //delete spectator4; // Spectator 4 was never added to any queue, so delete directly.


    // TCMS::SinglyLinkedList<int> sll_1, sll_2, sll_3;
  
    // sll_1.insertBegin(10);
    // sll_1.insertBegin(20);
    // sll_1.insertBegin(30);
    // sll_1.print();
    
    // sll_2.insertEnd(10);
    // sll_2.insertEnd(20);
    // sll_2.insertEnd(30);
    // sll_2.print();
    
    // sll.remove(20);
    // sll.remove(30);
    // sll.remove(10);

    // sll.removeBegin();
    // sll.removeEnd();

    // sll.print();
    
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

    std::cout << "\n\n\n";

    return 0;
}