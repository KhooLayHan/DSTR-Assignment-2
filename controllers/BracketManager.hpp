#pragma once

#include <iostream>
#include <memory>
#include "../data_structures/PriorityQueue.hpp"
#include "../data_structures/Stack.hpp"
#include "../models/Player.hpp"
#include "../models/Match.hpp"

namespace TCMS {
    class BracketManager {
    public:
        // Constructor: Initializes the bracket manager with a seeding queue
        BracketManager(std::shared_ptr<PriorityQueue<Players>> seedingQueue) {
            generateBracket(seedingQueue); // Generate the knockout bracket
        }

        // Destructor: Cleans up the bracket stack
        ~BracketManager() {
            while (!m_KnockoutBracketPlayers->isEmpty()) {
                m_KnockoutBracketPlayers->pop(); // Clear the stack
            }
        }

        // Display the knockout bracket
        void displayBracket() const {
            std::cout << "\n--- Knockout Bracket ---\n";
            for (const auto& player : *m_KnockoutBracketPlayers) {
                std::cout << player->getName() << "\n"; // Print each player's name
            }
        }

        // Get the knockout bracket as a shared_ptr to a stack
        std::shared_ptr<Stack<Players>> getBracket() const {
            return m_KnockoutBracketPlayers;
        }

    private:
        std::shared_ptr<Stack<Players>> m_KnockoutBracketPlayers = 
            std::make_shared<Stack<Players>>(); // Shared ownership of the bracket stack

        // Generate the knockout bracket from the seeding queue
        void generateBracket(std::shared_ptr<PriorityQueue<Players>> seedingQueue) {
            while (!seedingQueue->isEmpty()) {
                m_KnockoutBracketPlayers->push(seedingQueue->dequeue()); // Push players into the bracket
            }
        }
    };
} // namespace TCMS