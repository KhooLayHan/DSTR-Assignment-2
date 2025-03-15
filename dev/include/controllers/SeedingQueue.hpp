#pragma once

#include <iostream>
#include <string>
#include <string_view>

#include "../data_structures/PriorityQueue.hpp"

namespace TCMS
{
    class SeedingQueue
    {
    public:
        void addPlayer(const std::string& name, int32_t ranking) {
            m_SeedingQueue.enqueue(name, -ranking);
        }
    
        void printSeedingOrder() const {
            std::cout << "Seeding Order: ";
            m_SeedingQueue.print();
        }

        bool isEmpty() const { return m_SeedingQueue.isEmpty(); }
    private:
        PriorityQueue<std::string> m_SeedingQueue; 
    };
} // namespace TCMS
