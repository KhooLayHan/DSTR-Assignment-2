#pragma once 

#include <string>

#include "../data_structures/Vector.hpp"

#include "../controllers/RoundRobin.hpp"
#include "../controllers/Knockout.hpp"

#include "./Match.hpp"
#include "./Player.hpp"
#include "./Spectator.hpp"
#include "./Ticket.hpp"

namespace TCMS
{
    // Just a temporary template 
    class Tournament {
    public:
        void startTournament() {

        }   
        
        void displayInfo() {

        }
    
        void runTournament(Vector<Player>& players) {
            size_t groupCount = 4; // Adjust as needed

            RoundRobin roundRobin(players, groupCount);
            roundRobin.playGroupMatches();
            roundRobin.determineWinners();

            // Queue<Player>& advancingPlayers = roundRobin.getAdvancingPlayers();

            // MatchScheduler scheduler;
            
            // Knockout knockout;
            // knockout.generateKnockoutMatches(advancingPlayers, scheduler);
            // knockout.playKnockoutRounds(advancingPlayers, scheduler);
        }

        void endTournament() {

        }
    private:
        std::string m_TournamentId;
        
        std::string m_Name;
        std::string m_Location;

        std::string m_StartDate; // Needs to replace the type later
        std::string m_EndDate; // Needs to replace the type later

        std::string m_PlayerList; // Needs to replace the type
        std::string m_MatchesList; // Needs to replace the type
    };    
} // namespace TCMS
