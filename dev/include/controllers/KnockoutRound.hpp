// #pragma once

// #include <memory>
// #include "../models/Player.hpp"
// #include "../models/Match.hpp"
// #include "./MatchScheduler.hpp"
// #include "./SeedingQueue.hpp"
// #include "../data_structures/Queue.hpp"
// #include "../data_structures/Stack.hpp"

// namespace TCMS
// {
//     class KnockoutRound {
//     public:
//         KnockoutRound(Queue<std::shared_ptr<Player>>& advancingPlayers) {
//             while (!advancingPlayers.isEmpty()) {
//                 m_PlayersQueue.enqueue(advancingPlayers.dequeue());
//             }
//         }
    
//         void playKnockoutMatches() {
//             std::cout << "\n--- Knockout Rounds Begin ---\n";
            
//             while (m_PlayersQueue.getLength() > 1) {
//                 Queue<std::shared_ptr<Player>> nextRoundQueue;
                
//                 while (!m_PlayersQueue.isEmpty()) {
//                     if (m_PlayersQueue.getLength() == 1) {  
//                         auto byePlayer = m_PlayersQueue.dequeue();
//                         std::cout << byePlayer->getName() << " gets a bye to the next round!\n";
//                         nextRoundQueue.enqueue(byePlayer);
//                         break;
//                     }

//                     auto p1 = m_PlayersQueue.dequeue();
//                     auto p2 = m_PlayersQueue.dequeue();
                    
//                     Match match(p1, p2);
//                     auto winner = match.playMatch();
//                     nextRoundQueue.enqueue(winner);
//                 }

//                 m_PlayersQueue = nextRoundQueue;
//             }

//             std::cout << "\n🏆 Champion: " << m_PlayersQueue.peekFront()->getName() << " 🏆\n";
//         }
//     private:
//         Queue<std::shared_ptr<Player>> m_PlayersQueue;
//     };
// } // namespace TCMS

// #pragma once

// #include <memory>
// #include "../models/Player.hpp"
// #include "../models/Match.hpp"
// #include "./MatchScheduler.hpp"
// #include "./SeedingQueue.hpp"
// #include "../data_structures/Queue.hpp"
// #include "../data_structures/Stack.hpp"

// namespace TCMS
// {
//     class KnockoutRound {
//     public:
//         // ✅ Use std::shared_ptr to ensure `advancingPlayers` lives until KnockoutRound is done
//         explicit KnockoutRound(std::shared_ptr<Queue<std::shared_ptr<Player>>> advancingPlayers)
//             : m_PlayersQueue(advancingPlayers) {}

//         void playKnockoutMatches() {
//             std::cout << "\n--- Knockout Rounds Begin ---\n";

//             while (m_PlayersQueue->getLength() > 1) {
//                 auto nextRoundQueue = std::make_shared<Queue<std::shared_ptr<Player>>>(); // ✅ Avoid memory overwrite
                
//                 while (!m_PlayersQueue->isEmpty()) {
//                     if (m_PlayersQueue->getLength() == 1) {  
//                         auto byePlayer = m_PlayersQueue->dequeue();
//                         std::cout << byePlayer->getName() << " gets a bye to the next round!\n";
//                         nextRoundQueue->enqueue(byePlayer);
//                         break;
//                     }

//                     auto p1 = m_PlayersQueue->dequeue();
//                     auto p2 = m_PlayersQueue->dequeue();

//                     Match match(p1, p2);
//                     auto winner = match.playMatch();
//                     nextRoundQueue->enqueue(winner);
//                 }

//                 m_PlayersQueue = nextRoundQueue; // ✅ Assign the new queue safely
//             }

//             std::cout << "\n🏆 Champion: " << m_PlayersQueue->peekFront()->getName() << " 🏆\n";
//         }

//     private:
//         std::shared_ptr<Queue<std::shared_ptr<Player>>> m_PlayersQueue;  // ✅ Use shared_ptr to avoid premature deletion
//     };
// } // namespace TCMS



// #pragma once

// #include "../models/Player.hpp"
// #include "../models/Match.hpp"
// #include "./MatchScheduler.hpp"
// #include "./SeedingQueue.hpp"

// #include "../data_structures/Queue.hpp"
// #include "../data_structures/Stack.hpp"

// // void runKnockOutTournament(Queue<Player>& players) {
// //     MatchScheduler matchScheduler;
// //     Queue<Player> winnersQueue;

// //     while (players.getSize()) {}

// // }

// namespace TCMS
// {
//     class KnockoutRound {
//     public:
//         KnockoutRound(Queue<Player>& advancingPlayers) {
//             // Move players from RoundRobin queue to Knockout queue
//             while (!advancingPlayers.isEmpty()) {
//                 Player dequedPlayer =  advancingPlayers.dequeue();


//                 m_PlayersQueue.enqueue(dequedPlayer);
//             }
//         }
    
//         void playKnockoutMatches() {
//             std::cout << "\n--- Knockout Rounds Begin ---\n";
            
//             while (m_PlayersQueue.getLength() > 1) {  // Continue until only 1 player remains
//                 Queue<Player> nextRoundQueue;
                
//                 while (!m_PlayersQueue.isEmpty()) {
//                     if (m_PlayersQueue.getLength() == 1) {  // Odd player gets a bye
//                         Player byePlayer = m_PlayersQueue.dequeue();
//                         std::cout << byePlayer.getName() << " gets a bye to the next round!\n";
//                         nextRoundQueue.enqueue(byePlayer);
//                         break;
//                     }
    
//                     // Pair up players for a match
//                     Player p1 = m_PlayersQueue.dequeue();
//                     Player p2 = m_PlayersQueue.dequeue();
                    
//                     Match match(p1, p2);
//                     Player winner = match.playMatch();
//                     nextRoundQueue.enqueue(winner);
//                 }
    
//                 // Move remaining players to next round
//                 m_PlayersQueue = nextRoundQueue;
//             }
            
//             std::cout << "\n🎉 Champion: " << m_PlayersQueue.peekFront().getName() << " 🎉\n";
//         }
//     private:
//         Queue<Player> m_PlayersQueue;  // Players still in the tournament
//     };
// } // namespace TCMS

#pragma once

#include <iostream>
#include <memory>
#include "../data_structures/Stack.hpp"
#include "../models/Player.hpp"
#include "../models/Match.hpp"

namespace TCMS {
    class KnockoutRound {
    public:
        KnockoutRound(std::shared_ptr<Stack<Players>> bracket) : m_KnockoutPlayers(bracket) {
            m_KnockoutPlayers = bracket;    
        }

        void playKnockoutMatches() {
            std::cout << "\n--- Knockout Rounds Begin ---\n";

            while (m_KnockoutPlayers->getLength() > 1) {
                auto nextRoundStack = std::make_shared<Stack<Players>>();

                while (!m_KnockoutPlayers->isEmpty()) {
                    if (m_KnockoutPlayers->getLength() == 1) {
                        auto byePlayer = m_KnockoutPlayers->pop();

                        std::cout << byePlayer->getName() << " gets a bye!\n";
                        nextRoundStack->push(byePlayer);
                        
                        break;
                    }

                    auto p1 = m_KnockoutPlayers->pop();
                    auto p2 = m_KnockoutPlayers->pop();

                    Match match(p1, p2);
                    auto winner = match.playMatch();
                    nextRoundStack->push(winner);
                }

                m_KnockoutPlayers = nextRoundStack;
            }

            std::cout << "\n🏆 Champion: " << m_KnockoutPlayers->peek()->getName() << " 🏆\n";
        }
    private:
        std::shared_ptr<Stack<Players>> m_KnockoutPlayers;
        
    };
}             
           
