#pragma once

// Header files
// #include "./ConfigManager.hpp"

#include "../controllers/Menu.hpp"
#include "../controllers/TicketingMenu.hpp"

#include <exception>

#if __cplusplus < 202002L
    #error "Minimum C++20 is necessary to run the program. Please update accordingly."
#endif

static int s_AllocationCount = 0; 

// void* operator new(size_t size) {
//     // std::cout << "Allocated " << size << " bytes\n";
//     s_AllocationCount++;
//     return malloc(size);
// }

// void operator delete(void* memory) noexcept {
//     // s_AllocationCount--;
//     std::free(memory);
// }

namespace TCMS {
    class System {      
    public:
        static void Init(/*int argc, char** argv*/) {
            assert(!s_Instance && "System is not initialize.");
            
            s_Instance = new System();

            // s_Instance->config.LoadFromArgs(argc, argv);
            
            // s_Instance->config.EnsureFileSizeLimit("./CSV/combined.csv");
            // s_Instance->config.EnsureFileSizeLimit("./Logs/log.txt");
            // s_Instance->config.EnsureFileSizeLimit("./Logs/error_log.txt");
            
            // s_Instance->config.EnsureFileSizeLimit("./Solutions/question_1.txt");
            // s_Instance->config.EnsureFileSizeLimit("./Solutions/question_2.txt");
            // s_Instance->config.EnsureFileSizeLimit("./Solutions/question_3_array.txt");
            // s_Instance->config.EnsureFileSizeLimit("./Solutions/question_3_linked_list.txt");
        
            std::cout << "---Tennis Championship Management System---\n";
            std::cout << "---      By Group 36     ---\n";
            
            std::cout << "1. Khoo Lay Han TP079817\n2. Chuah Wei Shen TP065295\n3. Ong Ye Hong TP074096\n4. Sally Abdulrahim Abdulrahman Al-Samie TP075399\n";

            // s_Instance->config.PrintConfig();
        }

        static void Run() {
            bool has_input = true;
            std::string input;
            
            auto init_header = []() {                    
                std::cout << "\nPlease choose a task: \n"; 
                std::cout << "1: Task 1: Tournament Scheduling and Player Progression (Khoo Lay Han)\n"; 
                std::cout << "2: Task 2: Ticket Sales and Spectator Management (Ong Ye Hong)\n"; 
                std::cout << "3: Task 3: Handling Player Withdrawals (Chuah Wei Shen)\n"; 
                std::cout << "4: Task 4: Match History Withdrawal (Sally)\n"; 
                std::cout << "5: Shutdown\n\n"; 

                std::cout << "Input: ";
            };
            
            init_header();
            std::cin >> input;

            while (has_input == true) {
                if (input == "1") {
                    // TCMS::Vector<Players> players = {
                    //     std::make_shared<Player>("Roger Federer",         95),
                    //     std::make_shared<Player>("Rafael Nadal",          90),
                    //     std::make_shared<Player>("Novak Djokovic",        92),
                    //     std::make_shared<Player>("Andy Murray",           85),
                    //     std::make_shared<Player>("Alexander Zverev",      87),
                    //     std::make_shared<Player>("Daniil Medvedev",       88),
                    //     std::make_shared<Player>("Stefanos Tsitsipas",    86),
                    //     std::make_shared<Player>("Carlos Alcaraz",        89),
                    // };
                
                    // Tournament tournament;
                    // tournament.runTournament(players);

                    // init_header();
                    // std::cin >> input;
                }
                else if (input == "2") {
                    try {
                        std::cout << "Starting Asia Pacific University Tennis Championship Ticketing System...\n";
                            
                        // Create and run the ticketing menu
                        TCMS::TicketingMenu menu;
                        menu.run();
                        
                        // std::cout << "Program terminated successfully.\n";
                    }
                    catch (const std::exception& e) {
                        std::cerr << "Error: " << e.what() << std::endl;
                    }
                    catch (...) {
                        std::cerr << "Unknown error occurred." << std::endl;
                    }

                    init_header();
                    std::cin >> input;
                }
                else if (input == "3") {
                    task3();

                    init_header();
                    std::cin >> input; 
                }
                else if (input == "4") {
                    Task4_displayMenu();

                    init_header();
                    std::cin >> input;
                }
                else if (input == "5") {
                    has_input = false;  
                    break;
                }
                else {
                    std::cout << "Inputted value was not registered. Please try again.\n";
                    init_header();
                    std::cin >> input; 
                }
            }
        }
        
        static void ShutDown() {
            if (s_Instance) {
                // s_Instance->config.DestroyFileOnShutdown("./CSV/combined.csv");
                
                // s_Instance->config.DestroyFileOnShutdown("./Solutions/question_1.txt");
                // s_Instance->config.DestroyFileOnShutdown("./Solutions/question_2.txt");
                // s_Instance->config.DestroyFileOnShutdown("./Solutions/question_3_array.txt");
                // s_Instance->config.DestroyFileOnShutdown("./Solutions/question_3_linked_list.txt");

                delete s_Instance;
                s_Instance = nullptr;
            }
        }
    protected:
        static System& GetInstance() {
            if (s_Instance == nullptr)
                s_Instance = new System();

            return *s_Instance;
        }

        System(const System&) = delete;
        System& operator=(const System&) = delete;
    private:
        System() {
        }

        ~System() {
            std::cout << "\nSystem has succesfully shutdown.";
            std::cout << '\n' << s_AllocationCount << " allocations.\n";
        }

        inline static System* s_Instance = nullptr;
        // ConfigManager config;
    };
} // namespace TCMS