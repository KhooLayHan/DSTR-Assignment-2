#pragma once 

#include <iostream>
#include <memory> // For smart pointers
#include <string>
#include <string_view>

#include "../core/UUID.hpp"

namespace TCMS
{
    class Player {
    public:
        Player() : m_Id(UUID().toString()), m_Name("Unknown"), m_SkillLevel(0) {}

        Player(std::string_view name, int32_t skillLevel) 
            : m_Id(UUID().toString()), m_Name(name), m_SkillLevel(skillLevel) {}

        // Delete Copy Constructor (Prevent Shallow Copies)
        Player(const Player&) = delete;
        Player& operator=(const Player&) = delete;

        // Allow Move Constructor
        Player(Player&& other) noexcept
            : m_Id(std::move(other.m_Id)),
              m_Name(std::move(other.m_Name)),
              m_SkillLevel(other.m_SkillLevel),
              m_Wins(other.m_Wins),
              m_Points(other.m_Points) {
            std::cout << "Move Constructor Called for " << m_Name << "\n";
        }

        Player& operator=(Player&& other) noexcept {
            if (this != &other) {
                m_Id = std::move(other.m_Id);
                m_Name = std::move(other.m_Name);
                m_SkillLevel = other.m_SkillLevel;
                m_Wins = other.m_Wins;
                m_Points = other.m_Points;
            }
            std::cout << "Move Assignment Called for " << m_Name << "\n";
            return *this;
        }

        ~Player() {
            std::cout << "Destructor Called for " << m_Name << "\n";
        }

        void addWin() { m_Wins++; m_Points += 3; }

        std::string getId() const { return m_Id; }
        std::string getName() const { return m_Name; }
        int32_t getSkillLevel() const { return m_SkillLevel; }
        int32_t getWins() const { return m_Wins; }
        int32_t getPoints() const { return m_Points; }

    private:
        std::string m_Id;
        std::string m_Name;
        int32_t m_SkillLevel;
        int32_t m_Wins = 0;
        int32_t m_Points = 0;
    };    
} // namespace TCMS
