#include "Ticket.h"

#include <iostream>
#include <stdexcept>

Ticket::Ticket(const std::string& ticketId,
               const std::string& showtimeId,
               const std::string& movieTitle,
               const std::string& seatNo)
    : ticketId(ticketId), showtimeId(showtimeId), movieTitle(movieTitle), seatNo(seatNo) {}

std::string Ticket::getTicketId() const {
    return ticketId;
}

std::string Ticket::getShowtimeId() const {
    return showtimeId;
}

std::string Ticket::getMovieTitle() const {
    return movieTitle;
}

std::string Ticket::getSeatNo() const {
    return seatNo;
}

std::string Ticket::toFileString() const {
    return ticketId + "|" + showtimeId + "|" + movieTitle + "|" + seatNo + "|" +
           getTicketType() + "|" + std::to_string(calculatePrice());
}

void Ticket::display() const {
    std::cout << ticketId << " | " << movieTitle << " | " << seatNo << " | "
              << getTicketType() << " | NT$" << calculatePrice() << std::endl;
}

AdultTicket::AdultTicket(const std::string& ticketId,
                         const std::string& showtimeId,
                         const std::string& movieTitle,
                         const std::string& seatNo)
    : Ticket(ticketId, showtimeId, movieTitle, seatNo) {}

int AdultTicket::calculatePrice() const {
    return 320;
}

std::string AdultTicket::getTicketType() const {
    return "成人票";
}

StudentTicket::StudentTicket(const std::string& ticketId,
                             const std::string& showtimeId,
                             const std::string& movieTitle,
                             const std::string& seatNo)
    : Ticket(ticketId, showtimeId, movieTitle, seatNo) {}

int StudentTicket::calculatePrice() const {
    return 280;
}

std::string StudentTicket::getTicketType() const {
    return "學生票";
}

ChildTicket::ChildTicket(const std::string& ticketId,
                         const std::string& showtimeId,
                         const std::string& movieTitle,
                         const std::string& seatNo)
    : Ticket(ticketId, showtimeId, movieTitle, seatNo) {}

int ChildTicket::calculatePrice() const {
    return 220;
}

std::string ChildTicket::getTicketType() const {
    return "兒童票";
}

std::unique_ptr<Ticket> createTicketByType(const std::string& ticketId,
                                           const std::string& showtimeId,
                                           const std::string& movieTitle,
                                           const std::string& seatNo,
                                           const std::string& ticketType) {
    if (ticketType == "成人票") {
        return std::make_unique<AdultTicket>(ticketId, showtimeId, movieTitle, seatNo);
    }
    if (ticketType == "學生票") {
        return std::make_unique<StudentTicket>(ticketId, showtimeId, movieTitle, seatNo);
    }
    if (ticketType == "兒童票") {
        return std::make_unique<ChildTicket>(ticketId, showtimeId, movieTitle, seatNo);
    }

    throw std::invalid_argument("Unknown ticket type: " + ticketType);
}
