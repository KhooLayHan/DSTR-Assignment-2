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
            static constexpr size_t QUALIFYING_SPOTS = 8; // Number of players advancing from qualifiers

            // Step 1: Run Qualifiers (Queue)
            Queue<Players> qualifierQueue;
            for (const auto& player : players) {
                qualifierQueue.enqueue(player); // Enqueue all players for qualifiers
            }

            auto qualifiers = std::make_shared<Qualifiers>(qualifierQueue, QUALIFYING_SPOTS);
            qualifiers->playQualifiers(); // Run the qualifiers
            auto qualifiersAdvancingPlayers = qualifiers->getAdvancingPlayers(); // Get advancing players

            // Step 2: Apply Seeding (Priority Queue)
            auto seedingQueue = std::make_shared<SeedingQueue>(qualifiersAdvancingPlayers);
            seedingQueue->printSeedingOrder(); // Print the seeding order
            auto seededPlayers = seedingQueue->getSeedingQueue(); // Get players sorted by ranking

            // Step 3: Round-Robin (Group Stage)
            auto roundRobin = std::make_shared<RoundRobin>(seededPlayers);
            roundRobin->playGroupMatches(); // Play group matches
            roundRobin->determineWinners(); // Determine winners from the group stage
            auto rrAdvancingPlayers = roundRobin->getAdvancingPlayers(); // Get advancing players

            // Step 4: Generate Brackets (Stack)
            auto bracket = std::make_shared<BracketManager>(rrAdvancingPlayers); // Create bracket
            bracket->displayBracket(); // Display the bracket

            // Step 5: Run Knockout Round (Stack; Bracket Manager)
            auto bracketStack = bracket->getBracket(); // Get the bracket as a stack
            auto knockout = std::make_shared<KnockoutRound>(bracketStack); // Initialize knockout round
            knockout->playKnockoutMatches(); // Play knockout matches

            std::cout << "\n\n🏆 Tournament Completed! 🏆\n\n\n"; // Tournament completion message
        }
    };
} // namespace TCMS