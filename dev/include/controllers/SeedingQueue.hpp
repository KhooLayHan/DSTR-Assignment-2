#pragma once

#include <iostream>
#include <memory>
#include "../data_structures/PriorityQueue.hpp"
#include "../models/Player.hpp"

namespace TCMS {
    class SeedingQueue {
    public:
        explicit SeedingQueue(std::shared_ptr<PriorityQueue<Players>> advancingPlayers) : 
            m_SeedingQueue(std::make_shared<PriorityQueue<Players>>()), m_AdvancingPlayers(std::make_shared<PriorityQueue<Players>>()) {
            while (!advancingPlayers->isEmpty()) {
                // auto player = m_AdvancingPlayers->peekFront();  // ✅ Peek first
                // m_SeedingQueue->enqueue(advancingPlayers->dequeue(), -advancingPlayers->peekFront()->getSkillLevel());
                m_AdvancingPlayers->enqueue(advancingPlayers->dequeue(), -advancingPlayers->peekFront()->getSkillLevel());
            }
        }

        void printSeedingOrder() const {
            std::cout << "\nSeeding Order: \n";
            // m_SeedingQueue->print();

            // auto tempQueue = m_AdvancingPlayers;
            // while (!tempQueue->isEmpty()) {
            //     std::cout << tempQueue->dequeue()->getName() << "\n";
            // }

            for (const auto& player : m_AdvancingPlayers->getElements()) {
                std::cout << player->getName() << "\n";
            }
        }

        std::shared_ptr<PriorityQueue<Players>> getSeedingQueue() {
            return m_AdvancingPlayers;
        }

        bool isEmpty() const { return m_AdvancingPlayers->isEmpty(); }
        

    private:
        std::shared_ptr<PriorityQueue<Players>> m_SeedingQueue;
        std::shared_ptr<PriorityQueue<Players>> m_AdvancingPlayers;
    };
}