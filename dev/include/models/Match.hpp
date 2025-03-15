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
                return m_Player_1;
            } else if (m_Player_2->getSkillLevel() > m_Player_1->getSkillLevel()) {
                m_Player_2->addWin();
                return m_Player_2;
            }

            std::cout << m_Player_1->getName() << " vs " << m_Player_2->getName()
                      << " -> No Winner (Draw)\n";
            return nullptr;
        }

    private:
        std::shared_ptr<Player> m_Player_1;
        std::shared_ptr<Player> m_Player_2;
    };    
} // namespace TCMS
