#pragma once

#include <algorithm>

#include "../data_structures/Queue.hpp"
#include "../data_structures/Vector.hpp"

#include "../models/Player.hpp"
#include "../models/Match.hpp"

namespace TCMS
{
    class RoundRobin {
    public:
        RoundRobin(Vector<Player>& players, int32_t groupSize) {            
            // Divide players into groups
            size_t groupsCount = players.getLength() / groupSize;
            m_Groups.reserve(groupsCount);
        
            for (size_t i = 0; i != players.getLength(); i++) {
                m_Groups[i % groupsCount].emplaceBack(players[i]);
            }
        }   

        void playGroupMatches() {
            std::cout << "\n--- Round Robin Group Matches ---\n";
            
            for (auto& group : m_Groups) {

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

                for (size_t i = 0; i != group.getLength(); i++) {
                    for (size_t j = 0; j != group.getLength(); j++) {
                        Match match(group[i], group[j]);
                        Player winner = match.playMatch();
                    }                        
                }
            }
        }

        void determineWinners() {
            std::cout << "\n --- Advancing Players ---\n";

            for (auto& group : m_Groups) {
                // group.

                // // Sort group players based on
                // std::sort(group.begin(), group.end(), [](const Player& first_player, const Player& second_player){
                //     return first_player.getSkillLevel() < second_player.getSkillLevel();
                // }); // Sort by skill
                
                m_AdvancingPlayers.enqueue(group[group.getLength() - 1]); // First best player
                m_AdvancingPlayers.enqueue(group[group.getLength() - 2]); // Second best player
            }
        }

        Queue<Player>& getAdvancingPlayers() {
            return m_AdvancingPlayers;
        }
    private:
        Vector<Vector<Player>> m_Groups;
        Queue<Player> m_AdvancingPlayers;
    };
} // namespace TCMS
