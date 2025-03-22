#pragma once 

#include <iostream>
#include <memory>  // For shared_ptr

#include "Player.hpp"

namespace TCMS
{
    class Match {
    public:
        Match(std::shared_ptr<Player> player_1, std::shared_ptr<Player> player_2)
            : m_Player_1(player_1), m_Player_2(player_2) {}

        std::shared_ptr<Player> playMatch() {
            if (m_Player_1->getSkillLevel() > m_Player_2->getSkillLevel()) {
                m_Player_1->addWin();
                            std::cout << m_Player_1->getName() << " vs " << m_Player_2->getName()
                << " -> Winner: " << m_Player_1->getName() << "\n";
                return m_Player_1;
            } else if (m_Player_2->getSkillLevel() > m_Player_1->getSkillLevel()) {
                m_Player_2->addWin();
                            std::cout << m_Player_1->getName() << " vs " << m_Player_2->getName()
                << " -> Winner: " << m_Player_2->getName() << "\n";
                return m_Player_2;
            }

            std::cout << m_Player_1->getName() << " vs " << m_Player_2->getName()
                      << " -> No Winner (Draw)\n";
            return nullptr;
        }

        //these getters for integration with MatchRecord / Tracker (BY SALLY)
        std::shared_ptr<Player> getPlayer1() const { return m_Player_1; }
        std::shared_ptr<Player> getPlayer2() const { return m_Player_2; }

    private:
        std::shared_ptr<Player> m_Player_1;
        std::shared_ptr<Player> m_Player_2;
    };    
} // namespace TCMS


// #pragma once 

// #include <iostream>

// #include "Player.hpp"

// namespace TCMS
// {
//     // Just a temporary template 
//     class Match {
//     public:
//         // Match() {}

//         Match(Player& player_1, Player& player_2) : m_Player_1(player_1), m_Player_2(player_2) {

//         }

//         // Match(const Player& player_1, const Player& player_2) : m_Player_1(player_1), m_Player_2(player_2) {

//         // }

//         Player playMatch() {
//             Player winner;

//             if (m_Player_1.getSkillLevel() > m_Player_2.getSkillLevel()) {
//                 m_Player_1.addWin();
//                 m_Winner = m_Player_1;
//                 winner = m_Player_1;
//             } else if (m_Player_2.getSkillLevel() > m_Player_1.getSkillLevel()) {
//                 m_Player_2.addWin();
//                 m_Winner = m_Player_2;
//                 winner = m_Player_2;
//             }
//             else if (m_Player_1.getSkillLevel() == m_Player_2.getSkillLevel()) {
//                 std::cout << 
//                 m_Player_1.getName() << " vs " << m_Player_2.getName()
//                 << " -> No Winners; Point 1: " << m_Player_1.getPoints() << ", Point 2: " << m_Player_2.getPoints() << "\n";
//                 return winner;
//             }
            
//             // Player winner = (m_Player_1.getSkillLevel() >= m_Player_2.getSkillLevel()) ? m_Player_1 : m_Player_2;

//             // winner.addWin();

//             std::cout << m_Player_1.getName() << " vs " << m_Player_2.getName()
//                 << " -> Winner: " << winner.getName() << "\n";
//             // std::cout << m_Player_1.getName() << " vs " << m_Player_2.getName()
//             //     << " -> Winner: " << m_Winner.getName() << ", Points: " << m_Winner.getPoints() << "\n";

//             // return m_Winner;
//             return winner;
//         }

//         void getWinner() {

//         } 

//         bool operator==(const Match& other) {
//             return (m_Player_1 == other.m_Player_1 && m_Player_2 == other.m_Player_2) ||
//                    (m_Player_1 == other.m_Player_2 && m_Player_2 == other.m_Player_1);
//         }

//         friend std::ostream& operator<<(std::ostream& output_stream, const Match& other) {
//             output_stream << other.m_Player_1 << ", " << other.m_Player_2;
//             return output_stream;
//         }
//     private:
//         std::string m_MatchId;

//         Player m_Player_1;
//         Player m_Player_2;

//         Player m_Winner;
//         std::string m_Score;

//         std::string m_MatchDate; // Will need to replace with own custom Date class
//     };    
// } // namespace TCMS
