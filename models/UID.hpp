#pragma once

#include <iostream>
#include <string>

namespace TCMS
{
    enum class TCMS_UID {
        Player, 
        Match,
    };

    class UID {
    public:
        UID(TCMS_UID uid) {
            switch (uid)
            {
            case TCMS_UID::Player:
                m_PlayerId = generatePlayerUID();
                break;
            case TCMS_UID::Match:
                m_MatchId = generateMatchUID();
                break;
            }
        }

        std::string toPlayerString() {
            return std::to_string(m_PlayerId); 
        }
        
        std::string toMatchString() {
            return std::to_string(m_MatchId); 
        }
    private:
        TCMS_UID m_UID;

        int32_t m_PlayerId;
        int32_t m_MatchId;

        int32_t generatePlayerUID() {
            static int32_t player_id = 1;
            return player_id++;
        }
        
        int32_t generateMatchUID() {
            static int32_t match_id = 1;
            return match_id++;
        }
    };
} // namespace TCMS
