// #include "../../../include/data_structures/linked_lists/DoublyLinkedList.hpp"

#include "DoublyLinkedList.hpp"
#include "Ticket.hpp" // Include necessary headers
#include "Spectator.hpp"
#include "PriorityQueue.hpp"

namespace TCMS {
    template class DoublyLinkedList<Ticket*>; // Instantiate for Ticket*
    template class DoublyLinkedList<Spectator*>; // Instantiate for Spectator*
    template class DoublyLinkedList<PriorityQueue<Spectator*>::PriorityItem>;
}

 // namespace TCMS