#include "./LinkedListNode.hpp"
#include "./DoublyLinkedListNode.hpp"
#include "./SinglyLinkedListNode.hpp"

#include "../models/Ticket.hpp" // Include necessary headers
#include "../models/Spectator.hpp"
#include "../PriorityQueue.hpp"

namespace TCMS {
    template class LinkedListNode<Ticket*, DoublyLinkedListNode<Ticket*>>;
    template class LinkedListNode<Spectator*, DoublyLinkedListNode<Spectator*>>;
    template class LinkedListNode<PriorityQueue<Spectator*>::PriorityItem, DoublyLinkedListNode<PriorityQueue<Spectator*>::PriorityItem>>;
    template class LinkedListNode<Spectator*, SinglyLinkedListNode<Spectator*>>;
} // namespace TCMS