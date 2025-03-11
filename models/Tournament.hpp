#pragma once 

#include <string>

namespace TCMS
{
    // Just a temporary template 
    class Tournament {
    public:
        void startTournament() {

        }   
        
        void displayInfo() {

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
