#pragma once 

#include <string>

namespace TCMS
{
    // Just a temporary template 
    class Spectator {
    public:
        void buyTicket() {
            
        }

        void enterVenue() {

        }

        void exitVenue() {

        }
    private:
        std::string m_SpectatorId;
        std::string m_Name;
        int32_t m_Age;    
    };    
} // namespace TCMS
