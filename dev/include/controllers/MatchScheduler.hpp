#pragma once

#include <string>

#include "../data_structures/CircularQueue.hpp" 
#include "../data_structures/Queue.hpp" 

#include "../models/Match.hpp" 
#include "../models/Player.hpp" 

namespace TCMS
{
    // Just a temporary template
    class MatchScheduler {
    public:
        void addScheduleMatch(const Player& player_1, const Player& player_2) {
            m_ScheduleQueue.enqueue({ player_1, player_2 });
        }

        void processMatch(Queue<Player>& advancingPlayers) {
            while (hasMatch()) {
                Match currentMatch = m_ScheduleQueue.dequeue();
                Player winner = currentMatch.playMatch();
                advancingPlayers.enqueue(winner);
            }
        }

        bool hasMatch() const {
            return !m_ScheduleQueue.isEmpty();
        }

        void getNextMatch() {

        }

        void displaySchedule() {

        }
    private:
        CircularQueue<Match> m_ScheduleQueue; 
    };
} // namespace TCMS
