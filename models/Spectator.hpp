// models/Spectator.hpp
#pragma once

#include <string>
#include <ctime> // For timestamps
#include "UUID.hpp"
#include "Ticket.hpp" // Include Ticket.hpp

namespace TCMS {

class Ticket;  // Forward declaration (still needed, even though we include Ticket.hpp)

class Spectator {
public:
    Spectator(const std::string& name, int age); // Constructor
    ~Spectator(); // Destructor

    std::string getSpectatorId() const;
    std::string getName() const;
    int getAge() const;
	Ticket* getTicket() const; // Get the spectator's ticket
    bool isInVenue() const;
    void setTicket(Ticket* t);
    void enterVenue();
    void exitVenue();
    std::time_t getEntryTime() const;
    std::time_t getExitTime() const;


private:
    std::string m_SpectatorId;
    std::string m_Name;
    int32_t m_Age;
    Ticket* m_Ticket; // Pointer to the Ticket object
    std::time_t m_EntryTime; // Timestamp for entry
    std::time_t m_ExitTime;  // Timestamp for exit
    bool m_InVenue;       // Flag to track if spectator is in the venue
};

} // namespace TCMS