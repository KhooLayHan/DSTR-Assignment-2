#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "../core/UUID.hpp"
#include "../core/UID.hpp"

#include "../data_structures/linked_lists/SinglyLinkedList.hpp"
#include "../data_structures/linked_lists/DoublyLinkedList.hpp"
#include "../data_structures/linked_lists/SinglyCircularLinkedList.hpp"

#include "../data_structures/Stack.hpp"
#include "../data_structures/Queue.hpp"
#include "../data_structures/PriorityQueue.hpp"
#include "../data_structures/CircularQueue.hpp"

#include "../data_structures/Vector.hpp"

// Task 1
#include "../controllers/PlayerManager.hpp"
#include "../models/Tournament.hpp"
#include "../models/Player.hpp"
#include "../models/Match.hpp"

// Task 3
#include "../controllers/WithdrawalManager.hpp"
#include "../controllers/MatchScheduler.hpp"

// Task 4
#include "../controllers/MatchHistoryTracker.hpp"
#include "../models/MatchRecord.hpp"

namespace TCMS
{
    void task1() {
        Vector<Players> players;
        FileHandling::readPlayerFile("./logs/player.txt", players);
        
        PlayerManager playerManager;
        playerManager.registerPlayers(players);

        Tournament tournament;
                
        std::cout << "\n|----------------------------------------------|\n";
        std::cout << "|              WELCOME TO TASK 1               |\n|----------------------------------------------|\n";
        std::cout << "| Tournament Scheduling and Player Progression |\n|----------------------------------------------|\n";
        std::cout << "|         By: Khoo Lay Han TP079817            |\n|----------------------------------------------|\n";

        auto initHeader = []{        
            std::cout << "\nWhat do you want to do?\n";
            std::cout << "1: Add New Player\t\t2. Read Existing Player\n";
            std::cout << "3: Update Existing Player\t4. Delete Existing Player\n";
            std::cout << "5: List All Players\t\t6. Run Tournament\n";
            std::cout << "7: Quit\n";
            
            std::cout << "\nInput: ";
        };

        bool isInput = true;
        std::string input;

        while (isInput == true) {
            initHeader();
            std::cin >> input;

            if (input == "1") {
                std::cout << "What is the Player's Name and Skill Level: ";
                    
                std::string name, skillLevel;
                std::cin >> name >> skillLevel;

                playerManager.createPlayer(name, std::stoi(skillLevel));
            } else if (input == "2") {
                std::cout << "What is the Player's UID: ";
                        
                std::string uid;
                std::cin >> uid;

                playerManager.getPlayer(uid);  
            } else if (input == "3") {
                std::cout << "What is the Player's UID to Update: ";
                    
                std::string uid, name;
                int32_t skillLevel;
                std::cin >> uid;
                
                std::cout << "\nWhat is the Player's new Name and Skill Level: ";
                std::cin >> name >> skillLevel;
                
                playerManager.updatePlayer(uid, name, skillLevel);
            } else if (input == "4") {
                std::cout << "What is Player's UID to Delete: ";
                        
                std::string uid;
                std::cin >> uid;

                playerManager.deletePlayer(uid);
            } else if (input == "5") {
                std::cout << "Reading players...\n"; 
                playerManager.listPlayers();
            } else if (input == "6") {
                tournament.runTournament(players);
            } else if (input == "7") {
                isInput = false;
                break;
            } else {
                std::cout << "\nUser input not registered! Please try again.\n";
            }
        }
    }

    void task3() {
        /**
         * This example demonstrates how to use the WithdrawalManager in a tournament setting.
         * It shows:
         * 1. Creating and managing reserve players
         * 2. Processing player withdrawals
         * 3. Finding replacements
         * 4. Updating the tournament schedule
         */
        using namespace TCMS;
        
        std::cout << "===== Asia Pacific University Tennis Championship =====\n";
        std::cout << "Player Withdrawal Management System Demonstration\n\n";
        
        // Create a withdrawal manager
        auto withdrawalManager = std::make_shared<WithdrawalManager>();
        auto matchScheduler = std::make_shared<MatchScheduler>();
        
        // Create a set of tournament players
        Vector<std::shared_ptr<Player>> tournamentPlayers;
        tournamentPlayers.pushBack(std::make_shared<Player>("Rafael Nadal", 95));
        tournamentPlayers.pushBack(std::make_shared<Player>("Roger Federer", 94));
        tournamentPlayers.pushBack(std::make_shared<Player>("Novak Djokovic", 96));
        tournamentPlayers.pushBack(std::make_shared<Player>("Andy Murray", 90));
        
        std::cout << "Tournament Players Initialized:\n";
        for (const auto& player : tournamentPlayers) {
            std::cout << "- " << player->getName() << " (Skill: " << player->getSkillLevel() << ")\n";
        }
        std::cout << "\n";
        
        // // Initialize reserve players
        std::cout << "Initializing reserve player list...\n";
        withdrawalManager->addReservePlayer(std::make_shared<Player>("Dominic Thiem", 85));
        withdrawalManager->addReservePlayer(std::make_shared<Player>("Alexander Zverev", 83));
        withdrawalManager->addReservePlayer(std::make_shared<Player>("Stefanos Tsitsipas", 82));
        
        // Show the initial reserve list
        withdrawalManager->displayReservePlayers();
        
        // Demonstrate a player withdrawal
        std::cout << "\nSimulating player withdrawal...\n";
        withdrawalManager->processWithdrawal(tournamentPlayers[1], "Knee injury"); // Federer withdraws
        
        // Show the updated withdrawal list
        withdrawalManager->displayWithdrawals();
        
        // Find a replacement and update the tournament
        std::cout << "\nFinding replacement and updating tournament...\n";
        auto replacement = withdrawalManager->findReplacement();
        if (replacement) {
            std::cout << "Replacement found: " << replacement->getName() << "\n";
            // In a real scenario, we would update the tournament brackets here
        }
        
        // Update the match schedule with the withdrawal manager
        withdrawalManager->updateSchedule(matchScheduler);
        
        // Show the updated reserve list
        withdrawalManager->displayReservePlayers();
        
        // Start the interactive user interface
        std::cout << "\nStarting interactive user interface...\n";
        withdrawalManager->handleUserInput();
        
        std::cout << "\nThank you for using the Player Withdrawal Management System.\n";
    }

    void task4()
    {
        auto task4_displayMenu = []{            
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
                << "6️⃣  Undo Last Match\n"
                << "7️⃣  Exit..\n"
                << "\033[0m"; // Reset color

            std::cout << "\033[1;34m==================================\033[0m\n"; // 🔵 Blue divider
            std::cout << "👉 Enter your choice: ";
        };

        MatchHistoryTracker historyTracker; // Object to manage match history
        int choice;
    
        do
        {
            task4_displayMenu(); // Function renamed everywhere it's called
            std::cin >> choice;
    
            if (std::cin.fail()) // Handle invalid input
            {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "\033[1;31m❌ Invalid choice! Please enter a number (1-7).\033[0m\n";
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
            else if (choice == 6) // Undo last match
            {
                historyTracker.undoLastMatch();
            }
            else if (choice == 7) // Exit the system
            {
                std::cout << "\033[1;32m✅ Exiting Match History Tracker...\033[0m\n";
            }
            else
            {
                std::cout << "\033[1;31m❌ Invalid choice! Please enter a number (1-7).\033[0m\n";
            }
    
        } while (choice != 7);
    }
} // namespace TCMS
