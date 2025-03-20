#pragma once
#include <iostream>
#include <fstream> // For file handling
#include <memory>
#include <sstream>

namespace TCMS
{
    class MatchRecord
    {
    public:
        MatchRecord(std::string player1, std::string player2, int score1, int score2)
            : m_Player1(player1), m_Player2(player2), m_Score1(score1), m_Score2(score2) {}

        std::string getPlayer1() const { return m_Player1; } // Getter for Player 1
        std::string getPlayer2() const { return m_Player2; } // Getter for Player 2

        void setPlayer1(const std::string &player) { m_Player1 = player; }
        void setPlayer2(const std::string &player) { m_Player2 = player; }
        void setScore1(int score) { m_Score1 = score; }
        void setScore2(int score) { m_Score2 = score; }

        std::string getMatchDetails() const
        {
            return m_Player1 + " (" + std::to_string(m_Score1) + ") vs " + m_Player2 + " (" + std::to_string(m_Score2) + ") -> Winner: " +
                   ((m_Score1 > m_Score2) ? m_Player1 : (m_Score1 < m_Score2) ? m_Player2
                                                                              : "Draw");
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

    private:
        std::string m_Player1;
        std::string m_Player2;
        int m_Score1;
        int m_Score2;
    };
} // namespace TCMS
