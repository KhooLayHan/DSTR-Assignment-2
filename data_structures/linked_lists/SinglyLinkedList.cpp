#include "./SinglyLinkedList.hpp"
#include "../models/Spectator.hpp"
#include "../Queue.hpp"

namespace TCMS {
    template class SinglyLinkedList<Spectator*>; // Instantiate for Spectator*
}