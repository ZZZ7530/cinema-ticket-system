#ifndef CINEMA_SYSTEM_H
#define CINEMA_SYSTEM_H

#include "Movie.h"
#include "Showtime.h"
#include "Ticket.h"

#include <memory>
#include <string>
#include <vector>

class CinemaSystem {
private:
    std::vector<Movie> movies;
    std::vector<Showtime> showtimes;
    std::vector<std::unique_ptr<Ticket>> tickets;
    std::vector<std::string> loadWarnings;
    std::vector<std::string> saveWarnings;

public:
    CinemaSystem();

    void loadAllData();
    bool saveAllData();

    const std::vector<Movie>& getMovies() const;
    const std::vector<Showtime>& getShowtimes() const;
    const std::vector<std::unique_ptr<Ticket>>& getTickets() const;
    const std::vector<std::string>& getLoadWarnings() const;
    const std::vector<std::string>& getSaveWarnings() const;

    int getMovieCount() const;
    int getShowtimeCount() const;
    int getTicketCount() const;
};

#endif
