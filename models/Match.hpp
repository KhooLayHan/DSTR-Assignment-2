#pragma once

#include <iostream>
#include <memory>  // For shared_ptr
#include "./Player.hpp"

namespace TCMS
{
    class Match {
    public:
        // Constructor: Initializes a match between two players
        Match(std::shared_ptr<Player> player_1, std::shared_ptr<Player> player_2)
            : m_Player_1(player_1), m_Player_2(player_2) {}

        // Simulates the match and determines the winner based on skill level
        std::shared_ptr<Player> playMatch() {
            // Player 1 wins if their skill level is higher
            if (m_Player_1->getSkillLevel() > m_Player_2->getSkillLevel()) {
                m_Player_1->addWin(); // Increment Player 1's win count
                
                std::cout << m_Player_1->getName() << " vs " << m_Player_2->getName()
                          << " -> Winner: " << m_Player_1->getName() << "\n";
                return m_Player_1; // Return Player 1 as the winner
            } 
            // Player 2 wins if their skill level is higher
            else if (m_Player_2->getSkillLevel() > m_Player_1->getSkillLevel()) {
                m_Player_2->addWin(); // Increment Player 2's win count
                
                std::cout << m_Player_1->getName() << " vs " << m_Player_2->getName()
                          << " -> Winner: " << m_Player_2->getName() << "\n";
                return m_Player_2; // Return Player 2 as the winner
            }

            // If skill levels are equal, the match is a draw
            std::cout << m_Player_1->getName() << " vs " << m_Player_2->getName()
                      << " -> No Winner (Draw)\n";
            return nullptr; // No winner
        }

        // Getters for integration with MatchRecord / Tracker
        std::shared_ptr<Player> getPlayer1() const { return m_Player_1; }
        std::shared_ptr<Player> getPlayer2() const { return m_Player_2; }

    private:
        std::shared_ptr<Player> m_Player_1; // First player in the match
        std::shared_ptr<Player> m_Player_2; // Second player in the match
    };
} // namespace TCMS