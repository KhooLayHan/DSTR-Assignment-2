#include <iostream>

#include "./models/System.hpp"

int main() {
    using namespace TCMS;
    std::cout << "Running...\n"; 

    // TCMS::Vector<std::shared_ptr<TCMS::Player>> players = {
    //     std::make_shared<Player>("Roger Federer",         95),
    //     std::make_shared<Player>("Rafael Nadal",          90),
    //     std::make_shared<Player>("Novak Djokovic",        92),
    //     std::make_shared<Player>("Andy Murray",           85),
    //     std::make_shared<Player>("Alexander Zverev",      87),
    //     std::make_shared<Player>("Daniil Medvedev",       88),
    //     std::make_shared<Player>("Stefanos Tsitsipas",    86),
    //     std::make_shared<Player>("Carlos Alcaraz",        89),
    // };

    System::Init();
    System::Run();
    System::ShutDown();
}
    // std::vector<int> vec = {4, 2, 5, 1, 3};

    // TCMS::RandomAccessIterator<int> begin(vec.data(), vec.data(), vec.data() + vec.size());
    // TCMS::RandomAccessIterator<int> end(vec.data() + vec.size(), vec.data(), vec.data() + vec.size());

    // static_assert(std::random_access_iterator<TCMS::RandomAccessIterator<int>>, "Iterator does not satisfy RandomAccessIterator requirements!");

    // std::sort(begin, end);  // Check for errors

    // for (auto it = begin; it != end; ++it) {
    //     std::cout << *it << " ";
    // }

    // Tournament tournament;
    // tournament.runTournament(players);

    

    // std::cout << "\n\n\n";
    
    // try {
    //     std::cout << "Starting Asia Pacific University Tennis Championship Ticketing System...\n";
        
    //     // Create and run the ticketing menu
    //     TCMS::TicketingMenu menu;
    //     menu.run();
        
    //     std::cout << "Program terminated successfully.\n";
    //     return 0;
    // }
    // catch (const std::exception& e) {
    //     std::cerr << "Error: " << e.what() << std::endl;
    //     return 1;
    // }
    // catch (...) {
    //     std::cerr << "Unknown error occurred." << std::endl;
    //     return 2;
    // }


    // TicketingSystem ticketingSystem;

    // // Create some tickets.  Use different Match IDs for variety.
    // Ticket* ticket1 = new Ticket(TicketType::VIP, 100.0, "A1", "M1"); // Match 1
    // Ticket* ticket2 = new Ticket(TicketType::EARLY_BIRD, 75.0, "B2", "M1");
    // Ticket* ticket3 = new Ticket(TicketType::GENERAL, 50.0, "C3", "M2"); // Match 2
    // Ticket* ticket4 = new Ticket(TicketType::GENERAL, 50.0, "C4", "M2");
    // Ticket* ticket5 = new Ticket(TicketType::VIP, 110.0, "A2", "M1"); // Another VIP
    // Ticket* ticket6 = new Ticket(TicketType::GENERAL, 60.0, "D5", "M3"); // Match 3

    // ticketingSystem.addTicket(ticket1);
    // ticketingSystem.addTicket(ticket2);
    // ticketingSystem.addTicket(ticket3);
    // ticketingSystem.addTicket(ticket4);
    // ticketingSystem.addTicket(ticket5);
    // ticketingSystem.addTicket(ticket6);


    // // Create some spectators
    // Spectator* spectator1 = new Spectator("Alice", 65); // VIP
    // Spectator* spectator2 = new Spectator("Bob", 45);   // Early Bird
    // Spectator* spectator3 = new Spectator("Charlie", 25); // General
    // Spectator* spectator4 = new Spectator("David", 30); // General
    // Spectator* spectator5 = new Spectator("Eve", 70);   // VIP

    // // Add spectators to the queue (correct priorities are assigned in addBuyerToQueue)
    // ticketingSystem.addBuyerToQueue(spectator1, TicketType::VIP); // Pass the type!
    // ticketingSystem.addBuyerToQueue(spectator2, TicketType::EARLY_BIRD); // Pass the type!
    // ticketingSystem.addBuyerToQueue(spectator3, TicketType::GENERAL); // Pass the type!
    // ticketingSystem.addBuyerToQueue(spectator4, TicketType::GENERAL);
    // ticketingSystem.addBuyerToQueue(spectator5, TicketType::VIP);
    // // Sell tickets
    // ticketingSystem.sellTickets();

    // // Display available and sold tickets
    // std::cout << "\n--- Available Tickets After Selling ---\n";
    // ticketingSystem.displayAvailableTickets();
    // std::cout << "\n--- Sold Tickets ---\n";
    // ticketingSystem.displaySoldTickets();

    // // Process entry queue (check-in)
    // ticketingSystem.processEntryQueue();

    // // Spectator Exit
    // ticketingSystem.spectatorExit(spectator1); // Spectator 1 exits

    // // Cancel a ticket (using the *actual* ticket ID, not just "T123")
    // std::cout << "\n--- Cancelling Ticket " << ticket2->getTicketId() << " ---\n";
    // ticketingSystem.cancelTicket(ticket2->getTicketId()); // Cancel Bob's ticket

    // //Try to Cancel an exiting ticket
    // std::cout << "\n--- Cancelling Ticket " << ticket1->getTicketId() << " ---\n";
    // ticketingSystem.cancelTicket(ticket1->getTicketId());

    // // Show available tickets after cancellation
    // std::cout << "\n--- Available Tickets After Cancellation ---\n";
    // ticketingSystem.displayAvailableTickets();

    // //Test revenue
    // std::cout << "\n--- Total Revenue ---\n";
    // std::cout << "Total Revenue: " << ticketingSystem.getTotalRevenue() << "\n";

    // // --- Clean up remaining spectators ---  VERY IMPORTANT
    // // Spectators 2 and 3 are still in the entry queue.  Spectator 4 never got a ticket.
    // // We *must* delete them to avoid memory leaks.

    // ticketingSystem.spectatorExit(spectator5); //Spectator 5 exists
    // ticketingSystem.spectatorExit(spectator3); //Spectator 3 exists
    // ticketingSystem.processEntryQueue();
    //delete spectator4; // Spectator 4 was never added to any queue, so delete directly.


    
