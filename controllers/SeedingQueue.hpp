#pragma once

#include <iostream>
#include <memory>
#include "../data_structures/PriorityQueue.hpp"
#include "../models/Player.hpp"

namespace TCMS {
    class SeedingQueue {
    public:
        // Constructor: Initializes the seeding queue with advancing players
        explicit SeedingQueue(std::shared_ptr<PriorityQueue<Players>> advancingPlayers) 
            : m_SeedingQueue(std::make_shared<PriorityQueue<Players>>()), // Initialize seeding queue
              m_AdvancingPlayers(std::make_shared<PriorityQueue<Players>>()) { // Initialize advancing players queue
            // Move players from the input queue to the advancing players queue, ordered by skill level
            while (!advancingPlayers->isEmpty()) {
                m_AdvancingPlayers->enqueue(advancingPlayers->dequeue(), -advancingPlayers->peekFront()->getSkillLevel());
            }
        }

        // Print the seeding order of players
        void printSeedingOrder() const {
            std::cout << "\n--- Round-Robin Players in Seeding Order ---\n";
            // Iterate through the advancing players and print their names
            for (const auto& player : m_AdvancingPlayers->getElements()) {
                std::cout << player->getName() << "\n";
            }
        }

        // Get the seeding queue (priority queue of advancing players)
        std::shared_ptr<PriorityQueue<Players>> getSeedingQueue() {
            return m_AdvancingPlayers;
        }

        // Check if the seeding queue is empty
        bool isEmpty() const { 
            return m_AdvancingPlayers->isEmpty(); 
        }

    private:
        std::shared_ptr<PriorityQueue<Players>> m_SeedingQueue; // Seeding queue (not used in current implementation)
        std::shared_ptr<PriorityQueue<Players>> m_AdvancingPlayers; // Priority queue of advancing players
    };
}
