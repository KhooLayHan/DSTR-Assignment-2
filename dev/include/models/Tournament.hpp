#pragma once 

#include <string>
#include <memory> // For smart pointers

#include "../data_structures/Vector.hpp"

#include "../controllers/Qualifiers.hpp"
#include "../controllers/RoundRobin.hpp"
#include "../controllers/KnockoutRound.hpp"

#include "./Match.hpp"
#include "./Player.hpp"
#include "./Spectator.hpp"
#include "./Ticket.hpp"

namespace TCMS
{
    class Tournament {
    public:
        void runTournament(Vector<std::shared_ptr<Player>>& players) {
            size_t qualifyingSpots = 8;
            Queue<std::shared_ptr<Player>> qualifierQueue;

            // Move players into the Qualifiers Queue
            for (const auto& player : players) {
                qualifierQueue.enqueue(player);
            }

            // Run Qualifiers
            Qualifiers qualifiers(qualifierQueue, qualifyingSpots);
            qualifiers.playQualifiers();
            Queue<std::shared_ptr<Player>>& advancingPlayers = qualifiers.getAdvancingPlayers();

            // Run Knockout Rounds
            KnockoutRound knockout(advancingPlayers);
            knockout.playKnockoutMatches();

            std::cout << "\n\nTournament Completed!\n";
        }
    };    
} // namespace TCMS
