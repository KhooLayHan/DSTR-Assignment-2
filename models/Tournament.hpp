#pragma once 

#include <string>
#include <memory> // For smart pointers

#include "../DataStructures/Vector.hpp"

#include "../controllers/Qualifiers.hpp"
#include "../controllers/RoundRobin.hpp"
#include "../controllers/KnockoutRound.hpp"

#include "Match.hpp"
#include "Player.hpp"
#include "Spectator.hpp"
#include "Ticket.hpp"

namespace TCMS
{
    class Tournament {
    public:
    void runTournament(Queue<std::shared_ptr<Player>>& players, Queue<std::shared_ptr<Player>>& substitutes) {
            size_t qualifyingSpots = 8;
            Queue<std::shared_ptr<Player>> qualifierQueue;
            
            size_t playerCount = players.getLength(); // Get the number of players before qualifiers

            // Ensure players are moved into the qualifierQueue
            for (size_t i = 0; i < playerCount; i++) {
                qualifierQueue.enqueue(players.dequeue()); // Move players into the qualifier queue
            }
            
            // // Run Qualifiers
            // Qualifiers qualifiers(qualifierQueue, qualifyingSpots);
            auto qualifiers = std::make_shared<Qualifiers>(qualifierQueue, qualifyingSpots);
            qualifiers->playQualifiers();
            auto advancingPlayers = qualifiers->getAdvancingPlayers();
            // qualifiers->getAdvancingPlayers();

            // ✅ Store advancingPlayers in a `shared_ptr` to ensure lifetime safety
            // auto advancingPlayers = std::make_shared<Queue<std::shared_ptr<Player>>>(qualifiers->getAdvancingPlayers());


            // ✅ Debug: Check if players are still in the queue
            // std::cout << "Players in advancing queue after qualifiers:\n";
            // qualifiers->displayAdvancingPlayers();  // Ensure this prints expected players

            // Convert Queue to Vector
            Vector<std::shared_ptr<Player>> advancingPlayersVec;
            while (!advancingPlayers->isEmpty()) {
                advancingPlayersVec.pushBack(advancingPlayers->dequeue());
            }

            // Step 2: Run Round Robin
            int32_t groupSize = 4;  // Adjust as needed
            auto roundRobin = std::make_shared<RoundRobin>(advancingPlayersVec, groupSize);
            roundRobin->playGroupMatches();
            roundRobin->determineWinners();
            // Queue<std::shared_ptr<Player>>& rrAdvancingPlayers = roundRobin->getAdvancingPlayers();

            // Get advancing players for knockout round
            std::shared_ptr<Queue<std::shared_ptr<Player>>> rrAdvancingPlayers = roundRobin->getAdvancingPlayers();

            // ✅ Debug: Ensure players advanced from Round Robin
            // std::cout << "\n✅ Players after Round Robin:\n";
            // while (!rrAdvancingPlayers.isEmpty()) {
            //     std::cout << rrAdvancingPlayers.peekFront()->getName() << "\n";
            //     rrAdvancingPlayers.dequeue();
            // }

            // // Run Knockout Rounds
            // KnockoutRound knockout(advancingPlayers);
            // knockout.playKnockoutMatches();
            // ✅ Pass `shared_ptr` to ensure `advancingPlayers` isn't freed
            auto knockout = std::make_shared<KnockoutRound>(rrAdvancingPlayers);
            knockout->playKnockoutMatches();


            std::cout << "\n\nTournament Completed!\n";
        }
    };    
} // namespace TCMS


// #pragma once 

// #include <string>

// #include "../data_structures/Vector.hpp"

// #include "../controllers/Qualifiers.hpp"
// #include "../controllers/RoundRobin.hpp"
// // #include "../controllers/Knockout.hpp"
// #include "../controllers/KnockoutRound.hpp"

// #include "./Match.hpp"
// #include "./Player.hpp"
// #include "./Spectator.hpp"
// #include "./Ticket.hpp"

// namespace TCMS
// {
//     // Just a temporary template 
//     class Tournament {
//     public:
//         void startTournament() {

//         }   
        
//         void displayInfo() {

//         }
    
//         void runTournament(Vector<Player>& players) {
//             size_t qualifyingSpots = 8;  // Adjust as needed
//             Queue<Player> qualifierQueue;
        
//             // Move players into the Qualifiers Queue
//             for (const auto& player : players) {
//                 qualifierQueue.enqueue(player);
//             }
        
//             // Run Qualifiers
//             Qualifiers qualifiers(qualifierQueue, qualifyingSpots);
//             qualifiers.playQualifiers();
//             Queue<Player>& advancingPlayers = qualifiers.getAdvancingPlayers();

//             // size_t groupCount = 4; // Adjust as needed

//             // RoundRobin roundRobin(players, groupCount);
//             // RoundRobin roundRobin(advancingPlayers, groupCount);
//             // roundRobin.playGroupMatches();
//             // roundRobin.determineWinners();

//             // Queue<Player>& advancingPlayers = roundRobin.getAdvancingPlayers();

//             // MatchScheduler scheduler;
            
//             // Knockout knockout;
//             // knockout.generateKnockoutMatches(advancingPlayers, scheduler);
//             // knockout.playKnockoutRounds(advancingPlayers, scheduler);

//             KnockoutRound knockout(advancingPlayers);
//             knockout.playKnockoutMatches();

//             std::cout << "\n\nTournament Completed!\n";
//         }

//         void endTournament() {

//         }
//     private:
//         std::string m_TournamentId;
        
//         std::string m_Name;
//         std::string m_Location;

//         std::string m_StartDate; // Needs to replace the type later
//         std::string m_EndDate; // Needs to replace the type later

//         std::string m_PlayerList; // Needs to replace the type
//         std::string m_MatchesList; // Needs to replace the type
//     };    
// } // namespace TCMS
