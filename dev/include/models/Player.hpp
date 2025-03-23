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
//     class Player {
//     public:
//         Player() : m_Id(UUID().toString()), m_Name("Unknown"), m_SkillLevel(0) {}

//         Player(std::string_view name, int32_t skillLevel) 
//             : m_Id(UUID().toString()), m_Name(name), m_SkillLevel(skillLevel) {}

//         Player(const Player& other) 
//             : m_Id(other.m_Id), m_Name(other.m_Name), 
//               m_SkillLevel(other.m_SkillLevel), m_Wins(other.m_Wins), m_Points(other.m_Points) {}

//         Player& operator=(const Player& other) {
//             if (this != &other) {
//                 m_Id = other.m_Id;
//                 m_Name = other.m_Name;
//                 m_SkillLevel = other.m_SkillLevel;
//                 m_Wins = other.m_Wins;
//                 m_Points = other.m_Points;
//             }
//             return *this;
//         }
//         // Allow Move Constructor
//         Player(Player&& other) noexcept
//             : m_Id(std::move(other.m_Id)),
//               m_Name(std::move(other.m_Name)),
//               m_SkillLevel(other.m_SkillLevel),
//               m_Wins(other.m_Wins),
//               m_Points(other.m_Points) {
//             std::cout << "Move Constructor Called for " << m_Name << "\n";
//         }

//         Player& operator=(Player&& other) noexcept {
//             if (this != &other) {
//                 m_Id = std::move(other.m_Id);
//                 m_Name = std::move(other.m_Name);
//                 m_SkillLevel = other.m_SkillLevel;
//                 m_Wins = other.m_Wins;
//                 m_Points = other.m_Points;
//             }
            
//             std::cout << "Move Assignment Called for " << m_Name << "\n";
//             return *this;
//         }

//         bool operator==(const Player& other) const {
//             return m_SkillLevel == other.m_SkillLevel;
//         } 

//         friend std::ostream& operator<<(std::ostream& output_stream, const Player& other) {
//             output_stream << "Player: " << other.m_Name;
//             return output_stream;
//         }

//         ~Player() {
//             std::cout << "Destructor Called for " << m_Name << "\n";
//             // delete m_
//         }

//         void addWin() { m_Wins++; m_Points += 3; }

//         std::string getId() const { return m_Id; }
//         std::string getName() const { return m_Name; }
//         int32_t getSkillLevel() const { return m_SkillLevel; }
//         int32_t getWins() const { return m_Wins; }
//         int32_t getPoints() const { return m_Points; }

//     private:
//         std::string m_Id;
//         std::string m_Name;
//         int32_t m_SkillLevel;
//         int32_t m_Wins = 0;
//         int32_t m_Points = 0;
//     };    

//     using Players = std::shared_ptr<Player>;
// } // namespace TCMS


class Player {
    public:
        // Player() {}

        Player() : m_UUID(UUID().toString()), m_UID(UID(TCMS_UID::Player).toPlayerString()), m_Name("Unknown"), m_SkillLevel(0), m_Age(0), m_Ranking(0), m_IsActive(true) {}
    
        Player(std::string_view name, int32_t skillLevel, std::string_view nationality, int32_t age, std::string_view gender, int32_t ranking)
            : m_UUID(UUID().toString()), m_UID(UID(TCMS_UID::Player).toPlayerString()), 
              m_Name(name), m_SkillLevel(skillLevel), m_Nationality(nationality), m_Age(age), m_Gender(gender), m_Ranking(ranking), m_IsActive(true) {}
    
        // Copy Constructor
        Player(const Player& other)
            : m_UUID(other.m_UUID), m_UID(other.m_UID), m_Name(other.m_Name), m_SkillLevel(other.m_SkillLevel),
              m_Nationality(other.m_Nationality), m_Age(other.m_Age), m_Gender(other.m_Gender),
              m_Ranking(other.m_Ranking), m_Wins(other.m_Wins), m_Losses(other.m_Losses),
              m_MatchesPlayed(other.m_MatchesPlayed), m_Points(other.m_Points),
              m_SetsWon(other.m_SetsWon), m_SetsLost(other.m_SetsLost),
              m_GamesWon(other.m_GamesWon), m_GamesLost(other.m_GamesLost),
              m_TournamentPoints(other.m_TournamentPoints), m_Seeding(other.m_Seeding),
              m_IsActive(other.m_IsActive), m_NextMatchId(other.m_NextMatchId),
              m_PreviousMatchIds(other.m_PreviousMatchIds), m_Aces(other.m_Aces),
              m_DoubleFaults(other.m_DoubleFaults) {}
    
        // Move Constructor
        Player(Player&& other) noexcept
            : m_UUID(std::move(other.m_UUID)), m_UID(std::move(other.m_UID)), m_Name(std::move(other.m_Name)),
              m_SkillLevel(other.m_SkillLevel), m_Nationality(std::move(other.m_Nationality)),
              m_Age(other.m_Age), m_Gender(std::move(other.m_Gender)),
              m_Ranking(other.m_Ranking), m_Wins(other.m_Wins), m_Losses(other.m_Losses),
              m_MatchesPlayed(other.m_MatchesPlayed), m_Points(other.m_Points),
              m_SetsWon(other.m_SetsWon), m_SetsLost(other.m_SetsLost),
              m_GamesWon(other.m_GamesWon), m_GamesLost(other.m_GamesLost),
              m_TournamentPoints(other.m_TournamentPoints), m_Seeding(other.m_Seeding),
              m_IsActive(other.m_IsActive), m_NextMatchId(std::move(other.m_NextMatchId)),
              m_PreviousMatchIds(std::move(other.m_PreviousMatchIds)),
              m_Aces(other.m_Aces), m_DoubleFaults(other.m_DoubleFaults) {}
    
        // Assignment Operators (Copy and Move)
        Player& operator=(const Player& other) {
            if (this != &other) {
                m_UUID = std::move(other.m_UUID);
                m_UID = std::move(other.m_UID);

                m_Name = other.m_Name;
                m_SkillLevel = other.m_SkillLevel;
                m_Nationality = other.m_Nationality;
                m_Age = other.m_Age;
                m_Gender = other.m_Gender;
                m_Ranking = other.m_Ranking;
                m_Wins = other.m_Wins;
                m_Losses = other.m_Losses;
                m_MatchesPlayed = other.m_MatchesPlayed;
                m_Points = other.m_Points;
                m_SetsWon = other.m_SetsWon;
                m_SetsLost = other.m_SetsLost;
                m_GamesWon = other.m_GamesWon;
                m_GamesLost = other.m_GamesLost;
                m_TournamentPoints = other.m_TournamentPoints;
                m_Seeding = other.m_Seeding;
                m_IsActive = other.m_IsActive;
                m_NextMatchId = other.m_NextMatchId;
                m_PreviousMatchIds = other.m_PreviousMatchIds;
                m_Aces = other.m_Aces;
                m_DoubleFaults = other.m_DoubleFaults;
            }
            return *this;
        }
    
        Player& operator=(Player&& other) noexcept {
            if (this != &other) {
                m_UUID = std::move(other.m_UUID);
                m_UID = std::move(other.m_UID);

                m_Name = std::move(other.m_Name);
                m_SkillLevel = other.m_SkillLevel;
                m_Nationality = std::move(other.m_Nationality);
                m_Age = other.m_Age;
                m_Gender = std::move(other.m_Gender);
                m_Ranking = other.m_Ranking;
                m_Wins = other.m_Wins;
                m_Losses = other.m_Losses;
                m_MatchesPlayed = other.m_MatchesPlayed;
                m_Points = other.m_Points;
                m_SetsWon = other.m_SetsWon;
                m_SetsLost = other.m_SetsLost;
                m_GamesWon = other.m_GamesWon;
                m_GamesLost = other.m_GamesLost;
                m_TournamentPoints = other.m_TournamentPoints;
                m_Seeding = other.m_Seeding;
                m_IsActive = other.m_IsActive;
                m_NextMatchId = std::move(other.m_NextMatchId);
                m_PreviousMatchIds = std::move(other.m_PreviousMatchIds);
                m_Aces = other.m_Aces;
                m_DoubleFaults = other.m_DoubleFaults;
            }
            return *this;
        }
    
        // Getters and Setters
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
        int32_t getSetsWon() const { return m_SetsWon; }
        int32_t getSetsLost() const { return m_SetsLost; }
        int32_t getGamesWon() const { return m_GamesWon; }
        int32_t getGamesLost() const { return m_GamesLost; }
        int32_t getTournamentPoints() const { return m_TournamentPoints; }
        int32_t getSeeding() const { return m_Seeding; }
        bool isActive() const { return m_IsActive; }
        std::string getNextMatchId() const { return m_NextMatchId; }
        Vector<std::string> getPreviousMatchIds() const { return m_PreviousMatchIds; }
        int32_t getAces() const { return m_Aces; }
        int32_t getDoubleFaults() const { return m_DoubleFaults; }
    
        void setName(std::string_view name) { m_Name = name; }
        void setSkillLevel(int32_t skillLevel) { m_SkillLevel = skillLevel; }
        void setNationality(std::string_view nationality) { m_Nationality = nationality; }
        void setAge(int32_t age) { m_Age = age; }
        void setGender(std::string_view gender) { m_Gender = gender; }
        void setRanking(int32_t ranking) { m_Ranking = ranking; }

        void addWin() { m_Wins++; m_MatchesPlayed++; m_Points += 3; }
        void addLoss() { m_Losses++; m_MatchesPlayed++; }
        void addSetWon() { m_SetsWon++; }
        void addSetLost() { m_SetsLost++; }
        void addGameWon() { m_GamesWon++; }
        void addGameLost() { m_GamesLost++; }
        void addAce() { m_Aces++; }
        void addDoubleFault() { m_DoubleFaults++; }
        void setNextMatchId(const std::string& matchId) { m_NextMatchId = matchId; }
        void addPreviousMatchId(const std::string& matchId) { m_PreviousMatchIds.pushBack(matchId); }
        void setSeeding(int32_t seeding) { m_Seeding = seeding; }
        void setActive(bool isActive) { m_IsActive = isActive; }
    
    private:
        std::string m_UUID;
        std::string m_UID;

        std::string m_Name;
        int32_t m_SkillLevel;
        std::string m_Nationality;
        int32_t m_Age;
        std::string m_Gender;
        int32_t m_Ranking;

        int32_t m_Wins = 0;
        int32_t m_Losses = 0;
        int32_t m_MatchesPlayed = 0;
        int32_t m_Points = 0;
        int32_t m_SetsWon = 0;
        int32_t m_SetsLost = 0;
        int32_t m_GamesWon = 0;
        int32_t m_GamesLost = 0;
        int32_t m_TournamentPoints = 0;
        int32_t m_Seeding = 0;
        
        bool m_IsActive = true;
        std::string m_NextMatchId;
        Vector<std::string> m_PreviousMatchIds;
        int32_t m_Aces = 0;
        int32_t m_DoubleFaults = 0;

        bool isInMatch;
        bool isInSeedingQueue;
        bool isInBrackets;
    };

    using Players = std::shared_ptr<Player>;
} // namespace TCMS
