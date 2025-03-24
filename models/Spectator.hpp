#pragma once

#include <string>
#include <iostream>
#include <ctime> // For timestamps

#include "../core/UUID.hpp"
#include "./Ticket.hpp" 

namespace TCMS {
    class Ticket;  // Forward declaration
    
    class Spectator {
    public:
        /**
         * @brief Constructs a new spectator.
         * 
         * @param name The spectator's name.
         * @param age The spectator's age.
         * @param priority The spectator's priority level (3=VIP, 2=Early Bird, 1=General).
         */
        Spectator(const std::string& name, int age, int priority = 1);
    
        /**
         * @brief Destructor.
         */
        ~Spectator();
    
        // Getters
        std::string getSpectatorId() const;
        std::string getName() const;
        int getAge() const;
        Ticket* getTicket() const;
        bool isInVenue() const;
        std::time_t getEntryTime() const;
        std::time_t getExitTime() const;
        int getPriority() const;
        std::string getSection() const;
        
        // Setters
        void setTicket(Ticket* t);
        void setPriority(int priority);
        void setSection(const std::string& sectionId);
        
        // Actions
        void enterVenue();
        void exitVenue();
    
    private:
        std::string m_SpectatorId;    ///< Unique identifier
        std::string m_Name;           ///< Spectator's name
        int32_t m_Age;                ///< Spectator's age
        Ticket* m_Ticket;             ///< Pointer to the Ticket object
        std::time_t m_EntryTime;      ///< Timestamp for entry
        std::time_t m_ExitTime;       ///< Timestamp for exit
        bool m_InVenue;               ///< Flag to track if spectator is in the venue
        int m_Priority;               ///< Priority level (3=VIP, 2=Early Bird, 1=General)
        std::string m_SectionId;      ///< ID of the assigned venue section
    };
} // namespace TCMS