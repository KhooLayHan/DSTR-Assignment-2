// #pragma once

// #include <iostream>
// #include <memory>

// #include "../data_structures/PriorityQueue.hpp"
// #include "../data_structures/Stack.hpp"
// #include "../models/Player.hpp"
// #include "../models/Match.hpp"

// namespace TCMS {
//     class BracketManager {
//     public:
//         BracketManager(PriorityQueue<Players>& seedingQueue) {
//             generateBracket(seedingQueue);
//         }

//         ~BracketManager() {
//             m_KnockoutBracketPlayers.pop();
//         }

//         void displayBracket() {
//             std::cout << "\n--- Knockout Bracket ---\n";
//             // Stack<Players> tempStack = m_KnockoutBracketPlayers;

//             // while (!tempStack.isEmpty()) {
//             //     std::cout << tempStack.pop()->getName() << "\n";
//             // }

//             // std::cout << "\n--- Players Advancing to Knockout ---\n";
//             for (const auto& player : m_KnockoutBracketPlayers.getElements()) {
//                 std::cout << player->getName() << "\n";
//             }
//         }

//         std::shared_ptr<Stack<Players>> getBracket() {
//             return m_KnockoutBracketPlayers;
//         }

//         void f() {
//             // std::cout << m_KnockoutBracketPlayerspeek()->getName() << "\n"; 
//             // m_KnockoutBracketPlayers.print();
//             // Stack<Players> tempStack = m_KnockoutBracketPlayers;
//             // tempStack.peek().get
//             // while (!tempStack.isEmpty()) {
//             //     std::cout << tempStack..pop()->getName() << "\n";
//             // }

//             // while (!tempStack.isEmpty()) {
//             //     auto g = tempStack.popNoDelete();
//             //     std::cout << g->getName() << "\n";
//             //     // std::cout << g-use_count() << "\n";
//             //     // g.reset();
//             //     // std::cout << g.unique() << "\n";
//             // }
//         }

//         // std::shared_ptr<Stack<Players>> getBracket() {
//         //     return m_KnockoutBracketPlayers.print;
//         // }

//     private:
//         Stack<Players> m_KnockoutBracketPlayers;

//         void generateBracket(PriorityQueue<Players>& seedingQueue) {
//             while (!seedingQueue.isEmpty()) {
//                 m_KnockoutBracketPlayers.push(seedingQueue.dequeue());
//             }
//         }
//     };
// }

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
        // Constructor: Generates the bracket from the seeding queue
        BracketManager(std::shared_ptr<PriorityQueue<Players>> seedingQueue) {
            generateBracket(seedingQueue);
        }

        // Destructor: Cleans up the bracket stack
        ~BracketManager() {
            while (!m_KnockoutBracketPlayers->isEmpty()) {
                m_KnockoutBracketPlayers->pop();
            }
        }

        // Displays the knockout bracket
        void displayBracket() const {
            std::cout << "\n--- Knockout Bracket ---\n";
            // auto tempStack = *m_KnockoutBracketPlayers; // Create a copy of the stack

            // while (!tempStack.isEmpty()) {
            //     auto player = tempStack.pop();
            //     std::cout << player->getName() << "\n";
            // }

            for (const auto& player : *m_KnockoutBracketPlayers) {
                std::cout << player->getName() << "\n";
            }
        }

        // Returns the knockout bracket as a shared_ptr to a stack
        std::shared_ptr<Stack<std::shared_ptr<Player>>> getBracket() const {
            return m_KnockoutBracketPlayers;
        }

    private:
        std::shared_ptr<Stack<Players>> m_KnockoutBracketPlayers = 
            std::make_shared<Stack<Players>>(); // Shared ownership of the bracket stack

        // Generates the bracket from the seeding queue
        void generateBracket(std::shared_ptr<PriorityQueue<Players>> seedingQueue) {
            while (!seedingQueue->isEmpty()) {
                m_KnockoutBracketPlayers->push(seedingQueue->dequeue());
            }
        }
    };
} // namespace TCMS