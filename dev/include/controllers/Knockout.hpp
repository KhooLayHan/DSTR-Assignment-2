// #pragma once

// #include "../models/Player.hpp"
// #include "../models/Match.hpp"
// #include "./MatchScheduler.hpp"
// #include "./SeedingQueue.hpp"

// // void runKnockOutTournament(Queue<Player>& players) {
// //     MatchScheduler matchScheduler;
// //     Queue<Player> winnersQueue;

// //     while (players.getSize()) {}

// // }

// namespace TCMS
// {
//     class Knockout {
//     public:        
//         void generateKnockoutMatches(Queue<Player>& advancingPlayers, MatchScheduler& scheduler) {
//             std::cout << "\n--- Knockout Rounds Begins ---\n" ;

//             while (advancingPlayers.getLength() >= 2) {
//                 Player player_1 = advancingPlayers.dequeue();
//                 Player player_2 = advancingPlayers.dequeue();

//                 scheduler.addScheduleMatch(player_1, player_2);
//                 std::cout << "Scheduled: " << player_1.getName() << " vs. " << player_2.getName() << "\n";
//             }
//         }

//         void playKnockoutRounds(Queue<Player>& advancingPlayers, MatchScheduler& scheduler) {
//             Queue<Player> nextRoundQueue;

//             while (scheduler.hasMatch()) {
//                 std::cout << "\n--- Player Knockout Matches ---\n";
//                 scheduler.processMatch(nextRoundQueue);
                
//                 while (!nextRoundQueue.isEmpty()) {
//                     advancingPlayers.enqueue(nextRoundQueue.dequeue());
//                 }

//                 generateKnockoutMatches(advancingPlayers, scheduler);
//             }

//             std::cout << "\n Champion: " << advancingPlayers.peekFront().getName() << "\n";
//         }
//     };
// } // namespace TCMS

// #pragma once

// #include <memory>  // For smart pointers
// #include "../models/Player.hpp"
// #include "../models/Match.hpp"
// #include "./MatchScheduler.hpp"
// #include "./SeedingQueue.hpp"

// namespace TCMS
// {
//     class Knockout {
//     public:
//         void generateKnockoutMatches(Queue<std::shared_ptr<Player>>& advancingPlayers, MatchScheduler& scheduler) {
//             std::cout << "\n--- Knockout Rounds Begin ---\n";

//             while (advancingPlayers.getLength() >= 2) {
//                 auto player_1 = advancingPlayers.dequeue();
//                 auto player_2 = advancingPlayers.dequeue();

//                 scheduler.addScheduleMatch(player_1, player_2);
//                 std::cout << "Scheduled: " << player_1->getName() << " vs. " << player_2->getName() << "\n";
//             }
//         }

//         void playKnockoutRounds(Queue<std::shared_ptr<Player>>& advancingPlayers, MatchScheduler& scheduler) {
//             Queue<std::shared_ptr<Player>> nextRoundQueue;

//             while (scheduler.hasMatch()) {
//                 std::cout << "\n--- Player Knockout Matches ---\n";
//                 scheduler.processMatch(nextRoundQueue);
                
//                 while (!nextRoundQueue.isEmpty()) {
//                     advancingPlayers.enqueue(nextRoundQueue.dequeue());
//                 }

//                 generateKnockoutMatches(advancingPlayers, scheduler);
//             }

//             std::cout << "\n🏆 Champion: " << advancingPlayers.peekFront()->getName() << " 🏆\n";
//         }
//     };
// } // namespace TCMS
