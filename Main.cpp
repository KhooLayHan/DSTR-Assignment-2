#include <iostream>
#include <string>
#include <memory>
#include "LinkedLists/SinglyLinkedList.hpp"
#include "LinkedLists/DoublyLinkedList.hpp"
#include "LinkedLists/SinglyCircularLinkedList.hpp"

#include "DataStructures/Stack.hpp"
#include "DataStructures/Queue.hpp"
#include "DataStructures/PriorityQueue.hpp"
#include "DataStructures/CircularQueue.hpp"
#include "DataStructures/Vector.hpp"

#include "models/UUID.hpp"

#include "DataStructures/iterators/Iterator.hpp"
#include "DataStructures/iterators/ForwardIterator.hpp"
#include "DataStructures/iterators/BidirectionalIterator.hpp"
#include "DataStructures/iterators/RandomAccessIterator.hpp"

#include "models/Tournament.hpp"
#include "models/Player.hpp"
#include "models/Match.hpp"

// #include "controllers/TicketingSystem.hpp"
#include "controllers/MatchHistoryTracker.hpp"
#include "models/MatchRecord.hpp"
// #include "models/Ticket.hpp"
// #include "models/Spectator.hpp"

// #include <vector>

void Task4_displayMenu()
{
    std::cout << "\033[1;34m" // 🔵 Bold Blue
              << "\n==================================\n"
              << "      🎾 MATCH HISTORY TRACKER 🎾\n"
              << "==================================\n"
              << "\033[0m"; // Reset color

    std::cout << "\033[1;33m" // 🟡 Bold Yellow
              << "1️⃣  Record Match Result\n"
              << "2️⃣  View Match History\n"
              << "3️⃣  Retrieve Specific Match\n"
              << "4️⃣  Delete Specific Match\n"
              << "5️⃣  Update Specific Match\n"
              << "6️⃣  Withdraw a Player\n"
              << "7️⃣  Undo Last Match\n"
              << "8️⃣  Exit..\n"
              << "\033[0m"; // Reset color

    std::cout << "\033[1;34m==================================\033[0m\n"; // 🔵 Blue divider
    std::cout << "👉 Enter your choice: ";
}

int main()
{
    using namespace TCMS;
    std::cout << "Running...\n";

    MatchHistoryTracker historyTracker; // Object to manage match history
    int choice;

    do
    {
        Task4_displayMenu(); // Function renamed everywhere it's called
        std::cin >> choice;

        if (std::cin.fail()) // Handle invalid input
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "\033[1;31m❌ Invalid choice! Please enter a number (1-8).\033[0m\n";
            continue;
        }

        std::cin.ignore();

        if (choice == 1) // Record match result using Task 1's Match class
        {
            std::string name1, name2;
            int skill1, skill2;
        
            std::cout << "Enter Player 1 Name: ";
            std::getline(std::cin, name1);
        
            while (true)
            {
                std::cout << "Enter Player 1 Skill Level (0-100): ";
                std::cin >> skill1;
        
                if (!std::cin.fail() && skill1 >= 0 && skill1 <= 100)
                    break;
        
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "\033[1;31m❌ Invalid skill! Please enter a number between 0 and 100.\033[0m\n";
            }
        
            std::cin.ignore(); // clear newline after number input
        
            std::cout << "Enter Player 2 Name: ";
            std::getline(std::cin, name2);
        
            while (true)
            {
                std::cout << "Enter Player 2 Skill Level (0-100): ";
                std::cin >> skill2;
        
                if (!std::cin.fail() && skill2 >= 0 && skill2 <= 100)
                    break;
        
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "\033[1;31m❌ Invalid skill! Please enter a number between 0 and 100.\033[0m\n";
            }
        
            std::cin.ignore(); // again to handle any leftover newline
        
            auto p1 = std::make_shared<TCMS::Player>(name1, skill1);
            auto p2 = std::make_shared<TCMS::Player>(name2, skill2);
        
            TCMS::Match match(p1, p2);
            auto winner = match.playMatch(); // This prints result + updates wins

            // Use the actual Match object
            historyTracker.addMatchFromPlayers(*match.getPlayer1(), *match.getPlayer2());
        
            std::cout << "\033[1;32m✅ Match recorded successfully!\033[0m\n";
        }
        
        else if (choice == 2) // Display all match history
        {
            historyTracker.displayAllHistory();
        }
        else if (choice == 3) // Retrieve a specific match
        {
            int position;
            std::cout << "Enter match position to retrieve: ";
            std::cin >> position;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "\033[1;31m❌ Invalid position! Enter a valid number.\033[0m\n";
                continue;
            }

            std::string matchDetails = historyTracker.retrieveHistory(position);
            std::cout << matchDetails << std::endl;
        }
        else if (choice == 4) // Delete a specific match
        {
            int position;
            std::cout << "Enter match position to delete: ";
            std::cin >> position;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "\033[1;31m❌ Invalid position! Enter a valid number.\033[0m\n";
                continue;
            }

            historyTracker.deleteMatch(position);
        }
        else if (choice == 5) // Update a specific match
        {
            int position;
            std::string p1, p2;
            int s1, s2;

            std::cout << "Enter match position to update: ";
            std::cin >> position;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "\033[1;31m❌ Invalid position! Enter a valid number.\033[0m\n";
                continue;
            }

            std::cin.ignore();
            std::cout << "Enter new Player 1 Name: ";
            std::getline(std::cin, p1);
            std::cout << "Enter new Player 2 Name: ";
            std::getline(std::cin, p2);
            std::cout << "Enter new " << p1 << " Score: ";
            std::cin >> s1;
            std::cout << "Enter new " << p2 << " Score: ";
            std::cin >> s2;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "\033[1;31m❌ Invalid scores! Enter valid integers.\033[0m\n";
                continue;
            }

            historyTracker.updateMatch(position, p1, p2, s1, s2);
        }
        else if (choice == 6) // Handle Player Withdrawal
        {
            int position;
            std::cout << "Enter match position to update: ";
            std::cin >> position;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "\033[1;31m❌ Invalid position! Enter a valid number.\033[0m\n";
                continue;
            }

            // Retrieve the match record based on the position
            auto matchToUpdate = historyTracker.retrieveMatch(position); // Ensure this method exists and returns a MatchRecord pointer

            if (!matchToUpdate)
            {
                std::cout << "\033[1;31m❌ Match not found!\033[0m\n";
                continue;
            }

            // Display current match details
            std::cout << "Current Match: " << matchToUpdate->getMatchDetails() << "\n";

            // Prompt user to select which player to withdraw
            std::cout << "Which player do you want to withdraw?\n";
            std::cout << "1️⃣ " << matchToUpdate->getPlayer1() << "\n";
            std::cout << "2️⃣ " << matchToUpdate->getPlayer2() << "\n";
            std::cout << "👉 Enter 1 or 2: ";

            int playerChoice;
            std::cin >> playerChoice;

            if (std::cin.fail() || (playerChoice != 1 && playerChoice != 2))
            {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "\033[1;31m❌ Invalid choice! Please enter 1 or 2.\033[0m\n";
                continue;
            }

            std::cin.ignore(); // Clear the newline character from the input buffer
            std::string newPlayer;
            std::cout << "Enter new Player Name (replacement): ";
            std::getline(std::cin, newPlayer);

            // Call the handlePlayerWithdrawal method with the selected player
            if (playerChoice == 1)
            {
                historyTracker.handlePlayerWithdrawal(position, newPlayer, true); // true for Player 1
            }
            else
            {
                historyTracker.handlePlayerWithdrawal(position, newPlayer, false); // false for Player 2
            }
        }
        else if (choice == 7) // Undo last match
        {
            historyTracker.undoLastMatch();
        }
        else if (choice == 8) // Exit the system
        {
            std::cout << "\033[1;32m✅ Exiting Match History Tracker...\033[0m\n";
        }
        else
        {
            std::cout << "\033[1;31m❌ Invalid choice! Please enter a number (1-8).\033[0m\n";
        }

    } while (choice != 8);

    // TicketingSystem ticketingSystem;

    // // Create some tickets.  Use different Match IDs for variety.
    // Ticket* ticket1 = new Ticket(TicketType::VIP, 100.0, "A1", "M1"); // Match 1
    // Ticket* ticket2 = new Ticket(TicketType::EARLY_BIRD, 75.0, "B2", "M1");
    // Ticket* ticket3 = new Ticket(TicketType::GENERAL, 50.0, "C3", "M2"); // Match 2
    // Ticket* ticket4 = new Ticket(TicketType::GENERAL, 50.0, "C4", "M2");
    // Ticket* ticket5 = new Ticket(TicketType::VIP, 110.0, "A2", "M1"); // Another VIP
    // Ticket* ticket6 = new Ticket(TicketType::GENERAL, 60.0, "D5", "M3"); // Match 3

    // MatchHios -= new
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
    // delete spectator4; // Spectator 4 was never added to any queue, so delete directly.

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

    // the code provided will have heap-use-after-free error unless using smart pointer or new/delete
    // dangling memory address

    // Tournament tournament;
    // tournament.runTournament(players);

    // std::cout << "\n\n\n";
}

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