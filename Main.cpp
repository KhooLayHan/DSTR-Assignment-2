#include <iostream>
#include <memory>
#include "./data_structures/Vector.hpp"

#include "models/Player.hpp"
#include "controllers/WithdrawalManager.hpp"
#include "controllers/MatchScheduler.hpp"

/**
 * This example demonstrates how to use the WithdrawalManager in a tournament setting.
 * It shows:
 * 1. Creating and managing reserve players
 * 2. Processing player withdrawals
 * 3. Finding replacements
 * 4. Updating the tournament schedule
 */
int main() {
    using namespace TCMS;
    
    std::cout << "===== Asia Pacific University Tennis Championship =====\n";
    std::cout << "Player Withdrawal Management System Demonstration\n\n";
    
    // Create a withdrawal manager
    auto withdrawalManager = std::make_shared<WithdrawalManager>();
    auto matchScheduler = std::make_shared<MatchScheduler>();
    
    // Create a set of tournament players
    std::vector<std::shared_ptr<Player>> tournamentPlayers;
    tournamentPlayers.push_back(std::make_shared<Player>("Rafael Nadal", 95));
    tournamentPlayers.push_back(std::make_shared<Player>("Roger Federer", 94));
    tournamentPlayers.push_back(std::make_shared<Player>("Novak Djokovic", 96));
    tournamentPlayers.push_back(std::make_shared<Player>("Andy Murray", 90));
    
    std::cout << "Tournament Players Initialized:\n";
    for (const auto& player : tournamentPlayers) {
        std::cout << "- " << player->getName() << " (Skill: " << player->getSkillLevel() << ")\n";
    }
    std::cout << "\n";
    
    // Initialize reserve players
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
    
    return 0;
}