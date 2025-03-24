#pragma once

#include <iostream>
#include <memory>

#include "../data_structures/Stack.hpp"

#include "../models/Player.hpp"
#include "../models/Match.hpp"

namespace TCMS {
    class KnockoutRound {
    public:
        // Constructor: Initializes the knockout round with a stack of players
        explicit KnockoutRound(std::shared_ptr<Stack<Players>> bracket) 
            : m_KnockoutPlayers(bracket) {} // Initialize the knockout players stack

        // Play the knockout matches
        void playKnockoutMatches() {
            std::cout << "\n--- Knockout Rounds Begin ---\n";

            // Continue until only one player remains
            while (m_KnockoutPlayers->getLength() > 1) {
                auto nextRoundStack = std::make_shared<Stack<Players>>(); // Stack for the next round

                // Process matches in the current round
                while (!m_KnockoutPlayers->isEmpty()) {
                    // Handle odd number of players (one player gets a bye)
                    if (m_KnockoutPlayers->getLength() == 1) {
                        auto byePlayer = m_KnockoutPlayers->pop(); // Player gets a bye
                        std::cout << byePlayer->getName() << " gets a bye!\n\n";
                        nextRoundStack->push(byePlayer); // Move the player to the next round
                        break;
                    }

                    // Pair up players for a match
                    auto p1 = m_KnockoutPlayers->pop(); // First player
                    auto p2 = m_KnockoutPlayers->pop(); // Second player

                    Match match(p1, p2); // Create a match
                    auto winner = match.playMatch(); // Play the match and get the winner
                    nextRoundStack->push(winner); // Move the winner to the next round
                }

                // Prepare for the next round
                m_KnockoutPlayers = nextRoundStack;
            }

            // Announce the champion
            std::cout << "\n🏆 Champion: " << m_KnockoutPlayers->peek()->getName() << " 🏆\n";
        }
    private:
        std::shared_ptr<Stack<Players>> m_KnockoutPlayers; // Stack of players in the knockout stage
    };
}
