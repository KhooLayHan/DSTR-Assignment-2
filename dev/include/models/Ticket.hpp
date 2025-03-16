// models/Ticket.hpp
#pragma once

#include <iostream>
#include <string>
#include "UUID.hpp"


namespace TCMS {

enum class TicketType { VIP, EARLY_BIRD, GENERAL };
enum class TicketStatus { AVAILABLE, SOLD, RESERVED, CHECKED_IN, CANCELLED };

class Ticket {
public:
    Ticket(TicketType type, double price, const std::string& seatNumber, const std::string& matchId);
    ~Ticket();

    std::string getTicketId() const;
    std::string getBuyerId() const;
    void setBuyerId(const std::string& buyerId);
    TicketType getTicketType() const;
    double getPrice() const;
    std::string getSeatNumber() const;
    TicketStatus getStatus() const;
    void setStatus(TicketStatus status);
    std::string getMatchId() const; // Get the match ID

	void markAsSold(); //
	void cancelTicket();
	void checkIn();

private:
    std::string m_TicketId;
    std::string m_BuyerId; // Can be empty initially
    TicketType m_TicketType;
    double m_Price;
    std::string m_SeatNumber;
    TicketStatus m_Status;
    std::string m_MatchId; // Add match_id
};

} // namespace TCMS