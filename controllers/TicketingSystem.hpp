#pragma once

#include <string>

#include "../DataStructures/PriorityQueue.hpp" // Probably to use this ???

namespace TCMS
{
    // Just a temporary template
    class TicketingSystem {
    public:
        void sellTickets() {

        }

        void cancelTicket() {

        }

        void prioritizeVIP() {

        }

        void displayAllTickets() {
            
        }
    private:
        PriorityQueue<std::string> m_TicketsQueue;

        std::string m_SoldTicketsList; // Need to replace with std::vector or std::array

        std::string m_AvailableTicketsList; // Need to replace with std::vector or std::array
    };
} // namespace TCMS
