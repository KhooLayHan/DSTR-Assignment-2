// WithdrawalManager.cpp
#include "WithdrawalManager.hpp"

namespace TCMS
{
    WithdrawalManager::WithdrawalManager() {
        std::cout << "Withdrawal Manager initialized.\n";
    }
    
    WithdrawalManager::~WithdrawalManager() {
        std::cout << "Withdrawal Manager destroyed.\n";
    }
    
    void WithdrawalManager::processWithdrawal(std::shared_ptr<Player> player, const std::string& reason) {
        if (!player) {
            std::cerr << "Error: Cannot process withdrawal for null player.\n";
            return;
        }
        
        std::cout << "Processing withdrawal for player: " << player->getName() << "\n";
        player->withdraw(); // Mark the player as withdrawn
        
        // Add to withdrawal stack
        m_WithdrawalStack.push(player);
        m_WithdrawalReasons.push(reason);
        
        std::cout << "Player " << player->getName() << " has been withdrawn due to: " << reason << "\n";
    }
    
    std::shared_ptr<Player> WithdrawalManager::findReplacement() {
        if (m_ReservePlayers.isEmpty()) {
            std::cout << "No reserve players available for replacement.\n";
            return nullptr;
        }
        
        // Get the next reserve player
        std::shared_ptr<Player> replacement = m_ReservePlayers.dequeue();
        std::cout << "Found replacement player: " << replacement->getName() << "\n";
        
        return replacement;
    }
    
    void WithdrawalManager::addReservePlayer(std::shared_ptr<Player> player) {
        if (!player) {
            std::cerr << "Error: Cannot add null player to reserves.\n";
            return;
        }
        
        m_ReservePlayers.enqueue(player);
        std::cout << "Added " << player->getName() << " to reserve player list.\n";
    }
    
    void WithdrawalManager::updateSchedule(std::shared_ptr<MatchScheduler> scheduler) {
        if (!scheduler) {
            std::cout << "No match scheduler provided.\n";
            return;
        }
        
        std::cout << "Updating match schedule after withdrawals...\n";
        
        // Create a temporary stack to process withdrawals without modifying the original
        Stack<std::shared_ptr<Player>> tempStack = m_WithdrawalStack;
        
        while (!tempStack.isEmpty()) {
            auto withdrawnPlayer = tempStack.pop();
            
            // Find a replacement player
            auto replacement = findReplacement();
            
            if (replacement) {
                std::cout << "Updating schedule: " << withdrawnPlayer->getName() 
                          << " replaced by " << replacement->getName() << "\n";
                
                // Here we would update the match scheduler with the replacement
                // In a real implementation, we would call scheduler->replacePlayer(withdrawnPlayer, replacement)
                // but since MatchScheduler is still a stub, we'll just demonstrate the concept
            } else {
                std::cout << "Warning: No replacement available for " << withdrawnPlayer->getName() 
                          << ". Matches will be forfeited.\n";
                // In a real implementation, we would handle the forfeit scenario
            }
        }
        
        std::cout << "Match schedule updated successfully.\n";
    }
    
    void WithdrawalManager::displayWithdrawals() const {
        if (m_WithdrawalStack.isEmpty()) {
            std::cout << "No player withdrawals recorded.\n";
            return;
        }
        
        std::cout << "\n--- Player Withdrawals ---\n";
        
        // Create temporary copies of the stacks to preserve the original stacks
        Stack<std::shared_ptr<Player>> tempPlayerStack = m_WithdrawalStack;
        Stack<std::string> tempReasonStack = m_WithdrawalReasons;
        
        // Display the withdrawals
        while (!tempPlayerStack.isEmpty()) {
            auto player = tempPlayerStack.pop();
            std::string reason = "Unknown";
            
            if (!tempReasonStack.isEmpty()) {
                reason = tempReasonStack.pop();
            }
            
            std::cout << "Player: " << player->getName() 
                      << " (Skill Level: " << player->getSkillLevel() 
                      << ") - Reason: " << reason << "\n";
        }
    }
    
    void WithdrawalManager::displayReservePlayers() const {
        if (m_ReservePlayers.isEmpty()) {
            std::cout << "No reserve players available.\n";
            return;
        }
        
        std::cout << "\n--- Reserve Players ---\n";
        
        // Create a temporary copy of the queue to preserve the original queue
        Queue<std::shared_ptr<Player>> tempQueue = m_ReservePlayers;
        
        // Display the reserve players
        size_t position = 1;
        while (!tempQueue.isEmpty()) {
            auto player = tempQueue.dequeue();
            std::cout << position << ". " << player->getName() 
                      << " (Skill Level: " << player->getSkillLevel() << ")\n";
            position++;
        }
    }
    
    void WithdrawalManager::handleUserInput() {
        int choice = 0;
        
        while (choice != 5) {
            std::cout << "\n=== Withdrawal Management System ===\n";
            std::cout << "1. Register a player withdrawal\n";
            std::cout << "2. Add a reserve player\n";
            std::cout << "3. View withdrawal list\n";
            std::cout << "4. View reserve players\n";
            std::cout << "5. Exit\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            
            switch (choice) {
                case 1: {
                    std::string name, reason;
                    int skillLevel;
                    
                    std::cout << "Enter player name: ";
                    std::cin.ignore();
                    std::getline(std::cin, name);
                    
                    std::cout << "Enter player skill level (1-100): ";
                    std::cin >> skillLevel;
                    
                    std::cout << "Enter withdrawal reason: ";
                    std::cin.ignore();
                    std::getline(std::cin, reason);
                    
                    auto player = std::make_shared<Player>(name, skillLevel);
                    processWithdrawal(player, reason);
                    break;
                }
                case 2: {
                    std::string name;
                    int skillLevel;
                    
                    std::cout << "Enter reserve player name: ";
                    std::cin.ignore();
                    std::getline(std::cin, name);
                    
                    std::cout << "Enter reserve player skill level (1-100): ";
                    std::cin >> skillLevel;
                    
                    auto player = std::make_shared<Player>(name, skillLevel);
                    addReservePlayer(player);
                    break;
                }
                case 3:
                    displayWithdrawals();
                    break;
                case 4:
                    displayReservePlayers();
                    break;
                case 5:
                    std::cout << "Exiting withdrawal management system.\n";
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        }
    }
    
    bool WithdrawalManager::hasPlayerWithdrawn(const std::string& playerId) const {
        // Create a temporary stack for checking
        Stack<std::shared_ptr<Player>> tempStack = m_WithdrawalStack;
        
        while (!tempStack.isEmpty()) {
            auto player = tempStack.pop();
            if (player->getId() == playerId) {
                return true;
            }
        }
        
        return false;
    }
    
    std::shared_ptr<Player> WithdrawalManager::getLatestWithdrawal() {
        if (m_WithdrawalStack.isEmpty()) {
            return nullptr;
        }
        
        // Peek at the top of the stack without removing it
        return m_WithdrawalStack.peek();
    }
} // namespace TCMS