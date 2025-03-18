#include "TicketingMenu.hpp"
#include <iostream>
#include <limits>
#include "../DataStructures/Vector.hpp"
#include "../models/Ticket.hpp"
namespace TCMS {

// Constructor
TicketingMenu::TicketingMenu() {
    // Initialize with default venue sections
    m_TicketingSystem.setupVenueSections(4, 30);
    // Initialize recently added tickets vector
    m_RecentlyAddedTickets = Vector<Ticket*>();
}

// Destructor
TicketingMenu::~TicketingMenu() {
    // No need to delete Ticket objects here as they are managed by TicketingSystem
    std::cout << "TicketingMenu destroyed.\n";
}

// Main menu loop
void TicketingMenu::run() {
    // Setup initial tickets for testing/demo purposes
    setupInitialTickets();
    
    bool running = true;
    while (running) {
        displayMainMenu();
        
        int choice = getIntInput("Enter your choice: ");
        std::cout << std::endl;
        
        switch (choice) {
            case 1:  // Ticket Management
                {
                    int subChoice = 0;
                    std::cout << "\n=== Ticket Management ===\n"
                              << "1. Add New Ticket\n"
                              << "2. View Available Tickets\n"
                              << "3. View Sold Tickets\n"
                              << "4. View Recently Added Tickets\n" 
                              << "5. Clear Recently Added Tickets\n"
                              << "6. Return to Main Menu\n";
                    
                    subChoice = getIntInput("Enter your choice: ");
                    std::cout << std::endl;
                    
                    switch (subChoice) {
                        case 1: addNewTicket(); break;
                        case 2: viewAvailableTickets(); break;
                        case 3: viewSoldTickets(); break;
                        case 4: viewRecentlyAddedTickets(); break;
                        case 5: clearRecentlyAddedTickets(); break;
                        case 6: break; // Return to main menu
                        default: std::cout << "Invalid choice. Please try again.\n";
                    }
                }
                break;
                
            case 2:  // Spectator Management
                {
                    int subChoice = 0;
                    std::cout << "\n=== Spectator Management ===\n"
                              << "1. Add New Spectator to Queue\n"
                              << "2. Process Ticket Sales\n"
                              << "3. Process Entry Queue\n"
                              << "4. Handle Spectator Exit\n"
                              << "5. Cancel Ticket\n"
                              << "6. Return to Main Menu\n";
                    
                    subChoice = getIntInput("Enter your choice: ");
                    std::cout << std::endl;
                    
                    switch (subChoice) {
                        case 1: addNewSpectator(); break;
                        case 2: processTicketSales(); break;
                        case 3: processEntryQueue(); break;
                        case 4: handleSpectatorExit(); break;
                        case 5: cancelTicket(); break;
                        case 6: break; // Return to main menu
                        default: std::cout << "Invalid choice. Please try again.\n";
                    }
                }
                break;
                
            case 3:  // Venue Management
                {
                    int subChoice = 0;
                    std::cout << "\n=== Venue Management ===\n"
                              << "1. Setup Venue Sections\n"
                              << "2. View Section Status\n"
                              << "3. Balance Sections\n"
                              << "4. Return to Main Menu\n";
                    
                    subChoice = getIntInput("Enter your choice: ");
                    std::cout << std::endl;
                    
                    switch (subChoice) {
                        case 1: setupVenueSections(); break;
                        case 2: viewSectionStatus(); break;
                        case 3: balanceSections(); break;
                        case 4: break; // Return to main menu
                        default: std::cout << "Invalid choice. Please try again.\n";
                    }
                }
                break;
                
            case 4:  // Reporting
                displayTicketStats();
                break;
                
            case 5:  // Exit
                std::cout << "Exiting program. Thank you for using the Ticketing System.\n";
                running = false;
                break;
                
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

// Display main menu options
void TicketingMenu::displayMainMenu() {
    std::cout << "\n====================================================\n"
              << "ASIA PACIFIC UNIVERSITY TENNIS CHAMPIONSHIP\n"
              << "TICKET SALES AND SPECTATOR MANAGEMENT SYSTEM\n"
              << "====================================================\n\n"
              << "1. Ticket Management\n"
              << "2. Spectator Management\n"
              << "3. Venue Management\n"
              << "4. View Statistics\n"
              << "5. Exit\n";
}

// Setup initial tickets for testing/demonstration
void TicketingMenu::setupInitialTickets() {
    // Create some sample tickets
    
    // VIP tickets (highest price)
    Ticket* vipTicket1 = new Ticket(TicketType::VIP, 200.0, "A1", "M1");
    Ticket* vipTicket2 = new Ticket(TicketType::VIP, 200.0, "A2", "M1");
    Ticket* vipTicket3 = new Ticket(TicketType::VIP, 200.0, "A3", "M2");
    
    // EARLY_BIRD tickets (medium price)
    Ticket* ebTicket1 = new Ticket(TicketType::EARLY_BIRD, 100.0, "B1", "M1");
    Ticket* ebTicket2 = new Ticket(TicketType::EARLY_BIRD, 100.0, "B2", "M1");
    Ticket* ebTicket3 = new Ticket(TicketType::EARLY_BIRD, 100.0, "B3", "M2");
    
    // GENERAL tickets (lowest price)
    Ticket* genTicket1 = new Ticket(TicketType::GENERAL, 50.0, "C1", "M1");
    Ticket* genTicket2 = new Ticket(TicketType::GENERAL, 50.0, "C2", "M1");
    Ticket* genTicket3 = new Ticket(TicketType::GENERAL, 50.0, "C3", "M2");
    
    // Add tickets to the system
    m_TicketingSystem.addTicket(vipTicket1);
    m_TicketingSystem.addTicket(vipTicket2);
    m_TicketingSystem.addTicket(vipTicket3);
    m_TicketingSystem.addTicket(ebTicket1);
    m_TicketingSystem.addTicket(ebTicket2);
    m_TicketingSystem.addTicket(ebTicket3);
    m_TicketingSystem.addTicket(genTicket1);
    m_TicketingSystem.addTicket(genTicket2);
    m_TicketingSystem.addTicket(genTicket3);
    
    // Store initial tickets in recently added list
    m_RecentlyAddedTickets.pushBack(vipTicket1);
    m_RecentlyAddedTickets.pushBack(vipTicket2);
    m_RecentlyAddedTickets.pushBack(vipTicket3);
    m_RecentlyAddedTickets.pushBack(ebTicket1);
    m_RecentlyAddedTickets.pushBack(ebTicket2);
    m_RecentlyAddedTickets.pushBack(ebTicket3);
    m_RecentlyAddedTickets.pushBack(genTicket1);
    m_RecentlyAddedTickets.pushBack(genTicket2);
    m_RecentlyAddedTickets.pushBack(genTicket3);
    
    std::cout << "Initial tickets have been set up.\n";
}

// Add a new ticket to the system
void TicketingMenu::addNewTicket() {
    std::cout << "=== Add New Ticket ===\n";
    
    TicketType type = selectTicketType();
    double price = getDoubleInput("Enter ticket price: $");
    std::string seatNumber = getStringInput("Enter seat number: ");
    std::string matchId = getStringInput("Enter match ID: ");
    
    // Create and add the new ticket
    Ticket* newTicket = new Ticket(type, price, seatNumber, matchId);
    m_TicketingSystem.addTicket(newTicket);
    
    // Add to recently added tickets
    m_RecentlyAddedTickets.pushBack(newTicket);
    
    std::cout << "Ticket added successfully.\n";
}

// View all available tickets
void TicketingMenu::viewAvailableTickets() {
    std::cout << "=== Available Tickets ===\n";
    m_TicketingSystem.displayAvailableTickets();
}

// View all sold tickets
void TicketingMenu::viewSoldTickets() {
    std::cout << "=== Sold Tickets ===\n";
    m_TicketingSystem.displaySoldTickets();
}

// View recently added tickets
void TicketingMenu::viewRecentlyAddedTickets() {
    std::cout << "=== Recently Added Tickets ===\n";
    
    if (m_RecentlyAddedTickets.isEmpty()) {
        std::cout << "No tickets have been recently added.\n";
        return;
    }
    
    std::cout << "Total recently added tickets: " << m_RecentlyAddedTickets.getLength() << "\n\n";
    
    for (size_t i = 0; i < m_RecentlyAddedTickets.getLength(); i++) {
        Ticket* ticket = m_RecentlyAddedTickets[i];
        std::cout << i+1 << ". Ticket ID: " << ticket->getTicketId()
                  << ", Type: " << (ticket->getTicketType() == TicketType::VIP ? "VIP" :
                                  (ticket->getTicketType() == TicketType::EARLY_BIRD ? "Early Bird" : "General"))
                  << ", Price: $" << ticket->getPrice()
                  << ", Seat: " << ticket->getSeatNumber()
                  << ", Match: " << ticket->getMatchId() << "\n";
    }
}

// Clear recently added tickets list
void TicketingMenu::clearRecentlyAddedTickets() {
    m_RecentlyAddedTickets.clear();
    std::cout << "Recently added tickets list has been cleared.\n";
}

// Add a new spectator to the purchase queue
void TicketingMenu::addNewSpectator() {
    std::cout << "=== Add New Spectator ===\n";
    
    std::string name = getStringInput("Enter spectator name: ");
    int age = getIntInput("Enter spectator age: ");
    TicketType preferredTicketType = selectTicketType();
    
    // Create and add the new spectator
    Spectator* newSpectator = new Spectator(name, age);
    m_TicketingSystem.addBuyerToQueue(newSpectator, preferredTicketType);
    
    std::cout << "Spectator " << name << " added to the queue for a " 
              << (preferredTicketType == TicketType::VIP ? "VIP" : 
                 (preferredTicketType == TicketType::EARLY_BIRD ? "Early Bird" : "General"))
              << " ticket.\n";
}

// Process ticket sales for queued spectators
void TicketingMenu::processTicketSales() {
    std::cout << "=== Processing Ticket Sales ===\n";
    m_TicketingSystem.sellTickets();
    std::cout << "Ticket sales processing complete.\n";
}

// Process spectator entry queue
void TicketingMenu::processEntryQueue() {
    std::cout << "=== Processing Entry Queue ===\n";
    m_TicketingSystem.processEntryQueue();
    std::cout << "Entry queue processing complete.\n";
}

// Handle spectator exit (Note: this requires identifying the spectator)
void TicketingMenu::handleSpectatorExit() {
    std::cout << "=== Handle Spectator Exit ===\n";
    std::cout << "Note: In a real implementation, you would select a spectator from a list.\n";
    std::cout << "For demonstration purposes, a placeholder message is shown.\n";
    std::cout << "Spectator exit processing would happen here.\n";
    
    // In a real implementation, you would:
    // 1. Display a list of spectators currently in the venue
    // 2. Let the user select one
    // 3. Call m_TicketingSystem.spectatorExit(selectedSpectator)
}

// Cancel a ticket
void TicketingMenu::cancelTicket() {
    std::cout << "=== Cancel Ticket ===\n";
    std::string ticketId = getStringInput("Enter ticket ID to cancel: ");
    m_TicketingSystem.cancelTicket(ticketId);
    
    // Also remove from recently added list if present
    if (!m_RecentlyAddedTickets.isEmpty()) {
        Vector<Ticket*> tempVector;
        bool found = false;
        
        for (size_t i = 0; i < m_RecentlyAddedTickets.getLength(); i++) {
            Ticket* ticket = m_RecentlyAddedTickets[i];
            if (ticket->getTicketId() != ticketId) {
                tempVector.pushBack(ticket);
            } else {
                found = true;
            }
        }
        
        if (found) {
            m_RecentlyAddedTickets = std::move(tempVector);
            std::cout << "Ticket also removed from recently added list.\n";
        }
    }
}

// Setup venue sections
void TicketingMenu::setupVenueSections() {
    std::cout << "=== Setup Venue Sections ===\n";
    int numSections = getIntInput("Enter number of sections: ");
    int sectionCapacity = getIntInput("Enter capacity per section: ");
    
    m_TicketingSystem.setupVenueSections(numSections, sectionCapacity);
    std::cout << "Venue sections setup complete.\n";
}

// View section status
void TicketingMenu::viewSectionStatus() {
    std::cout << "=== Section Status ===\n";
    m_TicketingSystem.displaySectionStatus();
}

// Balance sections
void TicketingMenu::balanceSections() {
    std::cout << "=== Section Balance Analysis ===\n";
    m_TicketingSystem.balanceSections();
}

// Display ticket statistics
void TicketingMenu::displayTicketStats() {
    std::cout << "=== Ticket Statistics ===\n";
    std::cout << "VIP Tickets Available: " 
              << m_TicketingSystem.getAvailableTicketsCount(TicketType::VIP) << std::endl;
    std::cout << "Early Bird Tickets Available: " 
              << m_TicketingSystem.getAvailableTicketsCount(TicketType::EARLY_BIRD) << std::endl;
    std::cout << "General Tickets Available: " 
              << m_TicketingSystem.getAvailableTicketsCount(TicketType::GENERAL) << std::endl;
    std::cout << "Total Revenue: $" << m_TicketingSystem.getTotalRevenue() << std::endl;
}

// Get integer input from user
int TicketingMenu::getIntInput(const std::string& prompt) {
    int value;
    bool valid = false;
    
    while (!valid) {
        std::cout << prompt;
        if (std::cin >> value) {
            valid = true;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
        }
    }
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

// Get double input from user
double TicketingMenu::getDoubleInput(const std::string& prompt) {
    double value;
    bool valid = false;
    
    while (!valid) {
        std::cout << prompt;
        if (std::cin >> value) {
            valid = true;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
        }
    }
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

// Get string input from user
std::string TicketingMenu::getStringInput(const std::string& prompt) {
    std::string value;
    
    std::cout << prompt;
    std::getline(std::cin, value);
    
    return value;
}

// Select ticket type
TicketType TicketingMenu::selectTicketType() {
    std::cout << "Select ticket type:\n"
              << "1. VIP\n"
              << "2. Early Bird\n"
              << "3. General\n";
    
    int typeChoice = getIntInput("Enter choice: ");
    
    switch (typeChoice) {
        case 1: return TicketType::VIP;
        case 2: return TicketType::EARLY_BIRD;
        case 3: return TicketType::GENERAL;
        default:
            std::cout << "Invalid choice. Defaulting to General ticket type.\n";
            return TicketType::GENERAL;
    }
}

} // namespace TCMS
