#include "./LinkedList.hpp"
#include "./DoublyLinkedListNode.hpp"

#include "../models/Ticket.hpp" // Include necessary headers
#include "../models/Spectator.hpp"
#include "../PriorityQueue.hpp"

namespace TCMS {
    template class LinkedList<Ticket*, DoublyLinkedListNode<Ticket*>>;
    template class LinkedList<Spectator*, DoublyLinkedListNode<Spectator*>>;
    template class LinkedList<PriorityQueue<Spectator*>::PriorityItem, DoublyLinkedListNode<PriorityQueue<Spectator*>::PriorityItem>>;
    template class LinkedList<Spectator*, SinglyLinkedListNode<Spectator*>>;
} // namespace TCMS