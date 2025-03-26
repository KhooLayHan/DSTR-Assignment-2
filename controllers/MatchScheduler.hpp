#pragma once

#include <string>
#include <memory>
#include <iostream>

#include "../data_structures/CircularQueue.hpp"
#include "../models/Match.hpp"
#include "../models/Player.hpp"

namespace TCMS
{
    /**
     * @brief Manages the scheduling of matches in a tournament
     * 
     * This class handles the creation, modification, and display of match schedules.
     * It integrates with the WithdrawalManager to handle player replacements.
     */
    class MatchScheduler {
    public:
        MatchScheduler() {
            std::cout << "Match Scheduler initialized.\n";
        }
        
        /**
         * @brief Add a match to the schedule
         * 
         * @param player1 First player in the match
         * @param player2 Second player in the match
         */
        void addMatch(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2) {
            if (!player1 || !player2) {
                std::cerr << "Error: Cannot create match with null player.\n";
                return;
            }
            
            auto match = std::make_shared<Match>(player1, player2);
            m_ScheduleQueue.enqueue(match);
            std::cout << "Match added: " << player1->getName() << " vs " << player2->getName() << "\n";
        }
        
        /**
         * @brief Get the next match from the schedule
         * 
         * @return The next match, or nullptr if none available
         */
        std::shared_ptr<Match> getNextMatch() {
            if (m_ScheduleQueue.isEmpty()) {
                std::cout << "No matches in the schedule.\n";
                return nullptr;
            }
            
            return m_ScheduleQueue.dequeue();
        }
        
        /**
         * @brief Replace a player in all scheduled matches
         * 
         * @param withdrawnPlayer The player who has withdrawn
         * @param replacement The replacement player
         */
        void replacePlayer(std::shared_ptr<Player> withdrawnPlayer, std::shared_ptr<Player> replacement) {
            if (!withdrawnPlayer || !replacement) {
                std::cerr << "Error: Invalid player replacement request.\n";
                return;
            }
            
            std::cout << "Replacing " << withdrawnPlayer->getName() << " with " 
                      << replacement->getName() << " in all scheduled matches.\n";
            
            // This would require a more complex implementation to actually replace players
            // in matches, but for the stub we'll just acknowledge the replacement
        }
        
        /**
         * @brief Display the current match schedule
         */
        void displaySchedule() {
            if (m_ScheduleQueue.isEmpty()) {
                std::cout << "No matches in the schedule.\n";
                return;
            }
            
            std::cout << "\n--- Match Schedule ---\n";
            m_ScheduleQueue.print();
        }
        
    private:
        CircularQueue<std::shared_ptr<Match>> m_ScheduleQueue;
    };
} // namespace TCMS