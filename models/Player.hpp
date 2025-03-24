#pragma once

#include <iostream>
#include <memory> // For smart pointers
#include <string>
#include <string_view>

#include "../core/UUID.hpp"
#include "../core/UID.hpp"
#include "../data_structures/Vector.hpp"

namespace TCMS
{
    /**
     * @brief Represents a player in the tournament management system.
     * 
     * This class stores player information such as name, skill level, nationality, age, gender, and ranking.
     * It also tracks player statistics like wins, losses, matches played, and points.
     */
    class Player {
    public:
        /**
         * @brief Default constructor initializes a player with default values.
         */
        Player() 
            : m_UUID(UUID().toString()), 
              m_UID(UID(TCMS_UID::Player).toPlayerString()), 
              m_Name("Unknown"), 
              m_SkillLevel(0), 
              m_Age(0), 
              m_Ranking(0), 
              m_Withdrawn(false) {}

        /**
         * @brief Constructor initializes a player with basic information.
         * @param name The name of the player.
         * @param skillLevel The skill level of the player.
         */
        Player(std::string_view name, int32_t skillLevel) 
            : m_UUID(UUID().toString()), 
              m_UID(UID(TCMS_UID::Player).toPlayerString()), 
              m_Name(name), 
              m_SkillLevel(skillLevel), 
              m_Age(0), 
              m_Ranking(0), 
              m_Withdrawn(false) {}

        /**
         * @brief Constructor initializes a player with detailed information.
         * @param name The name of the player.
         * @param skillLevel The skill level of the player.
         * @param nationality The nationality of the player.
         * @param age The age of the player.
         * @param gender The gender of the player.
         * @param ranking The ranking of the player.
         */
        Player(std::string_view name, int32_t skillLevel, std::string_view nationality, int32_t age, std::string_view gender, int32_t ranking)
            : m_UUID(UUID().toString()), 
              m_UID(UID(TCMS_UID::Player).toPlayerString()), 
              m_Name(name), 
              m_SkillLevel(skillLevel), 
              m_Nationality(nationality), 
              m_Age(age), 
              m_Gender(gender), 
              m_Ranking(ranking), 
              m_Withdrawn(false) {}

        /**
         * @brief Copy constructor.
         * @param other The player to copy from.
         */
        Player(const Player& other) = default;

        /**
         * @brief Move constructor.
         * @param other The player to move from.
         */
        Player(Player&& other) noexcept = default;

        /**
         * @brief Copy assignment operator.
         * @param other The player to copy from.
         * @return A reference to this player.
         */
        Player& operator=(const Player& other) = default;

        /**
         * @brief Move assignment operator.
         * @param other The player to move from.
         * @return A reference to this player.
         */
        Player& operator=(Player&& other) noexcept = default;

        // Getters
        std::string getUUID() const { return m_UUID; }
        std::string getUID() const { return m_UID; }
        std::string getName() const { return m_Name; }
        int32_t getSkillLevel() const { return m_SkillLevel; }
        std::string getNationality() const { return m_Nationality; }
        int32_t getAge() const { return m_Age; }
        std::string getGender() const { return m_Gender; }
        int32_t getRanking() const { return m_Ranking; }
        int32_t getWins() const { return m_Wins; }
        int32_t getLosses() const { return m_Losses; }
        int32_t getMatchesPlayed() const { return m_MatchesPlayed; }
        int32_t getPoints() const { return m_Points; }
        bool isWithdrawn() const { return m_Withdrawn; }

        // Setters
        void setName(std::string_view name) { m_Name = name; }
        void setSkillLevel(int32_t skillLevel) { m_SkillLevel = skillLevel; }
        void setNationality(std::string_view nationality) { m_Nationality = nationality; }
        void setAge(int32_t age) { m_Age = age; }
        void setGender(std::string_view gender) { m_Gender = gender; }
        void setRanking(int32_t ranking) { m_Ranking = ranking; }
        void setWithdrawn(bool withdrawn) { m_Withdrawn = withdrawn; }

        /**
         * @brief Increments the player's win count and updates points.
         */
        void addWin() { 
            m_Wins++; 
            m_MatchesPlayed++; 
            m_Points += 3; 
        }

        /**
         * @brief Increments the player's loss count.
         */
        void addLoss() { 
            m_Losses++; 
            m_MatchesPlayed++; 
        }

        /**
         * @brief Marks the player as withdrawn from the tournament.
         */
        void withdraw() { 
            m_Withdrawn = true; 
            std::cout << m_Name << " has withdrawn from the tournament.\n"; 
        }

    private:
        std::string m_UUID; // Unique identifier for the player.
        std::string m_UID;  // User-friendly identifier for the player.

        std::string m_Name; // Name of the player.
        int32_t m_SkillLevel; // Skill level of the player.
        std::string m_Nationality; // Nationality of the player.
        int32_t m_Age; // Age of the player.
        std::string m_Gender; // Gender of the player.
        int32_t m_Ranking; // Ranking of the player.

        int32_t m_Wins = 0; // Number of wins.
        int32_t m_Losses = 0; // Number of losses.
        int32_t m_MatchesPlayed = 0; // Total matches played.
        int32_t m_Points = 0; // Total points earned.

        bool m_Withdrawn = false; // Whether the player has withdrawn from the tournament.
    };

    using Players = std::shared_ptr<Player>; // Alias for a shared pointer to a Player.
} // namespace TCMS