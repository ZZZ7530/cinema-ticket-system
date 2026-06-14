#ifndef TICKET_H
#define TICKET_H

#include <memory>
#include <string>

class Ticket {
protected:
    std::string ticketId;
    std::string showtimeId;
    std::string movieTitle;
    std::string seatNo;

public:
    Ticket(const std::string& ticketId,
           const std::string& showtimeId,
           const std::string& movieTitle,
           const std::string& seatNo);
    virtual ~Ticket() = default;

    std::string getTicketId() const;
    std::string getShowtimeId() const;
    std::string getMovieTitle() const;
    std::string getSeatNo() const;

    virtual int calculatePrice() const = 0;
    virtual std::string getTicketType() const = 0;

    std::string toFileString() const;
    void display() const;
};

class AdultTicket : public Ticket {
public:
    AdultTicket(const std::string& ticketId,
                const std::string& showtimeId,
                const std::string& movieTitle,
                const std::string& seatNo);

    int calculatePrice() const override;
    std::string getTicketType() const override;
};

class StudentTicket : public Ticket {
public:
    StudentTicket(const std::string& ticketId,
                  const std::string& showtimeId,
                  const std::string& movieTitle,
                  const std::string& seatNo);

    int calculatePrice() const override;
    std::string getTicketType() const override;
};

class ChildTicket : public Ticket {
public:
    ChildTicket(const std::string& ticketId,
                const std::string& showtimeId,
                const std::string& movieTitle,
                const std::string& seatNo);

    int calculatePrice() const override;
    std::string getTicketType() const override;
};

std::unique_ptr<Ticket> createTicketByType(const std::string& ticketId,
                                           const std::string& showtimeId,
                                           const std::string& movieTitle,
                                           const std::string& seatNo,
                                           const std::string& ticketType);

#endif
