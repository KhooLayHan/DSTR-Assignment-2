// #pragma once

// #include <string>

// #include "../data_structures/Queue.hpp" // Not sure what to use

// namespace TCMS
// {
//     // Just a temporary template
//     class BracketManager {
//     public:
//         void updateBracket() {

//         }

//         void generateNextRound() {

//         }

//         void displayBracket() {

//         }
//     private:
//         Queue<std::string> m_BracketStructure; // Need to ???
//     };
// } // namespace TCMS

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
        BracketManager(PriorityQueue<Players>& seedingQueue) {
            generateBracket(seedingQueue);
        }

        ~BracketManager() {
            m_KnockoutBracketPlayers.pop();
        }

        void displayBracket() {
            std::cout << "\n--- Knockout Bracket ---\n";
            // Stack<Players> tempStack = m_KnockoutBracketPlayers;

            // while (!tempStack.isEmpty()) {
            //     std::cout << tempStack.pop()->getName() << "\n";
            // }

            // std::cout << "\n--- Players Advancing to Knockout ---\n";
            for (const auto& player : m_KnockoutBracketPlayers.getElements()) {
                std::cout << player->getName() << "\n";
            }
        }

        Stack<Players> getBracket() {
            return m_KnockoutBracketPlayers;
        }

        void f() {
            // std::cout << m_KnockoutBracketPlayerspeek()->getName() << "\n"; 
            // m_KnockoutBracketPlayers.print();
            // Stack<Players> tempStack = m_KnockoutBracketPlayers;
            // tempStack.peek().get
            // while (!tempStack.isEmpty()) {
            //     std::cout << tempStack..pop()->getName() << "\n";
            // }

            // while (!tempStack.isEmpty()) {
            //     auto g = tempStack.popNoDelete();
            //     std::cout << g->getName() << "\n";
            //     // std::cout << g-use_count() << "\n";
            //     // g.reset();
            //     // std::cout << g.unique() << "\n";
            // }
        }

        // std::shared_ptr<Stack<Players>> getBracket() {
        //     return m_KnockoutBracketPlayers.print;
        // }

    private:
        Stack<Players> m_KnockoutBracketPlayers;

        void generateBracket(PriorityQueue<Players>& seedingQueue) {
            while (!seedingQueue.isEmpty()) {
                m_KnockoutBracketPlayers.push(seedingQueue.dequeue());
            }
        }
    };
}