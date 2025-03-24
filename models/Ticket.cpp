#include "./Ticket.hpp"

namespace TCMS {
    Ticket::Ticket(TicketType type, double price, const std::string& seatNumber, const std::string& matchId) :
        m_TicketId(UUID().toString()), m_BuyerId(""), m_TicketType(type), m_Price(price),
        m_SeatNumber(seatNumber), m_Status(TicketStatus::AVAILABLE), m_MatchId(matchId) {}

    Ticket::~Ticket() {
        // Destructor.  No need to do anything here; TicketingSystem handles deletion.
        // std::cout << "Ticket " << m_TicketId << " destroyed.\n";
    }

    std::string Ticket::getTicketId() const {
        return m_TicketId;
    }

    std::string Ticket::getBuyerId() const {
        return m_BuyerId;
    }

    void Ticket::setBuyerId(const std::string& buyerId){
        m_BuyerId = buyerId;
    }

    TicketType Ticket::getTicketType() const {
        return m_TicketType;
    }

    double Ticket::getPrice() const {
        return m_Price;
    }

    std::string Ticket::getSeatNumber() const {
        return m_SeatNumber;
    }

    TicketStatus Ticket::getStatus() const {
        return m_Status;
    }

    void Ticket::setStatus(TicketStatus status){
        m_Status = status;
    }
    std::string Ticket::getMatchId() const{
        return m_MatchId;
    }

    void Ticket::markAsSold() {
        m_Status = TicketStatus::SOLD;
    }

    void Ticket::cancelTicket() {
        m_Status = TicketStatus::CANCELLED;
    }

    void Ticket::checkIn(){
        m_Status = TicketStatus::CHECKED_IN;
    }
} // namespace TCMS