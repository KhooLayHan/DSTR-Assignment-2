#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <string_view>

#include "../models/Player.hpp"

#include "../data_structures/hash_map/HashMap.hpp"
#include "../data_structures/linked_lists/SinglyLinkedList.hpp"
#include "../data_structures/Queue.hpp"
#include "../data_structures/Stack.hpp"

#include "../core/FileHandling.hpp"
#include "../utils/SimpleLoggingService.hpp"
#include "../utils/SimpleFileLogger.hpp"

namespace TCMS
{
    class PlayerManager
    {
    public:
        // Create a new Player with only given name and skillLevel 
        void createPlayer(std::string_view name, int32_t skillLevel)
        {
            auto player = std::make_shared<Player>(name, skillLevel, "Unknown", 0, "Unknown", 0);
            m_PlayerMap.insert(player->getUID(), player); // Add to HashMap
            m_PlayerQueue.enqueue(player);             // Add to Queue
            m_PlayerStack.push(player);                // Add to Stack
            m_PlayerList.insertEnd(player);            // Add to SinglyLinkedList

            std::cout << "\nCreated New Player: " << player->getName() << " (ID: " << player->getUUID() << ", UID: " << player->getUID() << ")\n";

            FileHandling::appendPlayerFileNewline("./logs/player.txt", player);
            // savePlayersToFile();
        }

        // Create a new player
        void createPlayer(std::string_view name, int32_t skillLevel, std::string_view nationality, int32_t age, std::string_view gender, int32_t ranking)
        {
            auto player = std::make_shared<Player>(name, skillLevel, nationality, age, gender, ranking);
            m_PlayerMap.insert(player->getUID(), player); // Add to HashMap
            m_PlayerQueue.enqueue(player);             // Add to Queue
            m_PlayerStack.push(player);                // Add to Stack
            m_PlayerList.insertEnd(player);            // Add to SinglyLinkedList

            std::cout << "\nCreated New Player: " << player->getName() << " (ID: " << player->getUUID() << ", UID: " << player->getUID() << ")\n";

            // savePlayersToFile();
            FileHandling::appendPlayerFileNewline("./logs/player.txt", player);
        }

        // Read players stored from Vector
        void registerPlayers(Vector<Players>& players)
        {
            for (auto& player : players) {
                m_PlayerMap.insert(player->getUID(), player); // Add to HashMap
                m_PlayerQueue.enqueue(player);             // Add to Queue
                m_PlayerStack.push(player);                // Add to Stack
                m_PlayerList.insertEnd(player);            // Add to SinglyLinkedList
            }
        }

        // Read a player by ID
        std::shared_ptr<Player> getPlayer(const std::string& id) const
        {
            auto player = m_PlayerMap.find(id);
            if (player)
            {
                std::cout << "\nPlayer Found: " << player->get()->getName() << "\n";
                return *player; // Dereference the pointer returned by Find
            }

            std::cout << "\nPlayer with ID " << id << " not found.\n";
            return nullptr;
        }

        // Read a player by ID (non-const)
        std::shared_ptr<Player> getPlayer(const std::string& id) 
        {
            auto player = m_PlayerMap.find(id);
            if (player)
            {
                std::cout << "\nPlayer Found: " << player->get()->getName() << "\n";
                return *player; // Dereference the pointer returned by Find
            }
            
            std::cout << "\nPlayer with ID " << id << " not found.\n";
            return nullptr;
        }

        // Update a player's details (name and skill level only)
        void updatePlayer(const std::string& id, std::string_view name, int32_t skillLevel)
        {
            auto player = getPlayer(id);
            if (player)
            {
                player->setName(name);
                player->setSkillLevel(skillLevel);
                player->setNationality("Unknown");
                player->setAge(0);
                player->setGender("Unknown");
                player->setRanking(0);
                std::cout << "\nUpdated Player: " << player->getName() << " (ID: " << player->getUUID() << ", UID: " << player->getUID() << ")\n";

                savePlayersToFile();
            } else {
                std::cout << "\nPlayer not found! Please try again.\n";
            }
        }

        // Update a player's details
        void updatePlayer(const std::string& id, std::string_view name, int32_t skillLevel, std::string_view nationality, int32_t age, std::string_view gender, int32_t ranking)
        {
            auto player = getPlayer(id);
            if (player)
            {
                player->setName(name);
                player->setSkillLevel(skillLevel);
                player->setNationality(nationality);
                player->setAge(age);
                player->setGender(gender);
                player->setRanking(ranking);
                std::cout << "\nUpdated Player: " << player->getName() << " (ID: " << player->getUUID() << ", UID: " << player->getUID() << ")\n";

                savePlayersToFile();
            } else {
                std::cout << "\nPlayer not found! Please try again.\n";
            }
        }

        // Delete a player by ID
        void deletePlayer(const std::string& id)
        {
            auto player = getPlayer(id);
            if (player)
            {
                // Remove from HashMap
                m_PlayerMap.remove(id);

                // Remove from Queue
                Queue<std::shared_ptr<Player>> tempQueue;
                while (!m_PlayerQueue.isEmpty())
                {
                    auto currentPlayer = m_PlayerQueue.dequeue();
                    if (currentPlayer->getUID() != id)
                    {
                        tempQueue.enqueue(currentPlayer);
                    }
                }

                while (!tempQueue.isEmpty()) {
                    m_PlayerQueue.enqueue(tempQueue.dequeue());
                }
                // playerQueue = tempQueue;

                // Remove from Stack
                Stack<std::shared_ptr<Player>> tempStack;
                while (!m_PlayerStack.isEmpty())
                {
                    auto currentPlayer = m_PlayerStack.pop();
                    if (currentPlayer->getUID() != id)
                    {
                        tempStack.push(currentPlayer);
                    }
                }
                m_PlayerStack = tempStack;

                // Remove from SinglyLinkedList
                m_PlayerList.remove(player);

                std::cout << "\nPlayer deleted: " << player->getName() << " (ID: " << id << ")\n";
                savePlayersToFile();
            }
        }

        // List all players (non-const)
        void listPlayers()
        {
            if (m_PlayerMap.isEmpty())
            {
                std::cout << "\nNo players found.\n";
                return;
            }

            std::cout << "\n----- Players (Queue) -----\n";
            // auto queueCopy = playerQueue;
            for ( auto& element : m_PlayerQueue) {
                std::cout << "ID: " << element->getUID() << ", Name: " << element->getName() << ", Skill Level: " << element->getSkillLevel() << "\n";
            }
            // while (!queueCopy.isEmpty())
            // {
            //         auto player = queueCopy.dequeue();
            //         std::cout << "ID: " << player->getUID() << ", Name: " << player->getName() << ", Skill Level: " << player->getSkillLevel() << "\n";
            // }

            // std::cout << "\n----- Players (Stack) -----\n";
            // auto stackCopy = playerStack;
            // while (!playerStack.isEmpty())
            // {
            //     auto player = playerStack.pop();
            //     std::cout << "ID: " << player->getUID() << ", Name: " << player->getName() << ", Skill Level: " << player->getSkillLevel() << "\n";
            // }

            // std::cout << "\n----- Players (SinglyLinkedList) -----\n";
            // auto current = playerList.getHeadBase();
            // while (auto current = playerList.getHeadBase())
            // {
            //     auto player = current->getData();
            //     std::cout << "ID: " << player->getUID() << ", Name: " << player->getName() << ", Skill Level: " << player->getSkillLevel() << "\n";
            //     current = current->getNext();
            // }
        }

        // Save all players to a file
        void savePlayersToFile()
        {
            std::stringstream data;

            // Add CSV header
            data << "UID,Name,SkillLevel,Nationality,Age,Gender,Ranking\n";

            auto current = m_PlayerList.getHeadBase();
            while (current)
            {
                auto player = current->getData();
                // std::cout << "ID: " << player->getUID() << ", Name: " << player->getName() << ", Skill Level: " << player->getSkillLevel() << "\n";
                
                data << player->getUID() << ","
                     << player->getName() << ","
                     << player->getSkillLevel() << ","
                     << player->getNationality() << ","
                     << player->getAge() << ","
                     << player->getGender() << ","
                     << player->getRanking() << "\n";

                current = current->getNext();
            }

            // Write the serialized data to the file
            FileHandling::writeFile(m_FilePath, data.str());

            SimpleFileLogger fileLogger;
            SimpleLoggingService::UseInfoLogger(fileLogger, "Player data saved to " + m_FilePath.string() + "\n");
        }

    private:
        HashMap<std::string, Players> m_PlayerMap; // Primary storage
        Queue<Players> m_PlayerQueue;            // Queue for FIFO operations
        Stack<Players> m_PlayerStack;            // Stack for LIFO operations
        SinglyLinkedList<Players> m_PlayerList;   // SinglyLinkedList for traversal

        FilePath m_FilePath = "./logs/player.txt"; // File path for persistence
    };
} // namespace TCMS