// controllers/TicketingSystem.cpp
#include "../controllers/TicketingSystem.hpp"
#include <iostream>
#include <algorithm> // For std::max

namespace TCMS {

// Constructor
TicketingSystem::TicketingSystem() {
    // Initialize venue sections with default values
    setupVenueSections();
}

// Destructor
TicketingSystem::~TicketingSystem() {
    // Clean up available tickets
    while (!available_tickets.isEmpty()) {
        Ticket* ticket = available_tickets.getFirst();
        available_tickets.removeBegin();
        delete ticket;
    }

    // Clean up sold tickets
    while (!sold_tickets.isEmpty()) {
        Ticket* ticket = sold_tickets.getFirst();
        sold_tickets.removeBegin();
        delete ticket;
    }

    // Clean up priority queue
    while (!ticket_priority_queue.isEmpty()) {
        Spectator* spectator = ticket_priority_queue.dequeue();
        delete spectator;
    }

    // Clean up entry queue
    while (!entry_queue.isEmpty()) {
        Spectator* spectator = entry_queue.dequeue();
        delete spectator;
    }
    
    // Clean up venue sections
    while (!venue_sections.isEmpty()) {
        VenueSection* section = venue_sections.dequeue();
        delete section;
    }

    std::cout << "TicketingSystem destroyed.\n";
}

// Setup venue sections with specified number and capacity
void TicketingSystem::setupVenueSections(int numSections, int sectionCapacity) {
    // Clear existing sections if any
    while (!venue_sections.isEmpty()) {
        VenueSection* section = venue_sections.dequeue();
        delete section;
    }
    
    // Create venue sections with the provided capacity
    for (int i = 0; i < numSections; i++) {
        std::string sectionName = "Section " + std::string(1, 'A' + i);
        VenueSection* section = new VenueSection(sectionName, sectionCapacity);
        venue_sections.enqueue(section);
    }
}

// Add a ticket to available tickets
void TicketingSystem::addTicket(Ticket* ticket) {
    available_tickets.insertEnd(ticket);
}

// Add a buyer to the priority queue based on ticket type
void TicketingSystem::addBuyerToQueue(Spectator* spectator, TicketType type) {
    int32_t priority;
    
    // Set priority based on ticket type
    switch (type) {
        case TicketType::VIP:
            priority = 3; // Highest priority
            spectator->setPriority(3);
            break;
        case TicketType::EARLY_BIRD:
            priority = 2;
            spectator->setPriority(2);
            break;
        case TicketType::GENERAL:
            priority = 1; // Lowest priority
            spectator->setPriority(1);
            break;
        default:
            priority = 0; // Should not happen, but handle for safety
            spectator->setPriority(0);
    }
    
    ticket_priority_queue.enqueue(spectator, priority);
}

// Find an available ticket of the specified type
Ticket* TicketingSystem::findAvailableTicket(TicketType type) {
    DoublyLinkedListNode<Ticket*>* current = static_cast<DoublyLinkedListNode<Ticket*>*>(available_tickets.getHeadBase());
    
    while (current != nullptr) {
        Ticket* ticket = current->getData();
        if (ticket->getTicketType() == type && ticket->getStatus() == TicketStatus::AVAILABLE) {
            return ticket;
        }
        current = current->getNext();
    }
    
    return nullptr; // No matching ticket found
}

// Sell tickets to buyers in the priority queue
void TicketingSystem::sellTickets() {
    std::cout << "\n=== Processing Ticket Sales ===\n";
    
    while (!ticket_priority_queue.isEmpty()) {
        Spectator* buyer = ticket_priority_queue.dequeue();
        TicketType desiredType;
        
        // Determine ticket type based on priority
        int buyerPriority = buyer->getPriority();
        if (buyerPriority == 3) {
            desiredType = TicketType::VIP;
        } else if (buyerPriority == 2) {
            desiredType = TicketType::EARLY_BIRD;
        } else {
            desiredType = TicketType::GENERAL;
        }
        
        // Find an available ticket of the desired type
        Ticket* ticket = findAvailableTicket(desiredType);
        
        if (ticket) {
            // Sell the ticket
            ticket->markAsSold();
            ticket->setBuyerId(buyer->getSpectatorId());
            buyer->setTicket(ticket);
            
            // Move ticket from available to sold list
            available_tickets.remove(ticket);
            sold_tickets.insertEnd(ticket);
            
            // Add buyer to entry queue
            entry_queue.enqueue(buyer);
            
            std::cout << "Ticket sold to " << buyer->getName() 
                      << " (" << (desiredType == TicketType::VIP ? "VIP" : 
                                 (desiredType == TicketType::EARLY_BIRD ? "Early Bird" : "General"))
                      << ") for seat " << ticket->getSeatNumber() 
                      << " at price $" << ticket->getPrice() << std::endl;
        } else {
            // Handle case where no ticket of desired type is available
            std::cout << "No available " << (desiredType == TicketType::VIP ? "VIP" :
                                           (desiredType == TicketType::EARLY_BIRD ? "Early Bird" : "General"))
                      << " tickets for " << buyer->getName() << ". Trying alternative ticket types..." << std::endl;
            
            // Try to find any available ticket, starting from higher types
            if (desiredType != TicketType::VIP) {
                ticket = findAvailableTicket(TicketType::VIP);
            }
            
            if (!ticket && desiredType != TicketType::EARLY_BIRD) {
                ticket = findAvailableTicket(TicketType::EARLY_BIRD);
            }
            
            if (!ticket && desiredType != TicketType::GENERAL) {
                ticket = findAvailableTicket(TicketType::GENERAL);
            }
            
            if (ticket) {
                // Sell the alternative ticket
                ticket->markAsSold();
                ticket->setBuyerId(buyer->getSpectatorId());
                buyer->setTicket(ticket);
                
                // Move ticket from available to sold list
                available_tickets.remove(ticket);
                sold_tickets.insertEnd(ticket);
                
                // Add buyer to entry queue
                entry_queue.enqueue(buyer);
                
                std::cout << "Alternative " << (ticket->getTicketType() == TicketType::VIP ? "VIP" :
                                              (ticket->getTicketType() == TicketType::EARLY_BIRD ? "Early Bird" : "General"))
                          << " ticket sold to " << buyer->getName() 
                          << " for seat " << ticket->getSeatNumber()
                          << " at price $" << ticket->getPrice() << std::endl;
            } else {
                std::cout << "No tickets available for " << buyer->getName() << ". Customer turned away." << std::endl;
                delete buyer; // Delete the spectator if no ticket is sold
            }
        }
    }
    
    std::cout << "=== Ticket Sales Processing Complete ===\n";
}

// Cancel a ticket by ID
void TicketingSystem::cancelTicket(const std::string& ticket_id) {
    // Search for the ticket in sold tickets
    DoublyLinkedListNode<Ticket*>* current = static_cast<DoublyLinkedListNode<Ticket*>*>(sold_tickets.getHeadBase());
    
    while (current != nullptr) {
        if (current->getData()->getTicketId() == ticket_id) {
            Ticket* ticket = current->getData();
            
            // Prevent cancellation if the spectator has already checked in
            if (ticket->getStatus() == TicketStatus::CHECKED_IN) {
                std::cout << "Cannot cancel ticket " << ticket_id 
                          << ": Spectator has already checked in." << std::endl;
                return;
            }
            
            // Remove ticket from sold tickets
            std::string buyerId = ticket->getBuyerId();
            sold_tickets.remove(ticket);
            
            // Reset ticket status and buyer ID
            ticket->setStatus(TicketStatus::AVAILABLE);
            ticket->setBuyerId("");
            
            // Move back to available tickets
            available_tickets.insertEnd(ticket);
            
            // Find and remove the spectator from entry queue if they are there
            Queue<Spectator*> tempQueue;
            while (!entry_queue.isEmpty()) {
                Spectator* tempSpectator = entry_queue.dequeue();
                if (tempSpectator->getTicket() != nullptr && 
                    tempSpectator->getTicket()->getTicketId() == ticket_id) {
                    // Clear spectator's ticket
                    tempSpectator->setTicket(nullptr);
                    delete tempSpectator; // Delete spectator if ticket is cancelled
                } else {
                    tempQueue.enqueue(tempSpectator);
                }
            }
            
            // Restore entry queue
            while (!tempQueue.isEmpty()) {
                entry_queue.enqueue(tempQueue.dequeue());
            }
            
            std::cout << "Ticket " << ticket_id << " successfully cancelled." << std::endl;
            return;
        }
        current = current->getNext();
    }
    
    std::cout << "Ticket " << ticket_id << " not found or cannot be cancelled." << std::endl;
}

// Check in a spectator
void TicketingSystem::checkInSpectator(Spectator* spectator) {
    if (spectator->getTicket() != nullptr) {
        if (spectator->getTicket()->getStatus() == TicketStatus::SOLD) {
            spectator->getTicket()->setStatus(TicketStatus::CHECKED_IN);
            spectator->enterVenue();
            
            // Assign spectator to a venue section
            assignSectionToSpectator(spectator);
            
            std::cout << "Spectator " << spectator->getName() << " checked in and assigned to "
                      << spectator->getSection() << "." << std::endl;
        } else {
            std::cout << "Spectator " << spectator->getName() 
                      << " cannot check in. Ticket status is not SOLD." << std::endl;
        }
    } else {
        std::cout << "Spectator " << spectator->getName() << " does not have a ticket." << std::endl;
    }
}

// Process all spectators in the entry queue
void TicketingSystem::processEntryQueue() {
    std::cout << "\n=== Processing Entry Queue ===\n";
    
    if (entry_queue.isEmpty()) {
        std::cout << "No spectators in entry queue." << std::endl;
        return;
    }
    
    while (!entry_queue.isEmpty()) {
        Spectator* spectator = entry_queue.dequeue();
        checkInSpectator(spectator);
    }
    
    std::cout << "=== Entry Queue Processing Complete ===\n";
    
    // Display section status after processing entries
    displaySectionStatus();
}

// Handle spectator exit
void TicketingSystem::spectatorExit(Spectator* spectator) {
    if (spectator->isInVenue()) {
        // Get section ID before exiting
        std::string sectionId = spectator->getSection();
        
        // Update spectator status
        spectator->exitVenue();
        
        std::cout << "Spectator " << spectator->getName() << " has left the venue." << std::endl;
        
        // Update ticket status
        DoublyLinkedListNode<Ticket*>* currentTicket = static_cast<DoublyLinkedListNode<Ticket*>*>(sold_tickets.getHeadBase());
        while (currentTicket != nullptr) {
            if (currentTicket->getData()->getBuyerId() == spectator->getSpectatorId()) {
                currentTicket->getData()->setStatus(TicketStatus::AVAILABLE);
                currentTicket->getData()->setBuyerId("");
                break;
            }
            currentTicket = currentTicket->getNext();
        }
        
        delete spectator; // Now we delete the spectator, after they have exited
    } else {
        std::cout << "Spectator " << spectator->getName() << " is not in the venue." << std::endl;
    }
}

// Assign a spectator to a venue section
void TicketingSystem::assignSectionToSpectator(Spectator* spectator) {
    // For VIP ticket holders, try to find a section with fewer people first
    if (spectator->getTicket()->getTicketType() == TicketType::VIP) {
        VenueSection* leastOccupiedSection = findLeastOccupiedSection();
        if (leastOccupiedSection && !leastOccupiedSection->isFull()) {
            leastOccupiedSection->addSpectator(spectator);
            spectator->setSection(leastOccupiedSection->getName());
            return;
        }
    }
    
    // Otherwise use the circular queue to find a section with space
    // First, check if we have any sections
    if (venue_sections.isEmpty()) {
        std::cout << "Warning: No venue sections available! Spectator has no assigned section." << std::endl;
        return;
    }
    
    // Try each section until finding one with space
    size_t sectionCount = venue_sections.getSize();
    for (size_t i = 0; i < sectionCount; i++) {
        VenueSection* currentSection = venue_sections.peekFront();
        
        if (!currentSection->isFull()) {
            currentSection->addSpectator(spectator);
            spectator->setSection(currentSection->getName());
            
            // Rotate to the next section for the next assignment
            venue_sections.rotate();
            return;
        }
        
        // Try the next section
        venue_sections.rotate();
    }
    
    // If all sections are full, assign to the first section anyway (overload)
    VenueSection* firstSection = venue_sections.peekFront();
    firstSection->addSpectator(spectator); // Will be added even though it's full
    spectator->setSection(firstSection->getName());
    
    std::cout << "Warning: All sections are full. " << spectator->getName()
              << " assigned to " << firstSection->getName() << " (overcapacity)." << std::endl;
}

// Find the least occupied venue section
VenueSection* TicketingSystem::findLeastOccupiedSection() {
    if (venue_sections.isEmpty()) {
        return nullptr;
    }
    
    VenueSection* leastOccupiedSection = nullptr;
    size_t minOccupancy = SIZE_MAX;
    size_t totalSections = venue_sections.getSize();
    
    // Need to iterate through all sections
    for (size_t i = 0; i < totalSections; i++) {
        VenueSection* currentSection = venue_sections.peekFront();
        
        if (currentSection->getCurrentOccupancy() < minOccupancy) {
            minOccupancy = currentSection->getCurrentOccupancy();
            leastOccupiedSection = currentSection;
        }
        
        venue_sections.rotate();
    }
    
    return leastOccupiedSection;
}

// Try to balance the occupancy across sections
void TicketingSystem::balanceSections() {
    std::cout << "\n=== Section Balance Analysis ===\n";
    
    if (venue_sections.isEmpty()) {
        std::cout << "No venue sections configured." << std::endl;
        return;
    }
    
    size_t maxOccupancy = 0;
    size_t minOccupancy = SIZE_MAX;
    std::string maxSection;
    std::string minSection;
    size_t totalSections = venue_sections.getSize();
    
    // Find the sections with maximum and minimum occupancy
    for (size_t i = 0; i < totalSections; i++) {
        VenueSection* currentSection = venue_sections.peekFront();
        
        if (currentSection->getCurrentOccupancy() > maxOccupancy) {
            maxOccupancy = currentSection->getCurrentOccupancy();
            maxSection = currentSection->getName();
        }
        
        if (currentSection->getCurrentOccupancy() < minOccupancy) {
            minOccupancy = currentSection->getCurrentOccupancy();
            minSection = currentSection->getName();
        }
        
        venue_sections.rotate();
    }
    
    std::cout << "Maximum occupancy: " << maxSection << " with " << maxOccupancy << " spectators" << std::endl;
    std::cout << "Minimum occupancy: " << minSection << " with " << minOccupancy << " spectators" << std::endl;
    std::cout << "Occupancy difference: " << (maxOccupancy - minOccupancy) << " spectators" << std::endl;
    
    if (maxOccupancy - minOccupancy > 10) {
        std::cout << "Warning: Sections are significantly imbalanced." << std::endl;
    } else {
        std::cout << "Sections are reasonably balanced." << std::endl;
    }
}

// Display the status of all venue sections
void TicketingSystem::displaySectionStatus() {
    std::cout << "\n=== Venue Section Status ===\n";
    
    if (venue_sections.isEmpty()) {
        std::cout << "No venue sections configured." << std::endl;
        return;
    }
    
    size_t totalSections = venue_sections.getSize();
    for (size_t i = 0; i < totalSections; i++) {
        VenueSection* currentSection = venue_sections.peekFront();
        
        size_t occupancy = currentSection->getCurrentOccupancy();
        size_t capacity = currentSection->getCapacity();
        size_t percentage = (capacity > 0) ? (occupancy * 100 / capacity) : 0;
        
        std::cout << currentSection->getName() << ": "
                  << occupancy << "/"
                  << capacity << " spectators ("
                  << percentage
                  << "% full)" << std::endl;
        
        venue_sections.rotate();
    }
}

// Get the count of available tickets by type
int TicketingSystem::getAvailableTicketsCount(TicketType type) {
    int count = 0;
    DoublyLinkedListNode<Ticket*>* current = static_cast<DoublyLinkedListNode<Ticket*>*>(available_tickets.getHeadBase());
    
    while (current != nullptr) {
        if (current->getData()->getTicketType() == type && 
            current->getData()->getStatus() == TicketStatus::AVAILABLE) {
            count++;
        }
        current = current->getNext();
    }
    
    return count;
}

// Calculate total revenue from sold tickets
double TicketingSystem::getTotalRevenue() {
    double revenue = 0;
    DoublyLinkedListNode<Ticket*>* current = static_cast<DoublyLinkedListNode<Ticket*>*>(sold_tickets.getHeadBase());
    
    while (current != nullptr) {
        revenue += current->getData()->getPrice();
        current = current->getNext();
    }
    
    return revenue;
}

// Display all available tickets
void TicketingSystem::displayAvailableTickets() {
    std::cout << "Available Tickets:\n";
    DoublyLinkedListNode<Ticket*>* current = static_cast<DoublyLinkedListNode<Ticket*>*>(available_tickets.getHeadBase());
    
    if (current == nullptr) {
        std::cout << "No tickets currently available.\n";
        return;
    }
    
    while (current != nullptr) {
        Ticket* ticket = current->getData();
        if (ticket->getStatus() == TicketStatus::AVAILABLE) {
            std::cout << "Ticket ID: " << ticket->getTicketId()
                      << ", Type: " << (ticket->getTicketType() == TicketType::VIP ? "VIP" :
                                      (ticket->getTicketType() == TicketType::EARLY_BIRD ? "Early Bird" : "General"))
                      << ", Price: $" << ticket->getPrice()
                      << ", Seat: " << ticket->getSeatNumber() << "\n";
        }
        current = current->getNext();
    }
}

// Display all sold tickets
void TicketingSystem::displaySoldTickets() {
    std::cout << "Sold Tickets:\n";
    DoublyLinkedListNode<Ticket*>* current = static_cast<DoublyLinkedListNode<Ticket*>*>(sold_tickets.getHeadBase());
    
    if (current == nullptr) {
        std::cout << "No tickets have been sold yet.\n";
        return;
    }
    
    while (current != nullptr) {
        Ticket* ticket = current->getData();
        std::cout << "Ticket ID: " << ticket->getTicketId()
                  << ", Type: " << (ticket->getTicketType() == TicketType::VIP ? "VIP" :
                                  (ticket->getTicketType() == TicketType::EARLY_BIRD ? "Early Bird" : "General"))
                  << ", Price: $" << ticket->getPrice()
                  << ", Seat: " << ticket->getSeatNumber()
                  << ", Buyer ID: " << ticket->getBuyerId()
                  << ", Status: " << (ticket->getStatus() == TicketStatus::SOLD ? "Sold" : "Checked In") << "\n";
        current = current->getNext();
    }
}

} // namespace TCMS