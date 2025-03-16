// #include "../../../include/data_structures/linked_lists/DoublyLinkedListNode.hpp"

#include "DoublyLinkedListNode.hpp"
#include "../models/Ticket.hpp"
#include "../models/Spectator.hpp"
#include "PriorityQueue.hpp"

namespace TCMS {
    // Explicit template instantiations (REQUIRED)
    template class DoublyLinkedListNode<Ticket*>;
    template class DoublyLinkedListNode<Spectator*>;
    template class DoublyLinkedListNode<PriorityQueue<Spectator*>::PriorityItem>;
} // namespace TCMS