// controllers/TicketingMenu.hpp

#pragma once

#include "../controllers/TicketingSystem.hpp"
#include "../models/Ticket.hpp"
#include "../DataStructures/Vector.hpp"
#include <string>

namespace TCMS {

class TicketingMenu {
public:
    TicketingMenu();
    ~TicketingMenu();
    
    void run();

private:
    TicketingSystem m_TicketingSystem;
    Vector<Ticket*> m_RecentlyAddedTickets;
    
    // Menu display functions
    void displayMainMenu();
    void setupInitialTickets();
    
    // Ticket management functions
    void addNewTicket();
    void viewAvailableTickets();
    void viewSoldTickets();
    void viewRecentlyAddedTickets();
    void clearRecentlyAddedTickets();
    
    // Spectator management functions
    void addNewSpectator();
    void processTicketSales();
    void processEntryQueue();
    void handleSpectatorExit();
    void cancelTicket();
    
    // Venue management functions
    void setupVenueSections();
    void viewSectionStatus();
    void balanceSections();
    
    // Statistics function
    void displayTicketStats();
    
    // Utility functions for user input
    int getIntInput(const std::string& prompt);
    double getDoubleInput(const std::string& prompt);
    std::string getStringInput(const std::string& prompt);
    TicketType selectTicketType();
};

} // namespace TCMS