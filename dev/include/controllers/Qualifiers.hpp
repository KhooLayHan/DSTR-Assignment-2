// #pragma once

// #include <memory>
// #include "../models/Player.hpp"
// #include "../models/Match.hpp"
// #include "../data_structures/Queue.hpp"

// namespace TCMS
// {
//     class Qualifiers {
//     public:
//         Qualifiers(Queue<Players>& registeredPlayers, size_t qualifyingSpots)
//             :   m_AdvancingPlayers(std::make_shared<Queue<Players>>()), 
//                 m_QualifyingSpots(qualifyingSpots) {
//             while (!registeredPlayers.isEmpty()) {
//                 m_QualifierQueue.enqueue(registeredPlayers.dequeue());
//             }
//         }

//         ~Qualifiers() {
//             std::cout << "Qualifiers destructor called.\n";
//         }

//         void playQualifiers() {
//             std::cout << "\n--- Qualifiers Stage Begins ---\n";
            
//             Queue<Players> winnersQueue;

//             while (m_QualifierQueue.getLength() > 1) {
//                 Players p1 = m_QualifierQueue.dequeue();
//                 Players p2 = m_QualifierQueue.dequeue();
                
//                 if (!p1 || !p2) {
//                     throw std::runtime_error("Unexpected null player reference in qualifiers.");
//                 }

//                 Match match(p1, p2);
//                 auto winner = match.playMatch();
//                 winnersQueue.enqueue(winner);
//             }

//             if (!m_QualifierQueue.isEmpty()) {
//                 auto autoQualified = m_QualifierQueue.dequeue();
//                 std::cout << autoQualified->getName() << " automatically qualifies!\n";
//                 winnersQueue.enqueue(autoQualified);
//             }

//             while (!winnersQueue.isEmpty() && m_AdvancingPlayers->getLength() < m_QualifyingSpots) {
//                 m_AdvancingPlayers->enqueue(winnersQueue.dequeue());
//             }

//             std::cout << "\n--- Players Advancing to Round-Robin ---\n";
//             displayAdvancingPlayers();
//         }

//         std::shared_ptr<Queue<Players>> getAdvancingPlayers() {
//             return m_AdvancingPlayers;
//         }

//         void displayAdvancingPlayers() {
//             std::shared_ptr<Queue<Players>> tempQueue = std::make_shared<Queue<Players>>();;
//             // while (!tempQueue.isEmpty()) {
//             //     std::cout << tempQueue.dequeue()->getName() << "\n";
//             // }

//             // Create a safe iteration copy without modifying the original queue
//             // Queue<Players> copyQueue = m_AdvancingPlayers;
//             // while (!copyQueue.isEmpty()) {
//             //     auto player = copyQueue.dequeue();
//             //     std::cout << player->getName() << "\n";
//             //     tempQueue.enqueue(player);  // Restore dequeued elements
//             // }

//             // m_AdvancingPlayers = std::move(tempQueue);  // Restore original queue

//             // ✅ Safely iterate and restore queue
//             size_t originalLength = m_AdvancingPlayers->getLength();
//             for (size_t i = 0; i < originalLength; i++) {
//                 auto player = m_AdvancingPlayers->dequeue();
//                 std::cout << player->getName() << "\n";
//                 tempQueue->enqueue(player);
//             }

//             // ✅ Restore queue contents
//             // m_AdvancingPlayers = std::move(tempQueue);
//             m_AdvancingPlayers = tempQueue;
//         }

//     private:
//         Queue<Players> m_QualifierQueue;
        
//         std::shared_ptr<Queue<Players>> m_AdvancingPlayers;
//         size_t m_QualifyingSpots;
//     };
// } // namespace TCMS


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
        Qualifiers(Queue<Players>& registeredPlayers, size_t qualifyingSpots)
            : m_AdvancingPlayers(std::make_shared<PriorityQueue<Players>>()),
              m_QualifyingSpots(qualifyingSpots) {
            while (!registeredPlayers.isEmpty()) {
                m_QualifierQueue.enqueue(registeredPlayers.dequeue());
            }
        }

        void playQualifiers() {
            std::cout << "\n--- Qualifiers Stage Begins ---\n";
            Queue<Players> winnersQueue;

            while (m_QualifierQueue.getLength() > 1) {
                auto p1 = m_QualifierQueue.dequeue();
                auto p2 = m_QualifierQueue.dequeue();
                
                // m_QualifierQueue.

                Match match(p1, p2);
                auto winner = match.playMatch();
                winnersQueue.enqueue(winner);
            }

            while (!winnersQueue.isEmpty() && m_AdvancingPlayers->getLength() < m_QualifyingSpots) {
                auto player = winnersQueue.dequeue();
                m_AdvancingPlayers->enqueue(player, player->getSkillLevel());
            }

            std::cout << "\n--- Players Advancing to Round-Robin ---\n";
            displayAdvancingPlayers();
        }

        std::shared_ptr<PriorityQueue<Players>> getAdvancingPlayers() {
            return m_AdvancingPlayers;
        }

        void displayAdvancingPlayers() {
            // std::cout << "\n--- Players Advancing to Knockout ---\n";
            for (const auto& player : m_AdvancingPlayers->getElements()) {
                std::cout << player->getName() << "\n";
            }
            // std::vector<std::shared_ptr<Player>> tempList;

            // // Extract elements without modifying the original queue
            // auto tempQueue = *m_AdvancingPlayers;
            // while (!tempQueue.isEmpty()) {
            //     tempList.push_back(tempQueue.dequeue());
            // }
        
            // // // Print players
            // std::cout << "\n--- Players Advancing to Knockout ---\n";
            // for (const auto& player : tempList) {
            //     std::cout << player->getName() << "\n";
            // }

            // auto tempQueue = m_AdvancingPlayers->deepCopy(); // Uses deepCopy()

            // std::cout << "\n--- Players Advancing to Knockout ---\n";
            // while (!tempQueue.isEmpty()) {
            //     auto player = tempQueue.dequeue(); // Now owns a unique copy
            //     std::cout << player->getName() << "\n"; // No risk of accessing freed memory!
            // }
        }
    private:
        Queue<Players> m_QualifierQueue;
        std::shared_ptr<PriorityQueue<Players>> m_AdvancingPlayers;
        size_t m_QualifyingSpots;
    };
} // namespace TCMS

// #pragma once

// #include <iostream>
// #include "../models/Player.hpp"
// #include "../models/Match.hpp"
// #include "../data_structures/PriorityQueue.hpp"
// #include "../data_structures/Queue.hpp"

// namespace TCMS
// {
//     class Qualifiers {
//     public:
//         Qualifiers(Queue<Player*>& registeredPlayers, size_t qualifyingSpots)
//             : m_AdvancingPlayers(new PriorityQueue<Player*>()),
//               m_QualifyingSpots(qualifyingSpots) {
//             while (!registeredPlayers.isEmpty()) {
//                 m_QualifierQueue.enqueue(registeredPlayers.dequeue());
//             }
//         }

//         ~Qualifiers() {
//             // Clean up players in the qualifier queue
//             while (!m_QualifierQueue.isEmpty()) {
//                 delete m_QualifierQueue.dequeue();
//             }

//             // Clean up players in the advancing players queue
//             while (!m_AdvancingPlayers->isEmpty()) {
//                 delete m_AdvancingPlayers->dequeue();
//             }

//             // Delete the advancing players queue itself
//             delete m_AdvancingPlayers;
//         }

//         void playQualifiers() {
//             std::cout << "\n--- Qualifiers Stage Begins ---\n";
//             Queue<Player*> winnersQueue;

//             while (m_QualifierQueue.getLength() > 1) {
//                 auto p1 = m_QualifierQueue.dequeue();
//                 auto p2 = m_QualifierQueue.dequeue();
                
//                 Match match(p1, p2);
//                 auto winner = match.playMatch();
//                 winnersQueue.enqueue(winner);
//             }

//             while (!winnersQueue.isEmpty() && m_AdvancingPlayers->getLength() < m_QualifyingSpots) {
//                 auto player = winnersQueue.dequeue();
//                 m_AdvancingPlayers->enqueue(player, player->getSkillLevel());
//             }

//             std::cout << "\n--- Players Advancing to Round-Robin ---\n";
//             // displayAdvancingPlayers();
//         }

//         PriorityQueue<Player*>* getAdvancingPlayers() {
//             return m_AdvancingPlayers;
//         }

//         void displayAdvancingPlayers() {
//             // std::vector<Player*> tempList;

//             // // Extract elements without modifying the original queue
//             // auto tempQueue = *m_AdvancingPlayers;
//             // while (!tempQueue.isEmpty()) {
//             //     tempList.push_back(tempQueue.dequeue());
//             // }
        
//             // // Print players
//             // std::cout << "\n--- Players Advancing to Knockout ---\n";
//             // for (const auto& player : tempList) {
//             //     std::cout << player->getName() << "\n";
//             // }
//             // PriorityQueue<Player*> tempQueue = m_AdvancingPlayers->deepCopy();
//             // while (!tempQueue.isEmpty()) {
//             //     Player* player = tempQueue.dequeue();
//             //     std::cout << player->getName() << "\n";
//             // }

//             std::cout << "\n--- Players Advancing to Knockout ---\n";
//             for (const auto& player : m_AdvancingPlayers->getElements()) {
//                 std::cout << player->getName() << "\n";
//             }
//         }

//     private:
//         Queue<Player*> m_QualifierQueue;
//         PriorityQueue<Player*>* m_AdvancingPlayers; // Raw pointer to priority queue
//         size_t m_QualifyingSpots;
//     };
// } // namespace TCMS