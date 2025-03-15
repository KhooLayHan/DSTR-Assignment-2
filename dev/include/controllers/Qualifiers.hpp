#pragma once

#include <memory>
#include "../models/Player.hpp"
#include "../models/Match.hpp"
#include "../data_structures/Queue.hpp"

namespace TCMS
{
    class Qualifiers {
    public:
        Qualifiers(Queue<std::shared_ptr<Player>>& registeredPlayers, size_t qualifyingSpots)
            : m_QualifyingSpots(qualifyingSpots) {
            while (!registeredPlayers.isEmpty()) {
                m_QualifierQueue.enqueue(registeredPlayers.dequeue());
            }
        }

        void playQualifiers() {
            std::cout << "\n--- Qualifiers Stage Begins ---\n";
            
            Queue<std::shared_ptr<Player>> winnersQueue;

            while (m_QualifierQueue.getLength() > 1) {
                auto p1 = m_QualifierQueue.dequeue();
                auto p2 = m_QualifierQueue.dequeue();
                
                Match match(p1, p2);
                auto winner = match.playMatch();
                winnersQueue.enqueue(winner);
            }

            if (!m_QualifierQueue.isEmpty()) {
                auto autoQualified = m_QualifierQueue.dequeue();
                std::cout << autoQualified->getName() << " automatically qualifies!\n";
                winnersQueue.enqueue(autoQualified);
            }

            while (!winnersQueue.isEmpty() && m_AdvancingPlayers.getLength() < m_QualifyingSpots) {
                m_AdvancingPlayers.enqueue(winnersQueue.dequeue());
            }

            std::cout << "\n--- Players Advancing to Round-Robin ---\n";
            displayAdvancingPlayers();
        }

        Queue<std::shared_ptr<Player>>& getAdvancingPlayers() {
            return m_AdvancingPlayers;
        }

        void displayAdvancingPlayers() {
            Queue<std::shared_ptr<Player>> tempQueue = m_AdvancingPlayers;
            while (!tempQueue.isEmpty()) {
                std::cout << tempQueue.dequeue()->getName() << "\n";
            }
        }

    private:
        Queue<std::shared_ptr<Player>> m_QualifierQueue;
        Queue<std::shared_ptr<Player>> m_AdvancingPlayers;
        size_t m_QualifyingSpots;
    };
} // namespace TCMS
