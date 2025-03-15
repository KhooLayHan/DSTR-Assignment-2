#pragma once

#include <algorithm>
#include <memory>  // For smart pointers
#include <unordered_map>

#include "../data_structures/Queue.hpp"
#include "../data_structures/PriorityQueue.hpp"
#include "../data_structures/Vector.hpp"

#include "../models/Player.hpp"
#include "../models/Match.hpp"

#include "../algorithms/Sort.hpp"

namespace TCMS
{
    class RoundRobin {
    public:
        RoundRobin(Vector<std::shared_ptr<Player>>& players, int32_t groupSize) {   
            PriorityQueue<std::shared_ptr<Player>> rankingQueue;

            // Enqueue players based on ranking (higher skill = higher priority)
            for (const auto& player : players) {
                rankingQueue.enqueue(player, player->getSkillLevel());
            }
            
            // Divide sorted players into groups
            size_t groupsCount = players.getLength() / groupSize;
            m_Groups.reserve(groupsCount);

            size_t groupIndex = 0;
            while (!rankingQueue.isEmpty()) {
                m_Groups[groupIndex % groupsCount].emplaceBack(rankingQueue.dequeue());
                groupIndex++;
            }
        }   

        void playGroupMatches() {
            std::cout << "\n--- Round Robin Group Matches ---\n";
            
            for (auto& group : m_Groups) {
                for (size_t i = 0; i < group.getLength(); i++) {
                    for (size_t j = 0; j < group.getLength(); j++) {
                        if (i == j) continue;  // Prevent a player from playing themselves

                        Match match(group[i], group[j]);
                        auto winner = match.playMatch();

                        if (winner) {
                            m_MatchWins[winner->getId()]++;  // Track number of wins
                            m_TotalPoints[winner->getId()] += winner->getSkillLevel() + winner->getPoints();  // Track points
                        }
                    }                        
                }
            }
        }

        void determineWinners() {
            std::cout << "\n --- Advancing Players ---\n";

            for (auto& group : m_Groups) {            
                std::cout << group[0]->getName() << "\n";
                std::cout << group[1]->getName() << "\n";
                std::cout << group[2]->getName() << "\n";
                std::cout << group[3]->getName() << "\n";

                std::cout << m_MatchWins[group[0]->getId()] << "\n";
                std::cout << m_MatchWins[group[1]->getId()] << "\n";
                std::cout << m_MatchWins[group[2]->getId()] << "\n";
                std::cout << m_MatchWins[group[3]->getId()] << "\n";

                auto firstPlayer = group[group.getLength() - 1];  // First best player
                auto secondPlayer = group[group.getLength() - 2];  // Second best player

                if (m_MatchWins[firstPlayer->getId()] == m_MatchWins[secondPlayer->getId()]) {
                    auto tiebreakerWinner = applyTieBreaker(firstPlayer, secondPlayer);
                    m_AdvancingPlayers.enqueue(tiebreakerWinner);
                } else {
                    m_AdvancingPlayers.enqueue(firstPlayer);  // First best player
                    m_AdvancingPlayers.enqueue(secondPlayer);  // Second best player
                }
            }
        }

        std::shared_ptr<Player> applyTieBreaker(std::shared_ptr<Player>& firstPlayer, std::shared_ptr<Player>& secondPlayer) {
            if (m_TotalPoints[firstPlayer->getId()] > m_TotalPoints[secondPlayer->getId()]) {
                return firstPlayer;
            } else if (m_TotalPoints[secondPlayer->getId()] > m_TotalPoints[firstPlayer->getId()]) {
                return secondPlayer;
            } else {
                return (firstPlayer->getSkillLevel() > secondPlayer->getSkillLevel()) ? firstPlayer : secondPlayer;
            }
        }

        Queue<std::shared_ptr<Player>>& getAdvancingPlayers() {
            return m_AdvancingPlayers;
        }

    private:
        Vector<Vector<std::shared_ptr<Player>>> m_Groups;
        Queue<std::shared_ptr<Player>> m_AdvancingPlayers;

        std::unordered_map<std::string, int32_t> m_MatchWins;  // Player Id -> Total Win Count
        std::unordered_map<std::string, int32_t> m_TotalPoints;  // Player Id -> Total Points
    };
} // namespace TCMS
