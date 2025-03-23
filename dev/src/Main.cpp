#include <iostream>
#include <string>

#include "../include/data_structures/linked_lists/SinglyLinkedList.hpp"
#include "../include/data_structures/linked_lists/DoublyLinkedList.hpp"
#include "../include/data_structures/linked_lists/SinglyCircularLinkedList.hpp"

#include "../include/data_structures/Stack.hpp"
#include "../include/data_structures/Queue.hpp"
#include "../include/data_structures/PriorityQueue.hpp"
#include "../include/data_structures/CircularQueue.hpp"

#include "../include/core/UUID.hpp"

#include "../include/data_structures/Vector.hpp"

// #include "../include/data_structures/iterators/Iterator.hpp"
// #include "../include/data_structures/iterators/ForwardIterator.hpp"
// #include "../include/data_structures/iterators/BidirectionalIterator.hpp"
// #include "../include/data_structures/iterators/RandomAccessIterator.hpp"

#include "../include/models/Tournament.hpp"
#include "../include/models/Player.hpp"

#include "../include/controllers/TicketingSystem.hpp"
#include "../include/models/Ticket.hpp"
#include "../include/models/Spectator.hpp"

#include "../include/data_structures/hash_map/HashMap.hpp"

#include "../include/controllers/PlayerManager.hpp"

int main() {
    using namespace TCMS;

    // HashMap<std::string, Players> players;
    // auto player1 = std::make_shared<Player>("Roger Federez", 56, "Spain", 5, "Male", 1);
    // players[player1->getUID()] = player1;
    // auto player = std::make_shared<Player>("Alcarez", 56, "Spain", 5, "Male", 1);
    // players[player->getUID()] = player;
    // map.insert("GG", );
    // map.insert("one", 1);
    // map.insert("two", 2);
    // map.insert("something", 3);
    // map.printAll();
    // // map.
    // map.
    // std::cout << map.bucketCount() << '\n';
    // std::cout << map.getLength() << '\n';
    // std::cout << map.remove("ee") << '\n';
    // map.clear();
    // std::cout << map. << '\n';

    // std::cout << map["ff"] << "\n\n";

    // for (const auto& pair : players) {
    //     std::cout << pair.first << ": " << pair.second->getName() << std::endl;
    // }

    // PlayerManager pp;
    // pp.listPlayers();
    // pp.createPlayer("Roger Federez", 56, "Spain", 5, "Male", 1);
    // pp.createPlayer("John Federez", 56, "Spain", 5, "Male", 1);
    // pp.createPlayer("Gfgg", 56, "Spain", 5, "Male", 1);
    // pp.createPlayer("Jamie", 56, "Spain", 5, "Male", 1);
    // pp.listPlayers();
    
    PlayerManager playerManager;
    Tournament tournament;
    
    std::string input;
    
    auto initHeader = []{        
        std::cout << "\n\n|----------------------------------------------|\n";
        std::cout << "|              WELCOME TO TASK 1               |\n|----------------------------------------------|\n";
        std::cout << "| Tournament Scheduling and Player Progression |\n|----------------------------------------------|\n";
        std::cout << "|         By: Khoo Lay Han TP079817            |\n|----------------------------------------------|\n";
        
        std::cout << "\nWhat do you want to do?\n";
        std::cout << "1: Add New Player\t\t2. Read Existing Player\n";
        std::cout << "3: Update Existing Player\t4. Delete Existing Player\n";
        std::cout << "5: List All Players\t\t6. Run Tournament\n";
        std::cout << "7: Quit\n";
        
        std::cout << "\nInput: ";
    };

    bool isInput = true;

    do {        
        if (input == "1") {
            std::cout << "What is the Player's Name and Skill Level: ";
                
            std::string name, skillLevel;
            std::cin >> name >> skillLevel;

            playerManager.createPlayer(name, std::stoi(skillLevel));

            initHeader();
            std::cin >> input;
        } else if (input == "2") {
            std::cout << "What is the Player's UID: ";
                    
            std::string uid;
            std::cin >> uid;

            playerManager.getPlayer(uid);
            
            initHeader();
            std::cin >> input;     
        } else if (input == "3") {
            std::cout << "What is the Player's UID to Update: ";
                
            std::string uid, name;
            int32_t skillLevel;
            std::cin >> uid;
            
            std::cout << "\nWhat is the Player's new Name and Skill Level: ";
            std::cin >> name >> skillLevel;
            
            playerManager.updatePlayer(uid, name, skillLevel);

            initHeader();
            std::cin >> input;
        } else if (input == "4") {
            std::cout << "What is Player's UID to Delete: ";
                    
            std::string uid;
            std::cin >> uid;

            playerManager.deletePlayer(uid);

            initHeader();
            std::cin >> input;
        } else if (input == "5") {
            std::cout << "All players shown!\n"; 
            playerManager.listPlayers();

            initHeader();
            std::cin >> input;
        } else if (input == "6") {
            Vector<Players> players = {
                std::make_shared<Player>("Roger Federer",         95, "Germany", 45, "M", 1),
                std::make_shared<Player>("Rafael Nadal",          90, "Germany", 45, "M", 1),
                std::make_shared<Player>("Novak Djokovic",        92, "Germany", 45, "M", 1),
                std::make_shared<Player>("Andy Murray",           85, "Germany", 45, "M", 1),
                std::make_shared<Player>("Alexander Zverev",      87, "Germany", 45, "M", 1),
                std::make_shared<Player>("Daniil Medvedev",       88, "Germany", 45, "M", 1),
                std::make_shared<Player>("Stefanos Tsitsipas",    86, "Germany", 45, "M", 1),
                std::make_shared<Player>("Carlos Alcaraz",        89, "Germany", 45, "M", 1),
            };

            tournament.runTournament(players);

            initHeader();
            std::cin >> input;
        } else if (input == "7") {
            isInput = false;
            break;
        } else {
            std::cout << "\nUser input not registered! Please try again.\n";

            initHeader();
            std::cin >> input;
        }
    } while (isInput == true);

    // pp.listPlayers();
    // pp.deletePlayer("2");
    // // pp.deletePlayer("1");
    // pp.deletePlayer("3");
    // pp.deletePlayer("4");
    // pp.updatePlayer("1", "ROGGHT", 32, "Germany", 5, "Fe", 1);
    // std::cout << pp.getPlayer("1")->getName();
// pp.listPlayers();
    // Vector<Players> players = {
    //     std::make_shared<Player>("Roger Federer",         95, "Germany", 45, "M", 1),
    //     std::make_shared<Player>("Rafael Nadal",          90, "Germany", 45, "M", 1),
    //     std::make_shared<Player>("Novak Djokovic",        92, "Germany", 45, "M", 1),
    //     std::make_shared<Player>("Andy Murray",           85, "Germany", 45, "M", 1),
    //     std::make_shared<Player>("Alexander Zverev",      87, "Germany", 45, "M", 1),
    //     std::make_shared<Player>("Daniil Medvedev",       88, "Germany", 45, "M", 1),
    //     std::make_shared<Player>("Stefanos Tsitsipas",    86, "Germany", 45, "M", 1),
    //     std::make_shared<Player>("Carlos Alcaraz",        89, "Germany", 45, "M", 1),
    // };

    // Tournament tournament;
    // tournament.runTournament(players);

    // // Clean up players in the qualifier queue
    // while (!m_QualifierQueue.isEmpty()) {
    //     delete m_QualifierQueue.dequeue();
    // }

    // // Clean up players in the advancing players queue
    // while (!m_AdvancingPlayers->isEmpty()) {
    //     delete m_AdvancingPlayers->dequeue();
    // }

    // // Delete the advancing players queue itself
    // delete m_AdvancingPlayers;
}


    // Vector<std::unique_ptr<Player>> players = {
    //     std::make_unique<Player>("Roger Federer",         95),
    //     std::make_unique<Player>("Rafael Nadal",          90),
    //     std::make_unique<Player>("Novak Djokovic",        92),
    //     std::make_unique<Player>("Andy Murray",           85),
    //     std::make_unique<Player>("Alexander Zverev",      87),
    //     std::make_unique<Player>("Daniil Medvedev",       88),
    //     std::make_unique<Player>("Stefanos Tsitsipas",    86),
    //     std::make_unique<Player>("Carlos Alcaraz",        89),
    // };
    // Vector<Players> players = {
    //     new Player("Roger Federer",         95),
    //     new Player("Rafael Nadal",          90),
    //     new Player("Novak Djokovic",        92),
    //     new Player("Andy Murray",           85),
    //     new Player("Alexander Zverev",      87),
    //     new Player("Daniil Medvedev",       88),
    //     new Player("Stefanos Tsitsipas",    86),
    //     new Player("Carlos Alcaraz",        89),
    // };
