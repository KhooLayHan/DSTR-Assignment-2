#pragma once

#include <memory>
#include "../models/Player.hpp"
#include "../models/Match.hpp"
#include "../DataStructures/Queue.hpp"

namespace TCMS
{
    class Qualifiers {
    public:
        Qualifiers(Queue<std::shared_ptr<Player>>& registeredPlayers, size_t qualifyingSpots)
            :   m_AdvancingPlayers(std::make_shared<Queue<std::shared_ptr<Player>>>()), 
                m_QualifyingSpots(qualifyingSpots) {
            while (!registeredPlayers.isEmpty()) {
                m_QualifierQueue.enqueue(registeredPlayers.dequeue());
            }
        }

        ~Qualifiers() {
            std::cout << "Qualifiers destructor called.\n";
        }

        void playQualifiers() {
            std::cout << "\n--- Qualifiers Stage Begins ---\n";
            
            Queue<std::shared_ptr<Player>> winnersQueue;

            while (m_QualifierQueue.getLength() > 1) {
                std::shared_ptr<Player> p1 = m_QualifierQueue.dequeue();
                std::shared_ptr<Player> p2 = m_QualifierQueue.dequeue();
                
                if (!p1 || !p2) {
                    throw std::runtime_error("Unexpected null player reference in qualifiers.");
                }

                Match match(p1, p2);
                auto winner = match.playMatch();
                winnersQueue.enqueue(winner);
            }

            if (!m_QualifierQueue.isEmpty()) {
                auto autoQualified = m_QualifierQueue.dequeue();
                std::cout << autoQualified->getName() << " automatically qualifies!\n";
                winnersQueue.enqueue(autoQualified);
            }

            while (!winnersQueue.isEmpty() && m_AdvancingPlayers->getLength() < m_QualifyingSpots) {
                m_AdvancingPlayers->enqueue(winnersQueue.dequeue());
            }

            std::cout << "\n--- Players Advancing to Round-Robin ---\n";
            displayAdvancingPlayers();
        }

        std::shared_ptr<Queue<std::shared_ptr<Player>>> getAdvancingPlayers() {
            return m_AdvancingPlayers;
        }

        void displayAdvancingPlayers() {
            std::shared_ptr<Queue<std::shared_ptr<Player>>> tempQueue = std::make_shared<Queue<std::shared_ptr<Player>>>();;
            // while (!tempQueue.isEmpty()) {
            //     std::cout << tempQueue.dequeue()->getName() << "\n";
            // }

            // Create a safe iteration copy without modifying the original queue
            // Queue<std::shared_ptr<Player>> copyQueue = m_AdvancingPlayers;
            // while (!copyQueue.isEmpty()) {
            //     auto player = copyQueue.dequeue();
            //     std::cout << player->getName() << "\n";
            //     tempQueue.enqueue(player);  // Restore dequeued elements
            // }

            // m_AdvancingPlayers = std::move(tempQueue);  // Restore original queue

            // ✅ Safely iterate and restore queue
            size_t originalLength = m_AdvancingPlayers->getLength();
            for (size_t i = 0; i < originalLength; i++) {
                auto player = m_AdvancingPlayers->dequeue();
                std::cout << player->getName() << "\n";
                tempQueue->enqueue(player);
            }

            // ✅ Restore queue contents
            // m_AdvancingPlayers = std::move(tempQueue);
            m_AdvancingPlayers = tempQueue;
        }

    private:
        Queue<std::shared_ptr<Player>> m_QualifierQueue;
        
        std::shared_ptr<Queue<std::shared_ptr<Player>>> m_AdvancingPlayers;
        size_t m_QualifyingSpots;
    };
} // namespace TCMS


// #pragma once

// #include "../models/Player.hpp"
// #include "../models/Match.hpp"

// #include "../data_structures/Queue.hpp"

// namespace TCMS
// {
//     class Qualifiers {
//     public:
//         Qualifiers(Queue<Player>& registeredPlayers, size_t qualifyingSpots) 
//             : m_QualifyingSpots(qualifyingSpots) {
//             while (!registeredPlayers.isEmpty()) {
//                 m_QualifierQueue.enqueue(registeredPlayers.dequeue());
//             }
//         }

//         void playQualifiers() {
//             std::cout << "\n--- Qualifiers Stage Begins ---\n";
            
//             Queue<Player> winnersQueue;

//             while (m_QualifierQueue.getLength() != 0) {
//                 Player p1 = m_QualifierQueue.dequeue();
//                 Player p2 = m_QualifierQueue.dequeue();
                
//                 Match match(p1, p2);
//                 Player winner = match.playMatch();

//                 winnersQueue.enqueue(winner);
//             }

//             // If odd player remains, they automatically qualify
//             if (!m_QualifierQueue.isEmpty()) {
//                 Player autoQualified = m_QualifierQueue.dequeue();
//                 std::cout << autoQualified.getName() << " automatically qualifies!\n";
//                 winnersQueue.enqueue(autoQualified);
//             }

//             // Limit advancing players to the qualifying spots
//             while (!winnersQueue.isEmpty() && m_AdvancingPlayers.getLength() < m_QualifyingSpots) {
//                 m_AdvancingPlayers.enqueue(winnersQueue.dequeue());
//             }

//             std::cout << "\n--- Players Advancing to Round-Robin ---\n";
//             displayAdvancingPlayers();
//         }

//         Queue<Player>& getAdvancingPlayers() {
//             return m_AdvancingPlayers;
//         }

//         void displayAdvancingPlayers() {
//             Queue<Player> tempQueue = m_AdvancingPlayers;
//             while (!tempQueue.isEmpty()) {
//                 std::cout << tempQueue.dequeue().getName() << "\n";
//             }
//         }

//     private:
//         Queue<Player> m_QualifierQueue;
//         Queue<Player> m_AdvancingPlayers;
//         size_t m_QualifyingSpots;
//     };
// } // namespace TCMS
