#pragma once 

#include "Player.hpp"

namespace TCMS
{
    // Just a temporary template 
    class Match {
    public:
        void playMatch() {

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
