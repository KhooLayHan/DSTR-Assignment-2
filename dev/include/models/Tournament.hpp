// #pragma once 

// #include <string>
// #include <memory> // For smart pointers

// #include "../data_structures/Vector.hpp"

// #include "../controllers/Qualifiers.hpp"
// #include "../controllers/RoundRobin.hpp"
// #include "../controllers/KnockoutRound.hpp"

// #include "./Match.hpp"
// #include "./Player.hpp"
// #include "./Spectator.hpp"
// #include "./Ticket.hpp"

// namespace TCMS
// { 
//     using Players = std::shared_ptr<Player>;

//     class Tournament {
//     public:
//     void runTournament(Vector<Players>& players) {
//             size_t qualifyingSpots = 8;
//             Queue<Players> qualifierQueue;
            
//             // Move players into the Qualifiers Queue
//             for (const auto& player : players) {
//                 qualifierQueue.enqueue(player);
//             }

//             // // Run Qualifiers
//             // Qualifiers qualifiers(qualifierQueue, qualifyingSpots);
//             auto qualifiers = std::make_shared<Qualifiers>(qualifierQueue, qualifyingSpots);
//             qualifiers->playQualifiers();
//             auto advancingPlayers = qualifiers->getAdvancingPlayers();
//             // qualifiers->getAdvancingPlayers();

            // ✅ Store advancingPlayers in a `shared_ptr` to ensure lifetime safety
            // auto advancingPlayers = std::make_shared<Queue<std::shared_ptr<Player>>>(qualifiers->getAdvancingPlayers());


            // ✅ Debug: Check if players are still in the queue
            // std::cout << "Players in advancing queue after qualifiers:\n";
            // qualifiers->displayAdvancingPlayers();  // Ensure this prints expected players

            // Convert Queue to Vector
//             Vector<std::shared_ptr<Player>> advancingPlayersVec;
//             while (!advancingPlayers->isEmpty()) {
//                 advancingPlayersVec.pushBack(advancingPlayers->dequeue());
//             }

//             // Step 2: Run Round Robin
//             int32_t groupSize = 4;  // Adjust as needed
//             auto roundRobin = std::make_shared<RoundRobin>(advancingPlayersVec, groupSize);
//             roundRobin->playGroupMatches();
//             roundRobin->determineWinners();
//             // Queue<std::shared_ptr<Player>>& rrAdvancingPlayers = roundRobin->getAdvancingPlayers();

//             // Get advancing players for knockout round
//             std::shared_ptr<Queue<std::shared_ptr<Player>>> rrAdvancingPlayers = roundRobin->getAdvancingPlayers();

//             // ✅ Debug: Ensure players advanced from Round Robin
//             // std::cout << "\n✅ Players after Round Robin:\n";
//             // while (!rrAdvancingPlayers.isEmpty()) {
//             //     std::cout << rrAdvancingPlayers.peekFront()->getName() << "\n";
//             //     rrAdvancingPlayers.dequeue();
//             // }

//             // // Run Knockout Rounds
//             // KnockoutRound knockout(advancingPlayers);
//             // knockout.playKnockoutMatches();
//             // ✅ Pass `shared_ptr` to ensure `advancingPlayers` isn't freed
//             // auto knockout = std::make_shared<KnockoutRound>(rrAdvancingPlayers);
//             // knockout->playKnockoutMatches();


//             std::cout << "\n\nTournament Completed!\n";
//         }
//     };    
// } // namespace TCMS


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

#pragma once 

#include <string>
#include <memory>

#include "../data_structures/Vector.hpp"
#include "../data_structures/PriorityQueue.hpp"
#include "../controllers/Qualifiers.hpp"
#include "../controllers/RoundRobin.hpp"
#include "../controllers/BracketManager.hpp"
#include "../controllers/KnockoutRound.hpp"
#include "../controllers/SeedingQueue.hpp"

#include "./Match.hpp"
#include "./Player.hpp"
#include "./Spectator.hpp"
#include "./Ticket.hpp"

namespace TCMS
{ 
    class Tournament {
    public:
        void runTournament(Vector<Players> players) {
            static constexpr size_t QUALIFYING_SPOTS = 8;
            
            // Step 1: Run Qualifiers (Queue)
            Queue<Players> qualifierQueue;
            for (const auto& player : players) {
                qualifierQueue.enqueue(player);
            }

            auto qualifiers = std::make_shared<Qualifiers>(qualifierQueue, QUALIFYING_SPOTS);
            // Qualifiers* qualifiers = new Qualifiers(qualifierQueue, QUALIFYING_SPOTS);
            qualifiers->playQualifiers();
            
            // qualifiers->displayAdvancingPlayers();
            // qualifiers->displayAdvancingPlayers();
            // qualifiers->displayAdvancingPlayers();

            // Step 2: Apply Seeding (Priority Queue)
            auto qualifiersAdvancingPlayers = qualifiers->getAdvancingPlayers();
            auto seedingQueue = std::make_shared<SeedingQueue>(qualifiersAdvancingPlayers);
            seedingQueue->printSeedingOrder(); 

            // Get players sorted by ranking
            auto seededPlayers = seedingQueue->getSeedingQueue();

            // Step 3: Round-Robin (Circular Queue; No Bracket Here)
            // CircularQueue<Players> roundRobinQueue = std::make_shared<CircularQueue>();
            // std::shared_ptr<CircularQueue<Players>> roundRobinQueue = std::make_shared<CircularQueue<Players>>();
            // while (!seededPlayers->isEmpty()) {
            //     roundRobinQueue->enqueue(seededPlayers->dequeue());
            // }

            auto roundRobin = std::make_shared<RoundRobin>(seededPlayers);
            // RoundRobin roundRobin(seededPlayers);
            // auto roundRobin = std::make_shared<RoundRobin>(std::move(roundRobinQueue));
            // auto roundRobin = std::make_shared<RoundRobin>(qualifiersAdvancingPlayers);
            roundRobin->playGroupMatches();
            roundRobin->determineWinners();


            // Retrieve advancing players from the Round Robin stage
            auto rrAdvancingPlayers = roundRobin->getAdvancingPlayers(); // Shared ownership of PriorityQueue

            // Step 4: Generate Brackets (Stack)
            auto bracket = std::make_shared<BracketManager>(rrAdvancingPlayers); // Shared ownership of BracketManager
            bracket->displayBracket(); // Display the bracket

            // Step 5: Run Knockout Round (Stack; Bracket Manager)
            auto bracketStack = bracket->getBracket(); // Get the bracket as a stack
            auto knockout = std::make_shared<KnockoutRound>(bracketStack); // Shared ownership of KnockoutRound
            knockout->playKnockoutMatches(); // Play knockout matches

            std::cout << "\n\n🏆 Tournament Completed! 🏆\n\n\n";

            // bracket.~BracketManager();

            // delete[] bracket;
        }
        // std::shared_ptr<PriorityQueue<Players>> rrAdvancingPlayers = roundRobin->getAdvancingPlayers();

        // // Step 4: Generate Brackets (Stack)
        // BracketManager bracket(*rrAdvancingPlayers);
        // // BracketManager bracket(*seededPlayers);
        // bracket.displayBracket();
        // // bracket.f();

        // // ✅ Step 5: Run Knockout Round (Stack; Bracket Manager)
        // Stack<Players> bracketStack = bracket.getBracket();
        // KnockoutRound knockout(bracketStack);
        // // knockout.playKnockoutMatches();
    };    
} // namespace TCMS

            // Vector<std::shared_ptr<Player>> advancingPlayersVec;
            // while (!advancingPlayers->isEmpty()) {
            //     advancingPlayersVec.pushBack(advancingPlayers->dequeue());
            // }
            // for (const auto& player : advancingPlayersVec) {
            //     seedingQueue.addPlayer(advancingPlayers->dequeue());
            // }
