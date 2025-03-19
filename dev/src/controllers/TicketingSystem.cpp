// // #include "../../include/controllers/TicketingSystem.hpp"

// // controllers/TicketingSystem.cpp
// #include "../../include/controllers/TicketingSystem.hpp"
// #include <iostream>

// namespace TCMS {
//     // 1. TicketingSystem() (Constructor)
//     TicketingSystem::TicketingSystem() {
//         // Initialization, if needed.  At this point, the lists and queues
//         // are already initialized by their default constructors.
//         // No explicit initialization of member variables is strictly necessary here,
//         // as they are default-constructed.
//     }

//     // 2. ~TicketingSystem() (Destructor)
//     TicketingSystem::~TicketingSystem() {
//         // VERY IMPORTANT:  Prevent memory leaks!
//         // 1. Delete Ticket objects in both lists.
//         // 2. Delete Spectator objects in the queues (and those created during buying).

//         // Clear available tickets, deleting Ticket objects
//         while (!available_tickets.isEmpty()) {
//             Ticket* ticket = available_tickets.getFirst();
//             available_tickets.removeBegin();
//             delete ticket;
//         }

//         // Clear sold tickets, deleting Ticket objects
//         while (!sold_tickets.isEmpty()) {
//             Ticket* ticket = sold_tickets.getFirst();
//             sold_tickets.removeBegin();
//             delete ticket;
//         }

//         // Clear priority queue, deleting Spectator objects
//         while (!ticket_priority_queue.isEmpty()) {
//             Spectator* spectator = ticket_priority_queue.dequeue();
//             delete spectator;  // Assuming you dynamically allocate Spectators
//         }

//         //Clear entry_queue , deleting Spectator objects
//         while(!entry_queue.isEmpty()){
//             Spectator* spectator = entry_queue.dequeue();
//             delete spectator;
//         }
//         std::cout << "TicketingSystem destroyed.\n";
//     }

//     // 3. addTicket(Ticket* ticket)
//     void TicketingSystem::addTicket(Ticket* ticket) {
//         available_tickets.insertEnd(ticket);  // Add to the end of available tickets.
//     }

//     // 4. addBuyerToQueue(Spectator* spectator, TicketType type)
//     void TicketingSystem::addBuyerToQueue(Spectator* spectator, TicketType type) {
//         int32_t priority;
//         switch (type) {
//             case TicketType::VIP:
//                 priority = 3; // Highest priority
//                 break;
//             case TicketType::EARLY_BIRD:
//                 priority = 2;
//                 break;
//             case TicketType::GENERAL:
//                 priority = 1; // Lowest priority
//                 break;
//             default:
//                 priority = 0; // Should not happen, but handle for safety.
//         }
//         ticket_priority_queue.enqueue(spectator, priority);
//     }

//     // 5. findAvailableTicket(TicketType type)
//     Ticket* TicketingSystem::findAvailableTicket(TicketType type) {
//         DoublyLinkedListNode<Ticket*>* current = static_cast<DoublyLinkedListNode<Ticket*>*>(available_tickets.getHeadBase());
//         while (current != nullptr) {
//             Ticket* ticket = current->getData();
//             if (ticket->getTicketType() == type && ticket->getStatus() == TicketStatus::AVAILABLE) {
//                 return ticket;
//             }
//             current = current->getNext();
//         }
//         return nullptr; // No matching ticket found.
//     }

//     // 6. sellTickets()
//     void TicketingSystem::sellTickets() {
//         while (!ticket_priority_queue.isEmpty()) {
//             Spectator* buyer = ticket_priority_queue.dequeue();
//             TicketType desiredType;

//             // For demonstration, get ticket type from a new method in Spectator.
//             if(buyer->getAge() >= 60){
//                 desiredType = TicketType::VIP;
//             } else if (buyer->getAge() >= 40 && buyer->getAge() < 60){
//                 desiredType = TicketType::EARLY_BIRD;
//             } else {
//                 desiredType = TicketType::GENERAL;
//             }

//             Ticket* ticket = findAvailableTicket(desiredType);

//             if (ticket) {
//                 // Sell the ticket
//                 ticket->markAsSold();
//                 ticket->setBuyerId(buyer->getSpectatorId());
//                 buyer->setTicket(ticket);  // Associate the ticket with the spectator.

//                 // Move the ticket from available_tickets to sold_tickets
//                 available_tickets.remove(ticket);
//                 sold_tickets.insertEnd(ticket);

//                 // Add the buyer to the entry queue.
//                 entry_queue.enqueue(buyer);
//                 std::cout << "Ticket sold to " << buyer->getName() << " for seat " << ticket->getSeatNumber() << std::endl;

//             } else {
//                 std::cout << "No available " << (desiredType == TicketType::VIP ? "VIP" :
//                                                 (desiredType == TicketType::EARLY_BIRD ? "Early Bird" : "General"))
//                         << " tickets for " << buyer->getName() << std::endl;
//                 delete buyer; // Important: Delete the spectator if no ticket is sold.
//             }
//         }
//     }

//     // 7. cancelTicket(const std::string& ticket_id)
//     void TicketingSystem::cancelTicket(const std::string& ticket_id) {
//         // Search in sold_tickets first
//         DoublyLinkedListNode<Ticket*>* current = static_cast<DoublyLinkedListNode<Ticket*>*>(sold_tickets.getHeadBase());
//         while (current != nullptr) {
//             if (current->getData()->getTicketId() == ticket_id) {
//                 Ticket* ticket = current->getData();

//                 // Check if the spectator has checked in. Prevent the cancel
//                 if (ticket->getStatus() == TicketStatus::CHECKED_IN){
//                     std::cout << "Cannot cancel the ticket, Because the spectator had checked in." << std::endl;
//                     return;
//                 }
                
//                 // Remove from sold_tickets
//                 sold_tickets.remove(ticket);

//                 // Reset ticket status and buyer ID.
//                 ticket->setStatus(TicketStatus::AVAILABLE);
//                 ticket->setBuyerId("");

//                 // Move back to available_tickets
//                 available_tickets.insertEnd(ticket);

//                 // Find and remove the Spectator from entry_queue if they are there.
//                 //  Since we don't have a direct remove by data in Queue, it's tricky.
//                 //  We can create a temporary queue.
//                 Queue<Spectator*> tempQueue;
//                 while(!entry_queue.isEmpty()){
//                     Spectator* tempSpectator = entry_queue.dequeue();
//                     if(tempSpectator->getTicket() != nullptr && tempSpectator->getTicket()->getTicketId() == ticket_id){
//                         //clear Spectator's Ticket
//                         tempSpectator->setTicket(nullptr);
//                         delete tempSpectator; // Delete spectator if ticket is cancelled
//                     } else {
//                         tempQueue.enqueue(tempSpectator);
//                     }
//                 }
//                 // Copy back to entry_queue
//                 while(!tempQueue.isEmpty()){
//                     entry_queue.enqueue(tempQueue.dequeue());
//                 }
                
//                 std::cout << "Ticket " << ticket_id << " cancelled.\n";
//                 return;
//             }
//             current = current->getNext();
//         }
//         std::cout << "Ticket " << ticket_id << " not found or cannot be cancelled.\n";
//     }

//     // 8. checkInSpectator(Spectator* spectator)
//     void TicketingSystem::checkInSpectator(Spectator* spectator) {
//         if(spectator->getTicket() != nullptr){
//             if (spectator->getTicket()->getStatus() == TicketStatus::SOLD) {
//                 spectator->getTicket()->setStatus(TicketStatus::CHECKED_IN);
//                 spectator->enterVenue();
//                 std::cout << "Spectator " << spectator->getName() << " checked in.\n";
//             } else {
//                 std::cout << "Spectator " << spectator->getName() << " cannot check in. Ticket status is not SOLD.\n";
//             }
//         } else {
//             std::cout << "Spectator " << spectator->getName() << " does not have a ticket. \n";
//         }
//     }

//     // 9. processEntryQueue()
//     void TicketingSystem::processEntryQueue() {
//         while (!entry_queue.isEmpty()) {
//             Spectator* spectator = entry_queue.dequeue();
//             checkInSpectator(spectator);
//             //  delete spectator; // Don't delete here
//             // We still need the spectator object for exit.
//         }
//     }

//     // 10. spectatorExit(Spectator* spectator)
//     void TicketingSystem::spectatorExit(Spectator* spectator){
//         if(spectator->isInVenue()){
//             spectator->exitVenue();
//             std::cout << "Spectator " << spectator->getName() << " has left the venue.\n";
//             // Find the ticket in sold_tickets and reset status
//             DoublyLinkedListNode<Ticket*>* currentTicket =  static_cast<DoublyLinkedListNode<Ticket*>*>(sold_tickets.getHeadBase());
//             while(currentTicket != nullptr){
//                 if(currentTicket->getData()->getBuyerId() == spectator->getSpectatorId()){
//                     currentTicket->getData()->setStatus(TicketStatus::AVAILABLE);
//                     currentTicket->getData()->setBuyerId("");
//                     break;
//                 }
//                     currentTicket = currentTicket->getNext();
//             }
//             delete spectator; //Now we delete the spectator, after they have exit.
//         } else {
//             std::cout << "Spectator " << spectator->getName() << " is not in the venue.\n";
//         }
//     }

//     // 11. getAvailableTicketsCount(TicketType type)
//     int TicketingSystem::getAvailableTicketsCount(TicketType type) {
//         int count = 0;
//         DoublyLinkedListNode<Ticket*>* current = static_cast<DoublyLinkedListNode<Ticket*>*>(available_tickets.getHeadBase());
//         while (current != nullptr) {
//             if (current->getData()->getTicketType() == type && current->getData()->getStatus() == TicketStatus::AVAILABLE) {
//                 count++;
//             }
//             current = current->getNext();
//         }
//         return count;
//     }

//     // 12. getTotalRevenue()
//     double TicketingSystem::getTotalRevenue() {
//         double revenue = 0;
//         DoublyLinkedListNode<Ticket*>* current = static_cast<DoublyLinkedListNode<Ticket*>*>(sold_tickets.getHeadBase());
//         while (current != nullptr) {
//             revenue += current->getData()->getPrice();
//             current = current->getNext();
//         }
//         return revenue;
//     }

//     // 13. displayAvailableTickets()
//     void TicketingSystem::displayAvailableTickets() {
//     std::cout << "Available Tickets:\n";
//     DoublyLinkedListNode<Ticket*>* current = static_cast<DoublyLinkedListNode<Ticket*>*>(available_tickets.getHeadBase());
//     if (current == nullptr) {
//         std::cout << "No tickets currently available.\n";
//         return;
//     }
//     while (current != nullptr) {
//         Ticket* ticket = current->getData();
//         if(ticket->getStatus() == TicketStatus::AVAILABLE){
//             std::cout << "Ticket ID: " << ticket->getTicketId()
//                     << ", Type: " << (ticket->getTicketType() == TicketType::VIP ? "VIP" :
//                                         (ticket->getTicketType() == TicketType::EARLY_BIRD ? "Early Bird" : "General"))
//                     << ", Price: " << ticket->getPrice()
//                     << ", Seat: " << ticket->getSeatNumber() << "\n";
//         }
//         current = current->getNext();
//     }
//     }

//     // 14. displaySoldTickets()
//     void TicketingSystem::displaySoldTickets() {
//         std::cout << "Sold Tickets:\n";
//         DoublyLinkedListNode<Ticket*>* current = static_cast<DoublyLinkedListNode<Ticket*>*>(sold_tickets.getHeadBase());
//         if(current == nullptr){
//             std::cout << "No tickets have been sold yet.\n";
//             return;
//         }
//         while (current != nullptr) {
//             Ticket* ticket = current->getData();
//             std::cout << "Ticket ID: " << ticket->getTicketId()
//                     << ", Type: " << (ticket->getTicketType() == TicketType::VIP ? "VIP" :
//                                         (ticket->getTicketType() == TicketType::EARLY_BIRD ? "Early Bird" : "General"))
//                     << ", Price: " << ticket->getPrice()
//                     << ", Seat: " << ticket->getSeatNumber()
//                     << ", Buyer ID: " << ticket->getBuyerId() << "\n";
//             current = current->getNext();
//         }
//     }
// } // namespace TCMS