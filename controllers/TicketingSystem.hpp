#pragma once

#include <string>

#include "../data_structures/Queue.hpp"
#include "../data_structures/PriorityQueue.hpp"
#include "../data_structures/CircularQueue.hpp"

#include "../models/Ticket.hpp"
#include "../models/Spectator.hpp"
#include "../models/VenueSection.hpp"

namespace TCMS
{
    class TicketingSystem {
    public:
        /**
         * @brief Constructs a new ticketing system.
         */
        TicketingSystem();
        
        /**
         * @brief Destroys the ticketing system and frees all allocated resources.
         */
        ~TicketingSystem();

        // Ticket management
        void addTicket(Ticket* ticket);
        void addBuyerToQueue(Spectator* spectator, TicketType type);
        void sellTickets();
        void cancelTicket(const std::string& ticket_id);
        
        // Spectator entry/exit management
        void checkInSpectator(Spectator* spectator);
        void processEntryQueue();
        void spectatorExit(Spectator* spectator);
        
        // Venue section management
        void setupVenueSections(int numSections = 4, int sectionCapacity = 50);
        void assignSectionToSpectator(Spectator* spectator);
        void balanceSections();
        void displaySectionStatus();
        
        // Reporting and statistics
        int getAvailableTicketsCount(TicketType type);
        double getTotalRevenue();
        void displayAvailableTickets();
        void displaySoldTickets();
        
    private:
        // Data structures
        PriorityQueue<Spectator*> ticket_priority_queue; ///< Queue for ticket purchases
        Queue<Spectator*> entry_queue;                  ///< Queue for entry processing
        CircularQueue<VenueSection*> venue_sections;    ///< Circular queue for venue sections
        DoublyLinkedList<Ticket*> available_tickets;    ///< List of available tickets
        DoublyLinkedList<Ticket*> sold_tickets;         ///< List of sold tickets
        
        // Helper methods
        Ticket* findAvailableTicket(TicketType type);
        VenueSection* findLeastOccupiedSection();
    };
} // namespace TCMS