// WithdrawalManager.hpp
#pragma once

#include <string>
#include <memory>
#include <iostream>

#include "../DataStructures/Stack.hpp"
#include "../DataStructures/Queue.hpp"
#include "../models/Player.hpp"
#include "../controllers/MatchScheduler.hpp"
#include "../models/Match.hpp"

#include "../DataStructures/Vector.hpp"

namespace TCMS
{
    /**
     * @brief Manages player withdrawals during a tournament
     * 
     * This class handles the tracking and processing of player withdrawals,
     * finding suitable replacements, and updating the tournament schedule.
     * It uses a Stack to track withdrawals in LIFO order and a Queue to
     * manage reserve players.
     */
    class WithdrawalManager {
    public:
        WithdrawalManager();
        ~WithdrawalManager();
        
        /**
         * @brief Process a player withdrawal
         * 
         * @param player The player who is withdrawing
         * @param reason The reason for withdrawal
         */
        void processWithdrawal(std::shared_ptr<Player> player, const std::string& reason);
        
        /**
         * @brief Find a replacement for a withdrawn player
         * 
         * @return A replacement player from the reserve list, or nullptr if none available
         */
        std::shared_ptr<Player> findReplacement();
        
        /**
         * @brief Add a player to the reserve list
         * 
         * @param player The player to add to reserves
         */
        void addReservePlayer(std::shared_ptr<Player> player);
        
        /**
         * @brief Update the tournament schedule after withdrawals
         * 
         * @param scheduler The match scheduler to update
         */
        void updateSchedule(std::shared_ptr<MatchScheduler> scheduler);
        
        /**
         * @brief Display all withdrawn players
         */
        void displayWithdrawals();
        
        /**
         * @brief Display all reserve players
         */
        void displayReservePlayers();
        
        /**
         * @brief Interactive user interface for managing withdrawals
         */
        void handleUserInput();
        
        /**
         * @brief Check if a player has withdrawn
         * 
         * @param playerId The ID of the player to check
         * @return true if the player has withdrawn, false otherwise
         */
        bool hasPlayerWithdrawn(const std::string& playerId) const;
        
        /**
         * @brief Get the most recently withdrawn player
         * 
         * @return The most recent withdrawal, or nullptr if none
         */
        std::shared_ptr<Player> getLatestWithdrawal();

    private:
        // Stack to track player withdrawals (LIFO order)
        Stack<std::shared_ptr<Player>> m_WithdrawalStack;
        
        // Queue for reserve players who can replace withdrawn players
        Queue<std::shared_ptr<Player>> m_ReservePlayers;
        
        // Stack to track withdrawal reasons (matching the order of m_WithdrawalStack)
        Stack<std::string> m_WithdrawalReasons;
    };
} // namespace TCMS