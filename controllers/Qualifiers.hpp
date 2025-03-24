#pragma once

#include <memory>
#include "../models/Player.hpp"
#include "../models/Match.hpp"
#include "../data_structures/PriorityQueue.hpp"
#include "../data_structures/Queue.hpp"

namespace TCMS
{
    class Qualifiers {
    public:
        // Constructor: Initializes the qualifiers with registered players and the number of qualifying spots
        Qualifiers(Queue<Players>& registeredPlayers, size_t qualifyingSpots)
            : m_AdvancingPlayers(std::make_shared<PriorityQueue<Players>>()), // Initialize advancing players as a priority queue
              m_QualifyingSpots(qualifyingSpots) { // Set the number of qualifying spots
            // Move all registered players into the qualifier queue
            while (!registeredPlayers.isEmpty()) {
                m_QualifierQueue.enqueue(registeredPlayers.dequeue());
            }
        }

        // Play the qualifiers stage
        void playQualifiers() {
            std::cout << "\n--- Qualifiers Stage Begins ---\n";
            Queue<Players> winnersQueue; // Queue to store winners of each match

            // Play matches until there are fewer than 2 players left in the qualifier queue
            while (m_QualifierQueue.getLength() > 1) {
                auto p1 = m_QualifierQueue.dequeue(); // Dequeue the first player
                auto p2 = m_QualifierQueue.dequeue(); // Dequeue the second player

                Match match(p1, p2); // Create a match between the two players
                auto winner = match.playMatch(); // Play the match and get the winner
                winnersQueue.enqueue(winner); // Enqueue the winner
            }

            // Add winners to the advancing players queue until the qualifying spots are filled
            while (!winnersQueue.isEmpty() && m_AdvancingPlayers->getLength() < m_QualifyingSpots) {
                auto player = winnersQueue.dequeue(); // Dequeue a winner
                m_AdvancingPlayers->enqueue(player, player->getSkillLevel()); // Enqueue with priority based on skill level
            }

            // Display the list of advancing players
            std::cout << "\n--- Players Advancing to Round-Robin ---\n";
            displayAdvancingPlayers();
        }

        // Get the list of advancing players
        std::shared_ptr<PriorityQueue<Players>> getAdvancingPlayers() {
            return m_AdvancingPlayers;
        }

        // Display the list of advancing players
        void displayAdvancingPlayers() {
            // Iterate through the advancing players and print their names
            for (const auto& player : m_AdvancingPlayers->getElements()) {
                std::cout << player->getName() << "\n";
            }
        }

    private:
        Queue<Players> m_QualifierQueue; // Queue of players participating in qualifiers
        std::shared_ptr<PriorityQueue<Players>> m_AdvancingPlayers; // Priority queue of advancing players
        size_t m_QualifyingSpots; // Number of players that qualify for the next stage
    };
} // namespace TCMS
