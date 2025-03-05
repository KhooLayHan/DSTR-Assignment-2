#pragma once

#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "./Benchmark.hpp"

// Header files
#include "./ConfigManager.hpp"
#include "./Assignment.cpp"

#if __cplusplus < 202002L
    #error "Minimum C++20 is necessary to run the program. Please update accordingly."
#endif

static int s_AllocationCount = 0; 

void* operator new(size_t size) {
    // std::cout << "Allocated " << size << " bytes\n";
    s_AllocationCount++;
    return malloc(size);
}

namespace PerformanceEvaluation {
    class System {      
        public:
            static void Init(int argc, char** argv) {
                assert(!s_Instance && "System is not initialize.");
                
                s_Instance = new System;

                s_Instance->config.LoadFromArgs(argc, argv);
              
                s_Instance->config.EnsureFileSizeLimit("./CSV/combined.csv");
                s_Instance->config.EnsureFileSizeLimit("./Logs/log.txt");
                s_Instance->config.EnsureFileSizeLimit("./Logs/error_log.txt");
                
                s_Instance->config.EnsureFileSizeLimit("./Solutions/question_1.txt");
                s_Instance->config.EnsureFileSizeLimit("./Solutions/question_2.txt");
                s_Instance->config.EnsureFileSizeLimit("./Solutions/question_3_array.txt");
                s_Instance->config.EnsureFileSizeLimit("./Solutions/question_3_linked_list.txt");
            
                std::cout << "---Performance Evaluation---\n";
                std::cout << "---      By Group 36     ---\n";
                
                std::cout << "1. Khoo Lay Han TP079817\n2. Chuah Wei Shen TP065295\n3. Ong Ye Hong TP074096\n4. Sally Abdulrahim Abdulrahman Al-Samie TP075399\n";

                s_Instance->config.PrintConfig();
            }

            static void Run() {
                Benchmark benchmark;
                
                bool has_input = true;
                std::string input;
                
                auto init_header = []() {                    
                    std::cout << "\nPlease choose a question: \n"; 
                    std::cout << "1a: Question 1 Array          | 1b: Question 1 Linked List\n"; 
                    std::cout << "2a: Question 2 Array          | 2b: Question 2 Linked List\n"; 
                    std::cout << "3a: Question 3 Array          | 3b: Question 3 Linked List\n"; 
                    std::cout << "4a: Question 2 Extra Array    | 4b: Question 2 Extra Linked List\n"; 
                    std::cout << "5: Shutdown\n\n"; 
    
                    std::cout << "Input: ";
                };
                
                init_header();
                std::cin >> input;

                while (has_input == true) {
                    if (input == "1a") {
                        benchmark.MeasureDuration([](){ Assignment::Question_1_Array(); });
                        init_header();
                        std::cin >> input;
                    }
                    else if (input == "1b") {
                        benchmark.MeasureDuration([](){ Assignment::Question_1_LinkedList(); });
                        init_header();
                        std::cin >> input;
                    }
                    else if (input == "2a") {
                        benchmark.MeasureDuration([](){ Assignment::Question_2_Array(); });
                        init_header();
                        std::cin >> input;
                    }
                    else if (input == "2b") {
                        benchmark.MeasureDuration([](){ Assignment::Question_2_LinkedList(); });
                        init_header();
                        std::cin >> input;
                    }
                    else if (input == "3a") {
                        benchmark.MeasureDuration([](){ Assignment::Question_3_Array(); });
                        init_header();
                        std::cin >> input;
                    }
                    else if (input == "3b") {
                        benchmark.MeasureDuration([](){ Assignment::Question_3_Array(); });
                        init_header();
                        std::cin >> input;    
                    }
                    else if (input == "4a") {
                        benchmark.MeasureDuration([](){ Question_2_Array_ExtraExclusive(); });
                        init_header();
                        std::cin >> input;
                    }
                    else if (input == "4b") {
                        benchmark.MeasureDuration([](){ Question_2_LinkedList_ExtraExclusive(); });
                        init_header();
                        std::cin >> input;
                    } 
                    else if (input == "5") {
                        has_input = false;  
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
                    s_Instance->config.DestroyFileOnShutdown("./CSV/combined.csv");
                    
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
            ConfigManager config;
    };
}

#endif