#include "./Spectator.hpp"

namespace TCMS {
    Spectator::Spectator(const std::string& name, int age, int priority)
        : m_SpectatorId(UUID().toString()), 
        m_Name(name), 
        m_Age(age), 
        m_Ticket(nullptr), 
        m_EntryTime(0), 
        m_ExitTime(0), 
        m_InVenue(false),
        m_Priority(priority),
        m_SectionId("") {}

    Spectator::~Spectator() {
        // std::cout << "Spectator " << m_Name << " destroyed.\n";
    }

    std::string Spectator::getSpectatorId() const {
        return m_SpectatorId;
    }

    std::string Spectator::getName() const {
        return m_Name;
    }

    int Spectator::getAge() const {
        return m_Age;
    }

    Ticket* Spectator::getTicket() const {
        return m_Ticket;
    }

    void Spectator::setTicket(Ticket* t) {
        m_Ticket = t;
    }

    bool Spectator::isInVenue() const {
        return m_InVenue;
    }

    void Spectator::enterVenue() {
        m_InVenue = true;
        m_EntryTime = std::time(nullptr);
    }

    void Spectator::exitVenue() {
        m_InVenue = false;
        m_ExitTime = std::time(nullptr);
    }

    std::time_t Spectator::getEntryTime() const {
        return m_EntryTime;
    }

    std::time_t Spectator::getExitTime() const {
        return m_ExitTime;
    }

    int Spectator::getPriority() const {
        return m_Priority;
    }

    std::string Spectator::getSection() const {
        return m_SectionId;
    }

    void Spectator::setPriority(int priority) {
        m_Priority = priority;
    }

    void Spectator::setSection(const std::string& sectionId) {
        m_SectionId = sectionId;
    }
} // namespace TCMS