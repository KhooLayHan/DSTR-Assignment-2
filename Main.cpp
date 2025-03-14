// Main.cpp
#include <iostream>
#include "controllers/TicketingSystem.hpp"
#include "models/Ticket.hpp"
#include "models/Spectator.hpp"


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


    return 0;
}