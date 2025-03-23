// #pragma once

// #include <algorithm>
// #include <memory>  // For smart pointers
// #include <unordered_map>

// #include "../data_structures/Queue.hpp"
// #include "../data_structures/PriorityQueue.hpp"
// #include "../data_structures/Vector.hpp"

// #include "../models/Player.hpp"
// #include "../models/Match.hpp"

// #include "../algorithms/Sort.hpp"

// #include <cmath>

// namespace TCMS
// {
//     class RoundRobin {
//     public:
//         RoundRobin(Vector<std::shared_ptr<Player>>& players, int32_t groupSize)
//             :   m_AdvancingPlayers(std::make_shared<Queue<std::shared_ptr<Player>>>()) {   
//             PriorityQueue<std::shared_ptr<Player>> rankingQueue;

//             // Enqueue players based on ranking (higher skill = higher priority)
//             for (const auto& player : players) {
//                 rankingQueue.enqueue(player, player->getSkillLevel());
//             }
            
//             // Divide sorted players into groups
//             size_t groupsCount = ceil(players.getLength() / groupSize);
//             m_Groups.reserve(groupsCount);

//             size_t groupIndex = 0;
//             while (!rankingQueue.isEmpty()) {
//                 m_Groups[groupIndex % groupsCount].emplaceBack(rankingQueue.dequeue());
//                 groupIndex++;
//             }
//         }   
//         // RoundRobin(Vector<std::shared_ptr<Player>>& players, int32_t groupSize) {   
//         //     PriorityQueue<std::shared_ptr<Player>> rankingQueue;

//         //     // Enqueue players based on ranking (higher skill = higher priority)
//         //     for (const auto& player : players) {
//         //         rankingQueue.enqueue(player, player->getSkillLevel());
//         //     }
            
//         //     // Divide sorted players into groups
//         //     size_t groupsCount = ceil(players.getLength() / groupSize);
//         //     m_Groups.reserve(groupsCount);

//         //     size_t groupIndex = 0;
//         //     while (!rankingQueue.isEmpty()) {
//         //         m_Groups[groupIndex % groupsCount].emplaceBack(rankingQueue.dequeue());
//         //         groupIndex++;
//         //     }
//         // }   

//         void playGroupMatches() {
//             std::cout << "\n--- Round Robin Group Matches ---\n";
            
//             for (auto& group : m_Groups) {
//                 for (size_t i = 0; i < group.getLength(); i++) {
//                     for (size_t j = 0; j < group.getLength(); j++) {
//                         if (i == j) continue;  // Prevent a player from playing themselves

//                         Match match(group[i], group[j]);
//                         auto winner = match.playMatch();

//                         if (winner) {
//                             m_MatchWins[winner->getId()]++;  // Track number of wins
//                             m_TotalPoints[winner->getId()] += winner->getSkillLevel() + winner->getPoints();  // Track points
//                         }
//                     }                        
//                 }
//             }
//         }

//         void determineWinners() {
//             std::cout << "\n--- Advancing Players ---\n";

//             for (auto& group : m_Groups) {            
//                 // std::cout << group[0]->getName() << "\n";
//                 // std::cout << group[1]->getName() << "\n";
//                 // std::cout << group[2]->getName() << "\n";
//                 // std::cout << group[3]->getName() << "\n";

//                 // std::cout << m_MatchWins[group[0]->getId()] << "\n";
//                 // std::cout << m_MatchWins[group[1]->getId()] << "\n";
//                 // std::cout << m_MatchWins[group[2]->getId()] << "\n";
//                 // std::cout << m_MatchWins[group[3]->getId()] << "\n";

//                 auto firstPlayer = group[group.getLength() - 1];  // First best player
//                 auto secondPlayer = group[group.getLength() - 2];  // Second best player

//                 if (m_MatchWins[firstPlayer->getId()] == m_MatchWins[secondPlayer->getId()]) {
//                     auto tiebreakerWinner = applyTieBreaker(firstPlayer, secondPlayer);
//                     m_AdvancingPlayers->enqueue(tiebreakerWinner);
//                 } else {
//                     m_AdvancingPlayers->enqueue(firstPlayer);  // First best player
//                     m_AdvancingPlayers->enqueue(secondPlayer);  // Second best player
//                 }
//             }
//         }

//         std::shared_ptr<Player> applyTieBreaker(std::shared_ptr<Player>& firstPlayer, std::shared_ptr<Player>& secondPlayer) {
//             if (m_TotalPoints[firstPlayer->getId()] > m_TotalPoints[secondPlayer->getId()]) {
//                 return firstPlayer;
//             } else if (m_TotalPoints[secondPlayer->getId()] > m_TotalPoints[firstPlayer->getId()]) {
//                 return secondPlayer;
//             } else {
//                 return (firstPlayer->getSkillLevel() > secondPlayer->getSkillLevel()) ? firstPlayer : secondPlayer;
//             }
//         }

//         std::shared_ptr<Queue<std::shared_ptr<Player>>> getAdvancingPlayers() {
//             return m_AdvancingPlayers;
//         }

//     private:
//         Vector<Vector<std::shared_ptr<Player>>> m_Groups;
//         // Queue<std::shared_ptr<Player>> m_AdvancingPlayers;
//         std::shared_ptr<Queue<std::shared_ptr<Player>>> m_AdvancingPlayers;

//         std::unordered_map<std::string, int32_t> m_MatchWins;  // Player Id -> Total Win Count
//         std::unordered_map<std::string, int32_t> m_TotalPoints;  // Player Id -> Total Points
//     };
// } // namespace TCMS

#pragma once

#include <iostream>
#include <memory>
#include "../data_structures/CircularQueue.hpp"
#include "../data_structures/PriorityQueue.hpp"
#include "../models/Player.hpp"
#include "../models/Match.hpp"

#include <unordered_map>

#include "../data_structures/hash_map/HashMap.hpp"

namespace TCMS {
    class RoundRobin {
    public:
        RoundRobin(std::shared_ptr<PriorityQueue<Players>> seededPlayers) :
            // m_PlayerQueue(std::make_shared<CircularQueue<Players>>()), 
            m_AdvancingPlayers(std::make_shared<PriorityQueue<Players>>()) {   
            while (!seededPlayers->isEmpty()) {
                m_PlayerQueue.enqueue(seededPlayers->dequeue());
            }

            // To avoid circular references 
            // m_SeededPlayers = seededPlayers;
        }

        // explicit RoundRobin(std::shared_ptr<CircularQueue<Players>> roundRobinQueue)
        //     : m_PlayerQueue(roundRobinQueue),  // ✅ Receive Pre-Built Queue
        //       m_AdvancingPlayers(std::make_shared<PriorityQueue<Players>>()) {

        //       }


        // void playGroupMatches() {
        //     std::cout << "\n--- Round Robin Matches ---\n";
        //     size_t matchCount = m_PlayerQueue->getLength();

        //     for (size_t i = 0; i < matchCount; i++) {
        //         auto player1 = m_PlayerQueue->dequeue();
        //         auto player2 = m_PlayerQueue->peekFront(); // Next player in queue

        //         Match match(player1, player2);
        //         auto winner = match.playMatch();

        //         if (winner) {

        //             m_MatchWins[winner->getId()]++;
        //             m_TotalPoints[winner->getId()] += winner->getSkillLevel() + winner->getPoints();
                    
        //             m_AdvancingPlayers->enqueue(winner, winner->getSkillLevel());
        //         }

        //         m_PlayerQueue->enqueue(player1);  // Rotate players
        //     }
        // }

        void playGroupMatches() {
            std::cout << "\n--- Round Robin Matches ---\n";

            // size_t numPlayers = m_PlayerQueue.getLength();
            // auto tempQueue = m_PlayerQueue;  // Copy to avoid modifying original queue

            // // CircularQueue<Players> winnerQueue;

            // for (size_t i = 0; i < numPlayers - 1; i++) {  // Each player gets to play
            //     auto player1 = m_PlayerQueue.dequeue();
                
            //     // Match player1 with remaining players in queue
            //     size_t matches = numPlayers - i - 1;  // Prevent duplicate matchups
            //     for (size_t j = 0; j < matches; j++) {
            //         auto player2 = m_PlayerQueue.dequeue();
            //         // auto player2 = tempQueue.peekFront();
                    
            //         Match match(player1, player2);
            //         auto winner = match.playMatch();

            //         if (winner) {
            //             m_MatchWins[winner->getUUID()]++;
            //             m_TotalPoints[winner->getUUID()] += winner->getSkillLevel() + winner->getPoints();

            //             if (!m_AdvancingPlayersMap.count(winner->getUUID())) {
            //                 m_AdvancingPlayers->enqueue(winner, winner->getSkillLevel());
            //                 m_AdvancingPlayersMap[winner->getUUID()] = winner;
            //             }
            //         }
                    
            //         tempQueue.enqueue(player2);  // Rotate players back in queue
            //     }

            //     tempQueue.enqueue(player1);  // Ensure round-robin rotation
            // }

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
        
            for (size_t i = 0; i < numPlayers - 1; i++) {  // Each player gets to play
                auto player1 = players[i];
        
                // Match player1 with remaining players
                for (size_t j = i + 1; j < numPlayers; j++) {
                    auto player2 = players[j];
        
                    // Simulate the match
                    Match match(player1, player2);
                    auto winner = match.playMatch();
        
                    if (winner) {
                        // Update match wins and total points for the winner
                        m_MatchWins[winner->getUUID()]++;
                        m_TotalPoints[winner->getUUID()] += winner->getSkillLevel() + winner->getPoints();
        
                        // Add the winner to the advancing players queue and map
                        if (!m_AdvancingPlayersMap.count(winner->getUUID())) {
                            m_AdvancingPlayers->enqueue(winner, winner->getSkillLevel());
                            m_AdvancingPlayersMap[winner->getUUID()] = winner;
                        }
                    }
                }
            }
        
            // // Restore the original queue
            // for (const auto& player : players) {
            //     m_PlayerQueue.enqueue(player);
            // }
        
            // std::cout << "Round-robin matches completed.\n";
        }

        // void playGroupMatches() {
        //     std::cout << "\n--- Round Robin Matches ---\n";
        //     size_t matchCount = m_PlayerList.getLength();

        //     std::unordered_map<std::string, std::unordered_map<std::string, bool>> playedMatches;

        //     for (size_t i = 0; i < matchCount; i++) {
        //         for (size_t j = i + 1; j < matchCount; j++) {
        //             auto player1 = m_PlayerList[i];
        //             auto player2 = m_PlayerList[j];

                    // ✅ Check if this match was already played
        //             if (playedMatches[player1->getId()][player2->getId()] ||
        //                 playedMatches[player2->getId()][player1->getId()]) {
        //                 continue;
        //             }

        //             playedMatches[player1->getId()][player2->getId()] = true;
        //             playedMatches[player2->getId()][player1->getId()] = true;

        //             Match match(player1, player2);
        //             auto winner = match.playMatch();

        //             if (winner) {
        //                 m_MatchWins[winner->getId()]++;
        //                 m_TotalPoints[winner->getId()] += winner->getSkillLevel() + winner->getPoints();

        //                 // ✅ Avoid duplicate enqueue
        //                 if (m_AdvancingPlayersMap.find(winner->getId()) == m_AdvancingPlayersMap.end()) {
        //                     m_AdvancingPlayers->enqueue(winner, winner->getSkillLevel());
        //                     m_AdvancingPlayersMap[winner->getId()] = winner;
        //                 }
        //             }
        //         }
        //     }
        // }

        void determineWinners() {
            // std::cout << "\n--- Players Advancing to Knockout ---\n";

            // auto tempQueue = m_AdvancingPlayers;
            // while (!tempQueue->isEmpty()) {
            //     std::cout << tempQueue->dequeue()->getName() << "\n";
            // }

            std::cout << "\n--- Players Advancing to Knockout ---\n";
            for (const auto& player : m_AdvancingPlayers->getElements()) {
                std::cout << player->getName() << "\n";
            }
        }

        std::shared_ptr<PriorityQueue<Players>> getAdvancingPlayers() {
            return m_AdvancingPlayers;
        }

    private:
        // std::shared_ptr<CircularQueue<Players>> m_PlayerQueue;

        CircularQueue<Players> m_PlayerQueue;
        // std::shared_ptr<CircularQueue<Players>> m_PlayerQueue;
        std::shared_ptr<PriorityQueue<Players>> m_AdvancingPlayers;

        // HashMap<std::string, int32_t> m_MatchWins;  // Player Id -> Total Win Count
        // HashMap<std::string, int32_t> m_TotalPoints;  // Player Id -> Total Points
        // HashMap<std::string, Players> m_AdvancingPlayersMap;  // ✅ To track unique advancing players
        std::unordered_map<std::string, int32_t> m_MatchWins;  // Player Id -> Total Win Count
        std::unordered_map<std::string, int32_t> m_TotalPoints;  // Player Id -> Total Points
        std::unordered_map<std::string, Players> m_AdvancingPlayersMap;  // ✅ To track unique advancing players
        // Using std::weak_ptr to avoid circular dependencies
        // std::weak_ptr<PriorityQueue<Players>> m_SeededPlayers;
    };
}



// #pragma once

// #include <algorithm>

// #include "../data_structures/Queue.hpp"
// #include "../data_structures/PriorityQueue.hpp"
// #include "../data_structures/Vector.hpp"

// #include "../models/Player.hpp"
// #include "../models/Match.hpp"

// #include "../algorithms/Sort.hpp"

// #include <unordered_map>

// namespace TCMS
// {
//     class RoundRobin {
//     public:
//         RoundRobin(Vector<Player>& players, int32_t groupSize) {   
//             PriorityQueue<Player> rankingQueue;

//             // Enqueue players based on ranking (higher skill = higher priority)
//             for (const auto& player : players) {
//                 rankingQueue.enqueue(player, player.getSkillLevel());
//             }
            
//             // Divide sorted players into groups 
//             size_t groupsCount = players.getLength() / groupSize;
//             m_Groups.reserve(groupsCount);

//             size_t groupIndex = 0;
//             while (!rankingQueue.isEmpty()) {
//                 m_Groups[groupIndex % groupsCount].emplaceBack(rankingQueue.dequeue());
//                 groupIndex++;
//             }

//             // for (size_t i = 0; i != players.getLength(); i++) {
//             //     m_Groups[i % groupsCount].emplaceBack(players[i]);
//             // }
//         }   

//         void playGroupMatches() {
//             std::cout << "\n--- Round Robin Group Matches ---\n";
            
//             for (auto& group : m_Groups) {

                // for (size_t i = 0; i != m_Groups.getLength(); i++) {
                //     for (size_t j = 0; j != m_Groups.getLength(); j++) {
                //         Player& player_1 = group[i];
                //         Player& player_2 = group[i];

                //         // Simulate match based on ranking
                //         if (player_1 > player_2) {
                //             player_1.addWin();
                //             std::cout << player_1.getName() << " defeats " << player_2.getName() << "\n";  
                //         } else {
                //             player_2.addWin();
                //             std::cout << player_2.getName() << " defeats " << player_1.getName() << "\n";  
                //         }
                //     }
                // }

//                 for (size_t i = 0; i != group.getLength(); i++) {
//                     for (size_t j = 0; j != group.getLength(); j++) {
//                         Match match(group[i], group[j]);
//                         Player winner = match.playMatch();

//                         m_MatchWins[winner.getId()]++; // Track number of wins
//                         m_TotalPoints[winner.getId()] += winner.getSkillLevel() + winner.getPoints(); // Track number of points

//                         // match.playMatch();
                        
//                         // winner.addWin();
//                     }                        
//                 }
//             }
//         }

//         void determineWinners() {
//             std::cout << "\n --- Advancing Players ---\n";

//             for (auto& group : m_Groups) {            
//                 // group.

//             // Sort group players based on points (higher points = higher skill level and ranking)
//             // std::sort(group.begin(), group.end(),
//             //     [](const Vector<Player>& first_player, const Vector<Player>& second_player){
//             //         return first_player[0].getPoints() > second_player[1].getPoints();
//             //     }
//             // ); 
                
//             // Andy Murray
//             // Rafael Nadal
//             // Novak Djokovic
//             // Roger Federer

//                 std::cout << group[0].getName() << "\n";
//                 std::cout << group[1].getName() << "\n";
//                 std::cout << group[2].getName() << "\n";
//                 std::cout << group[3].getName() << "\n";
//                 // std::cout << group[4].getName() << "\n";
//                 // std::cout << group[5].getName() << "\n";
//                 // std::cout << group[6].getName() << "\n";

//                 std::cout << m_MatchWins[group[0].getId()] << "\n";
//                 std::cout << m_MatchWins[group[1].getId()] << "\n";
//                 std::cout << m_MatchWins[group[2].getId()] << "\n";
//                 std::cout << m_MatchWins[group[3].getId()] << "\n";

//                 // std::sort(m_Groups.begin(), m_Groups.end(), [&](const Player& first_player, const Player& second_player) {
//                 //         return m_MatchWins[first_player.getId()] > m_MatchWins[second_player.getId()];
//                 //     });

//                 // Sort::quickSort(group.begin(), group.end(), [&](const Player& first_player, const Player& second_player) {
//                 //     std::cout << "\n\nPPP" << first_player.getId() << second_player.getId() << "\n";

//                 //     return m_MatchWins[first_player.getId()] > m_MatchWins[second_player.getId()];
//                 // });
//                 // std::sort(group.begin(), group.end(), [&](const Player& first_player, const Player& second_player) {
//                 //     return m_MatchWins[first_player.getId()] > m_MatchWins[second_player.getId()];
//                 // });

//                 // for (size_t i = 0; i != group.getLength(); i++) {
//                 //     std::cout << group[i].getName() << "\n";
//                 //     // std::cout << group[1].getName() << "\n";
//                 // }

//                 Player firstPlayerId = group[group.getLength() - 1]; // First best player
//                 Player secondPlayerId = group[group.getLength() - 2]; // Second best player

//                 if (m_MatchWins[firstPlayerId.getId()] == m_MatchWins[secondPlayerId.getId()]) {
//                     Player tiebreakerWinner = applyTieBreaker(firstPlayerId, secondPlayerId);
//                     m_AdvancingPlayers.enqueue(tiebreakerWinner);
//                 } else {
//                     m_AdvancingPlayers.enqueue(firstPlayerId); // First best player
//                     m_AdvancingPlayers.enqueue(secondPlayerId); // Second best player
//                 }
//             }
//         }

//         Player applyTieBreaker(Player& first_player, Player& second_player) {
//             if (m_TotalPoints[first_player.getId()] > m_TotalPoints[second_player.getId()]) {
//                 return first_player;
//             } else if (m_TotalPoints[second_player.getId()] > m_TotalPoints[first_player.getId()]) {
//                 return second_player;
//             } else {
//                 return (first_player.getSkillLevel() > second_player.getSkillLevel()) ? first_player : second_player;
//             }
//         }

//         Queue<Player>& getAdvancingPlayers() {
//             return m_AdvancingPlayers;
//         }
//     private:
//         Vector<Vector<Player>> m_Groups;
//         Queue<Player> m_AdvancingPlayers;

//         std::unordered_map<std::string, int32_t> m_MatchWins; // Player Id -> Total Win Count
//         std::unordered_map<std::string, int32_t> m_TotalPoints; // Player Id -> Total Points
//     };
// } // namespace TCMS
// #pragma once

// #include <iostream>
// #include <memory>
// #include "../data_structures/CircularQueue.hpp"
// #include "../data_structures/PriorityQueue.hpp"
// #include "../models/Player.hpp"
// #include "../models/Match.hpp"

// namespace TCMS {
//     class RoundRobin {
//     public:
//         RoundRobin(CircularQueue<std::shared_ptr<Player>>& players)
//             : m_AdvancingPlayers(std::make_shared<PriorityQueue<std::shared_ptr<Player>>>()) {   

//             while (!players.isEmpty()) {
//                 m_PlayerQueue.enqueue(players.dequeue());  // Load players into CircularQueue
//             }
//         }

//         void playGroupMatches() {
//             std::cout << "\n--- Round Robin Matches ---\n";

//             size_t matchCount = m_PlayerQueue.getSize();
//             for (size_t i = 0; i < matchCount; i++) {
//                 auto player1 = m_PlayerQueue.dequeue();
//                 auto player2 = m_PlayerQueue.peekFront(); // Next player in the queue

//                 Match match(player1, player2);
//                 auto winner = match.playMatch();

//                 if (winner) {
//                     m_MatchWins[winner->getId()]++;
//                     m_TotalPoints[winner->getId()] += winner->getSkillLevel() + winner->getPoints();
//                 }

//                 m_PlayerQueue.enqueue(player1);  // Rotate players
//             }
//         }

//         void determineWinners() {
//             std::cout << "\n--- Advancing Players ---\n";
            
//             while (!m_PlayerQueue.isEmpty()) {
//                 auto player = m_PlayerQueue.dequeue();
//                 m_AdvancingPlayers->enqueue(player, m_MatchWins[player->getId()]);
//             }
//         }

//         std::shared_ptr<PriorityQueue<std::shared_ptr<Player>>> getAdvancingPlayers() {
//             return m_AdvancingPlayers;
//         }

//     private:
//         CircularQueue<std::shared_ptr<Player>> m_PlayerQueue;
//         std::shared_ptr<PriorityQueue<std::shared_ptr<Player>>> m_AdvancingPlayers;
//         HashMap<std::string, int32_t> m_MatchWins;
//         HashMap<std::string, int32_t> m_TotalPoints;
//     };
// }
