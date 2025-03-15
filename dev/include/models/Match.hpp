#pragma once 

#include <iostream>

#include "Player.hpp"

namespace TCMS
{
    // Just a temporary template 
    class Match {
    public:
        Match(Player player_1, Player player_2) : m_Player_1(player_1), m_Player_2(player_2) {

        }

        Player playMatch() {
            Player winner = (m_Player_1.getSkillLevel() >= m_Player_2.getSkillLevel()) ? m_Player_1 : m_Player_2;

            std::cout << m_Player_1.getName() << " vs " << m_Player_2.getName()
                << "-> Winner: " << winner.getName() << "\n";

            return winner;
        }

        void getWinner() {

        } 
    private:
        std::string m_MatchId;

        Player m_Player_1;
        Player m_Player_2;

        std::string m_Winner;
        std::string m_Score;

        std::string m_MatchDate; // Will need to replace with own custom Date class
    };    
} // namespace TCMS
