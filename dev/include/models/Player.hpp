#pragma once 

#include <string>
#include <iostream>

namespace TCMS
{
    // Just a temporary template 
    class Player {
    public:
        void registerPlayer() {

        }

        void withdraw() {

        }

        bool operator<(const Player& other) const {
            return m_SkillLevel < other.m_SkillLevel;
        }

        bool operator>(const Player& other) const {
            return m_SkillLevel < other.m_SkillLevel;
        }

        bool operator==(const Player& other) const {
            return m_Name == other.m_Name;
        }

        friend std::ostream& operator<<(std::ostream& output_stream, const Player& other) {
            output_stream << "Player: " << other.m_Name;
            return output_stream;
        }

        int32_t getSkillLevel() const { return m_SkillLevel; }
        std::string getName() const { return m_Name; }
        int32_t getAge() const { return m_Age; }

    private:
        std::string m_PlayerId;

        std::string m_Name;
        int32_t m_Age;

        int32_t m_SkillLevel;

        std::string m_MatchHistory;
        bool m_HasWithdrawn;
    };    
} // namespace TCMS
