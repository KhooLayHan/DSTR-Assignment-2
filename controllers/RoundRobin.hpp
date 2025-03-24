#pragma once

#include <iostream>
#include <memory>

#include "../data_structures/CircularQueue.hpp"
#include "../data_structures/PriorityQueue.hpp"
#include "../models/Player.hpp"
#include "../models/Match.hpp"
#include "../data_structures/hash_map/HashMap.hpp"

namespace TCMS {
    class RoundRobin {
    public:
        // Constructor: Initializes the RoundRobin with a queue of seeded players
        RoundRobin(std::shared_ptr<PriorityQueue<Players>> seededPlayers)
            : m_AdvancingPlayers(std::make_shared<PriorityQueue<Players>>()) {
            // Move players from the seeded queue to the round-robin queue
            while (!seededPlayers->isEmpty()) {
                m_PlayerQueue.enqueue(seededPlayers->dequeue());
            }
        }

        // Play round-robin matches between all players
        void playGroupMatches() {
            std::cout << "\n--- Round Robin Matches ---\n";

            size_t numPlayers = m_PlayerQueue.getLength();
            if (numPlayers < 2) {
                std::cerr << "Error: Not enough players to start a round-robin tournament.\n";
                return;
            }

            // Use a vector to store players for rotation
            Vector<std::shared_ptr<Player>> players;
            while (!m_PlayerQueue.isEmpty()) {
                players.pushBack(m_PlayerQueue.dequeue());
            }

            // Play matches between all pairs of players
            for (size_t i = 0; i < numPlayers - 1; i++) {
                auto player1 = players[i];

                for (size_t j = i + 1; j < numPlayers; j++) {
                    auto player2 = players[j];

                    // Simulate the match
                    Match match(player1, player2);
                    auto winner = match.playMatch();

                    if (winner) {
                        // Update match wins and total points for the winner
                        if (m_MatchWins.find(winner->getUUID())) {
                            m_MatchWins[winner->getUUID()]++;
                        } else {
                            m_MatchWins.insert(winner->getUUID(), 1);
                        }

                        if (m_TotalPoints.find(winner->getUUID())) {
                            m_TotalPoints[winner->getUUID()] += winner->getSkillLevel() + winner->getPoints();
                        } else {
                            m_TotalPoints.insert(winner->getUUID(), winner->getSkillLevel() + winner->getPoints());
                        }

                        // Add the winner to the advancing players queue and map if not already present
                        if (!m_AdvancingPlayersMap.find(winner->getUUID())) {
                            m_AdvancingPlayers->enqueue(winner, winner->getSkillLevel());
                            m_AdvancingPlayersMap.insert(winner->getUUID(), winner);
                        }
                    }
                }
            }
        }

        // Determine and display the winners advancing to the next stage
        void determineWinners() {
            std::cout << "\n--- Players Advancing to Knockout ---\n";
            for (const auto& player : m_AdvancingPlayers->getElements()) {
                std::cout << player->getName() << "\n";
            }
        }

        // Get the queue of advancing players
        std::shared_ptr<PriorityQueue<Players>> getAdvancingPlayers() {
            return m_AdvancingPlayers;
        }

    private:
        CircularQueue<Players> m_PlayerQueue; // Queue of players for round-robin matches
        std::shared_ptr<PriorityQueue<Players>> m_AdvancingPlayers; // Priority queue of advancing players

        // Custom HashMaps for tracking match wins, total points, and advancing players
        HashMap<std::string, int32_t> m_MatchWins; // Player UUID -> Total Win Count
        HashMap<std::string, int32_t> m_TotalPoints; // Player UUID -> Total Points
        HashMap<std::string, Players> m_AdvancingPlayersMap; // Player UUID -> Player object
    };
}