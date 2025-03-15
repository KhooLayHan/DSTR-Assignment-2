#pragma once

#include <memory>
#include "../models/Player.hpp"
#include "../models/Match.hpp"
#include "./MatchScheduler.hpp"
#include "./SeedingQueue.hpp"
#include "../data_structures/Queue.hpp"
#include "../data_structures/Stack.hpp"

namespace TCMS
{
    class KnockoutRound {
    public:
        KnockoutRound(Queue<std::shared_ptr<Player>>& advancingPlayers) {
            while (!advancingPlayers.isEmpty()) {
                m_PlayersQueue.enqueue(advancingPlayers.dequeue());
            }
        }
    
        void playKnockoutMatches() {
            std::cout << "\n--- Knockout Rounds Begin ---\n";
            
            while (m_PlayersQueue.getLength() > 1) {
                Queue<std::shared_ptr<Player>> nextRoundQueue;
                
                while (!m_PlayersQueue.isEmpty()) {
                    if (m_PlayersQueue.getLength() == 1) {  
                        auto byePlayer = m_PlayersQueue.dequeue();
                        std::cout << byePlayer->getName() << " gets a bye to the next round!\n";
                        nextRoundQueue.enqueue(byePlayer);
                        break;
                    }

                    auto p1 = m_PlayersQueue.dequeue();
                    auto p2 = m_PlayersQueue.dequeue();
                    
                    Match match(p1, p2);
                    auto winner = match.playMatch();
                    nextRoundQueue.enqueue(winner);
                }

                m_PlayersQueue = nextRoundQueue;
            }

            std::cout << "\n🏆 Champion: " << m_PlayersQueue.peekFront()->getName() << " 🏆\n";
        }
    private:
        Queue<std::shared_ptr<Player>> m_PlayersQueue;
    };
} // namespace TCMS
