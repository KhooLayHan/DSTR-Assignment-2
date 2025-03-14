// models/Spectator.cpp
#include "Spectator.hpp"

namespace TCMS {

Spectator::Spectator(const std::string& name, int age)
    : m_SpectatorId(UUID().toString()), m_Name(name), m_Age(age), m_Ticket(nullptr), m_EntryTime(0), m_ExitTime(0), m_InVenue(false) {}

Spectator::~Spectator() {
     // Destructor.  No need to delete m_Ticket here; TicketingSystem handles it.
     std::cout << "Spectator " << m_Name << " destroyed.\n";
}

std::string Spectator::getSpectatorId() const {
 return m_SpectatorId;
}

std::string Spectator::getName() const {
 return m_Name;
}

int Spectator::getAge() const{
 return m_Age;
}

Ticket* Spectator::getTicket() const {
 return m_Ticket;
}

void Spectator::setTicket(Ticket* t) {
 m_Ticket = t;
}

bool Spectator::isInVenue() const{
 return m_InVenue;
}

void Spectator::enterVenue() {
m_InVenue = true;
  m_EntryTime = std::time(nullptr); // Record entry time
}

void Spectator::exitVenue() {
 m_InVenue = false;
 m_ExitTime = std::time(nullptr); // Record exit time
}

std::time_t Spectator::getEntryTime() const{
     return m_EntryTime;
}
std::time_t Spectator::getExitTime() const{
 return m_ExitTime;
}

} // namespace TCMS