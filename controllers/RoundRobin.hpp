#pragma once

#include <algorithm>
#include <memory>  // For smart pointers
#include <unordered_map>

#include "../DataStructures/Queue.hpp"
#include "../DataStructures/PriorityQueue.hpp"
#include "../DataStructures/Vector.hpp"

#include "../models/Player.hpp"
#include "../models/Match.hpp"

// #include "../algorithms/Sort.hpp"

#include <cmath>

namespace TCMS
{
    class RoundRobin {
    public:
        RoundRobin(Vector<std::shared_ptr<Player>>& players, int32_t groupSize)
            :   m_AdvancingPlayers(std::make_shared<Queue<std::shared_ptr<Player>>>()) {   
            PriorityQueue<std::shared_ptr<Player>> rankingQueue;

            // Enqueue players based on ranking (higher skill = higher priority)
            for (const auto& player : players) {
                rankingQueue.enqueue(player, player->getSkillLevel());
            }
            
            // Divide sorted players into groups
            size_t groupsCount = ceil(players.getLength() / groupSize);
            m_Groups.reserve(groupsCount);

            size_t groupIndex = 0;
            while (!rankingQueue.isEmpty()) {
                m_Groups[groupIndex % groupsCount].emplaceBack(rankingQueue.dequeue());
                groupIndex++;
            }
        }   
        // RoundRobin(Vector<std::shared_ptr<Player>>& players, int32_t groupSize) {   
        //     PriorityQueue<std::shared_ptr<Player>> rankingQueue;

        //     // Enqueue players based on ranking (higher skill = higher priority)
        //     for (const auto& player : players) {
        //         rankingQueue.enqueue(player, player->getSkillLevel());
        //     }
            
        //     // Divide sorted players into groups
        //     size_t groupsCount = ceil(players.getLength() / groupSize);
        //     m_Groups.reserve(groupsCount);

        //     size_t groupIndex = 0;
        //     while (!rankingQueue.isEmpty()) {
        //         m_Groups[groupIndex % groupsCount].emplaceBack(rankingQueue.dequeue());
        //         groupIndex++;
        //     }
        // }   

        void playGroupMatches() {
            std::cout << "\n--- Round Robin Group Matches ---\n";
            
            for (auto& group : m_Groups) {
                for (size_t i = 0; i < group.getLength(); i++) {
                    for (size_t j = 0; j < group.getLength(); j++) {
                        if (i == j) continue;  // Prevent a player from playing themselves

                        Match match(group[i], group[j]);
                        auto winner = match.playMatch();

                        if (winner) {
                            m_MatchWins[winner->getUUID()]++;  // Track number of wins
                            m_TotalPoints[winner->getUUID()] += winner->getSkillLevel() + winner->getPoints();  // Track points
                        }
                    }                        
                }
            }
        }

        void determineWinners() {
            std::cout << "\n--- Advancing Players ---\n";

            for (auto& group : m_Groups) {            
                std::cout << group[0]->getName() << "\n";
                std::cout << group[1]->getName() << "\n";
                std::cout << group[2]->getName() << "\n";
                std::cout << group[3]->getName() << "\n";

                std::cout << m_MatchWins[group[0]->getUUID()] << "\n";
                std::cout << m_MatchWins[group[1]->getUUID()] << "\n";
                std::cout << m_MatchWins[group[2]->getUUID()] << "\n";
                std::cout << m_MatchWins[group[3]->getUUID()] << "\n";

                auto firstPlayer = group[group.getLength() - 1];  // First best player
                auto secondPlayer = group[group.getLength() - 2];  // Second best player

                if (m_MatchWins[firstPlayer->getUUID()] == m_MatchWins[secondPlayer->getUUID()]) {
                    auto tiebreakerWinner = applyTieBreaker(firstPlayer, secondPlayer);
                    m_AdvancingPlayers->enqueue(tiebreakerWinner);
                } else {
                    m_AdvancingPlayers->enqueue(firstPlayer);  // First best player
                    m_AdvancingPlayers->enqueue(secondPlayer);  // Second best player
                }
            }
        }

        std::shared_ptr<Player> applyTieBreaker(std::shared_ptr<Player>& firstPlayer, std::shared_ptr<Player>& secondPlayer) {
            if (m_TotalPoints[firstPlayer->getUUID()] > m_TotalPoints[secondPlayer->getUUID()]) {
                return firstPlayer;
            } else if (m_TotalPoints[secondPlayer->getUUID()] > m_TotalPoints[firstPlayer->getUUID()]) {
                return secondPlayer;
            } else {
                return (firstPlayer->getSkillLevel() > secondPlayer->getSkillLevel()) ? firstPlayer : secondPlayer;
            }
        }

        std::shared_ptr<Queue<std::shared_ptr<Player>>> getAdvancingPlayers() {
            return m_AdvancingPlayers;
        }

    private:
        Vector<Vector<std::shared_ptr<Player>>> m_Groups;
        // Queue<std::shared_ptr<Player>> m_AdvancingPlayers;
        std::shared_ptr<Queue<std::shared_ptr<Player>>> m_AdvancingPlayers;

        std::unordered_map<std::string, int32_t> m_MatchWins;  // Player Id -> Total Win Count
        std::unordered_map<std::string, int32_t> m_TotalPoints;  // Player Id -> Total Points
    };
} // namespace TCMS


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

//                 // for (size_t i = 0; i != m_Groups.getLength(); i++) {
//                 //     for (size_t j = 0; j != m_Groups.getLength(); j++) {
//                 //         Player& player_1 = group[i];
//                 //         Player& player_2 = group[i];

//                 //         // Simulate match based on ranking
//                 //         if (player_1 > player_2) {
//                 //             player_1.addWin();
//                 //             std::cout << player_1.getName() << " defeats " << player_2.getName() << "\n";  
//                 //         } else {
//                 //             player_2.addWin();
//                 //             std::cout << player_2.getName() << " defeats " << player_1.getName() << "\n";  
//                 //         }
//                 //     }
//                 // }

//                 for (size_t i = 0; i != group.getLength(); i++) {
//                     for (size_t j = 0; j != group.getLength(); j++) {
//                         Match match(group[i], group[j]);
//                         Player winner = match.playMatch();

//                         m_MatchWins[winner.getUUID()]++; // Track number of wins
//                         m_TotalPoints[winner.getUUID()] += winner.getSkillLevel() + winner.getPoints(); // Track number of points

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

//                 std::cout << m_MatchWins[group[0].getUUID()] << "\n";
//                 std::cout << m_MatchWins[group[1].getUUID()] << "\n";
//                 std::cout << m_MatchWins[group[2].getUUID()] << "\n";
//                 std::cout << m_MatchWins[group[3].getUUID()] << "\n";

//                 // std::sort(m_Groups.begin(), m_Groups.end(), [&](const Player& first_player, const Player& second_player) {
//                 //         return m_MatchWins[first_player.getUUID()] > m_MatchWins[second_player.getUUID()];
//                 //     });

//                 // Sort::quickSort(group.begin(), group.end(), [&](const Player& first_player, const Player& second_player) {
//                 //     std::cout << "\n\nPPP" << first_player.getUUID() << second_player.getUUID() << "\n";

//                 //     return m_MatchWins[first_player.getUUID()] > m_MatchWins[second_player.getUUID()];
//                 // });
//                 // std::sort(group.begin(), group.end(), [&](const Player& first_player, const Player& second_player) {
//                 //     return m_MatchWins[first_player.getUUID()] > m_MatchWins[second_player.getUUID()];
//                 // });

//                 // for (size_t i = 0; i != group.getLength(); i++) {
//                 //     std::cout << group[i].getName() << "\n";
//                 //     // std::cout << group[1].getName() << "\n";
//                 // }

//                 Player firstPlayerId = group[group.getLength() - 1]; // First best player
//                 Player secondPlayerId = group[group.getLength() - 2]; // Second best player

//                 if (m_MatchWins[firstPlayerId.getUUID()] == m_MatchWins[secondPlayerId.getUUID()]) {
//                     Player tiebreakerWinner = applyTieBreaker(firstPlayerId, secondPlayerId);
//                     m_AdvancingPlayers.enqueue(tiebreakerWinner);
//                 } else {
//                     m_AdvancingPlayers.enqueue(firstPlayerId); // First best player
//                     m_AdvancingPlayers.enqueue(secondPlayerId); // Second best player
//                 }
//             }
//         }

//         Player applyTieBreaker(Player& first_player, Player& second_player) {
//             if (m_TotalPoints[first_player.getUUID()] > m_TotalPoints[second_player.getUUID()]) {
//                 return first_player;
//             } else if (m_TotalPoints[second_player.getUUID()] > m_TotalPoints[first_player.getUUID()]) {
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
