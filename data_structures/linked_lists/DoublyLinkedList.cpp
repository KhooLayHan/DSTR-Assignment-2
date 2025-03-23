#include "./DoublyLinkedList.hpp"

#include "../models/Ticket.hpp" // Include necessary headers
#include "../models/Spectator.hpp"
#include "../PriorityQueue.hpp"

namespace TCMS {
    template class DoublyLinkedList<Ticket*>; // Instantiate for Ticket*
    template class DoublyLinkedList<Spectator*>; // Instantiate for Spectator*
    template class DoublyLinkedList<PriorityQueue<Spectator*>::PriorityItem>;
} // namespace TCMS