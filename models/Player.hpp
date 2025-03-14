// models/Player.hpp
#pragma once 

#include <string>

namespace TCMS
{
    // Just a temporary template 
    class Player {
    public:
        void registerPlayer() {

        }

        void withdraw() {

        }

    private:
        std::string m_PlayerId;

        std::string m_Name;
        int32_t m_Age;
        
        std::string m_MatchHistory;
        bool m_HasWithdrawn;
    };    
} // namespace TCMS
