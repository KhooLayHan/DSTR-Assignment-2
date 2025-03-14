// controllers/TicketingSystem.hpp
#pragma once

#include <string>
#include "../DataStructures/PriorityQueue.hpp"
#include "../DataStructures/Queue.hpp"
#include "../models/Ticket.hpp"
#include "../models/Spectator.hpp"

namespace TCMS
{
    class TicketingSystem {
    public:
        TicketingSystem();
        ~TicketingSystem();

        void addTicket(Ticket* ticket);
        void addBuyerToQueue(Spectator* spectator, TicketType type);
        void sellTickets();
        void cancelTicket(const std::string& ticket_id);
        void checkInSpectator(Spectator* spectator);
        void processEntryQueue();
        int getAvailableTicketsCount(TicketType type);
        double getTotalRevenue();
        void displayAvailableTickets();
        void displaySoldTickets();
        void spectatorExit(Spectator* spectator);

    private:
        PriorityQueue<Spectator*> ticket_priority_queue;
        Queue<Spectator*> entry_queue;
        DoublyLinkedList<Ticket*> available_tickets; // Use provided DoublyLinkedList
        DoublyLinkedList<Ticket*> sold_tickets;      // Use provided DoublyLinkedList

        Ticket* findAvailableTicket(TicketType type);
    };
} // namespace TCMS
