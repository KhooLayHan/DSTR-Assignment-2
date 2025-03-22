#pragma once
#include <iostream>
#include <fstream> // For file handling
#include <sstream>
#include <memory>
#include "../models/Player.hpp" // From Task 1

namespace TCMS
{
    class MatchRecord
    {
    public:
        // Constructor for Task 4 input
        MatchRecord(std::string player1, std::string player2, int score1, int score2)
        : m_Player1(player1), m_Player2(player2), m_Score1(score1), m_Score2(score2) {}

        // Constructor to support Task 1 integration
        MatchRecord(const Player &player1, const Player &player2)
        : m_Player1(player1.getName()), m_Player2(player2.getName()),
        m_Score1(player1.getSkillLevel()), m_Score2(player2.getSkillLevel()) {}

        std::string getMatchDetails() const
        {
            return m_Player1 + " vs " + m_Player2 + " -> Winner: " +
                   ((m_Score1 > m_Score2) ? m_Player1 : (m_Score1 < m_Score2) ? m_Player2 : "Draw");
        }        
      
        // Convert match record to string format for saving
        std::string toFileString() const
        {
            return m_Player1 + "," + m_Player2 + "," + std::to_string(m_Score1) + "," + std::to_string(m_Score2);
        }

        // Create a MatchRecord object from a saved file line
        static std::shared_ptr<MatchRecord> fromFileString(const std::string &line)
        {
            std::stringstream ss(line);
            std::string player1, player2;
            int score1, score2;

            std::getline(ss, player1, ',');
            std::getline(ss, player2, ',');
            ss >> score1;
            ss.ignore();
            ss >> score2;

            return std::make_shared<MatchRecord>(player1, player2, score1, score2);
        }

        const std::string &getPlayer1() const { return m_Player1; }
        const std::string &getPlayer2() const { return m_Player2; }
        int getScore1() const { return m_Score1; }
        int getScore2() const { return m_Score2; }

        void setPlayer1(const std::string &name) { m_Player1 = name; }
        void setPlayer2(const std::string &name) { m_Player2 = name; }
        void setScore1(int score) { m_Score1 = score; }
        void setScore2(int score) { m_Score2 = score; }

    private:
        std::string m_Player1;
        std::string m_Player2;
        int m_Score1;
        int m_Score2;
    };
} // namespace TCMS
