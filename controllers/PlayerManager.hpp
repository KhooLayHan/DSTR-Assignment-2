#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>
#include <string_view>

#include "../models/Player.hpp"

namespace TCMS
{
    class Player; // Forward declaration

    class PlayerManager {
    public:
        // Create a new player
        void createPlayer(std::string_view name, int32_t skillLevel, std::string_view nationality, int32_t age, std::string_view gender, int32_t ranking) {
            auto player = std::make_shared<Player>(name, skillLevel, nationality, age, gender, ranking);
            players[player->getId()] = player;
            std::cout << "Player created: " << player->getName() << " (ID: " << player->getId() << ")\n";
        }

        // Read a player by ID
        std::shared_ptr<Player> getPlayer(const std::string& id) const {
            auto it = players.find(id);
            if (it != players.end()) {
                return it->second;
            }
            std::cout << "Player with ID " << id << " not found.\n";
            return nullptr;
        }

        // Update a player's details
        void updatePlayer(const std::string& id, std::string_view name, int32_t skillLevel, std::string_view nationality, int32_t age, std::string_view gender, int32_t ranking) {
            auto player = getPlayer(id);
            if (player) {
                player->setName(name);
                player->setSkillLevel(skillLevel);
                player->setNationality(nationality);
                player->setAge(age);
                player->setGender(gender);
                player->setRanking(ranking);
                std::cout << "Player updated: " << player->getName() << " (ID: " << player->getId() << ")\n";
            }
        }

        // Delete a player by ID
        void deletePlayer(const std::string& id) {
            auto it = players.find(id);
            if (it != players.end()) {
                std::cout << "Player deleted: " << it->second->getName() << " (ID: " << id << ")\n";
                players.erase(it);
            } else {
                std::cout << "Player with ID " << id << " not found.\n";
            }
        }

        // List all players
        void listPlayers() const {
            if (players.empty()) {
                std::cout << "No players found.\n";
                return;
            }
            for (const auto& [id, player] : players) {
                std::cout << "ID: " << id << ", Name: " << player->getName() << ", Skill Level: " << player->getSkillLevel() << "\n";
            }
        }

    private:
        std::unordered_map<std::string, Players> players;
    };
} // namespace TCMS