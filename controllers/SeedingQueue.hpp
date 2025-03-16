// #pragma once

// #include <iostream>
// #include <string>
// #include <string_view>

// #include "../data_structures/PriorityQueue.hpp"

// namespace TCMS
// {
//     class SeedingQueue
//     {
//     public:
//         void addPlayer(const std::string& name, int32_t ranking) {
//             m_SeedingQueue.enqueue(name, -ranking);
//         }
    
//         void printSeedingOrder() const {
//             std::cout << "Seeding Order: ";
//             m_SeedingQueue.print();
//         }

//         bool isEmpty() const { return m_SeedingQueue.isEmpty(); }
//     private:
//         PriorityQueue<std::string> m_SeedingQueue; 
//     };
// } // namespace TCMS

#pragma once

#include <iostream>
#include <string>
#include <memory>  // For smart pointers
#include "../DataStructures/PriorityQueue.hpp"
#include "../models/Player.hpp"  // Include Player class

namespace TCMS
{
    class SeedingQueue
    {
    public:
        /**
         * @brief Adds a player to the seeding queue.
         * 
         * @param player A shared pointer to the player object.
         */
        void addPlayer(std::shared_ptr<Player> player) {
            m_SeedingQueue.enqueue(player, -player->getSkillLevel()); // Higher skill = higher priority
        }
    
        /**
         * @brief Prints the seeding order of players.
         */
        void printSeedingOrder() const {
            std::cout << "Seeding Order: ";
            m_SeedingQueue.print();
        }

        /**
         * @brief Checks if the seeding queue is empty.
         * 
         * @return True if the queue is empty, otherwise false.
         */
        bool isEmpty() const { return m_SeedingQueue.isEmpty(); }

    private:
        PriorityQueue<std::shared_ptr<Player>> m_SeedingQueue; 
    };
} // namespace TCMS
