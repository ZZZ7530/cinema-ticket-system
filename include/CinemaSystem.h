#ifndef CINEMA_SYSTEM_H
#define CINEMA_SYSTEM_H

#include "Movie.h"
#include "Showtime.h"
#include "Ticket.h"

#include <memory>
#include <vector>

class CinemaSystem {
private:
    std::vector<Movie> movies;
    std::vector<Showtime> showtimes;
    std::vector<std::unique_ptr<Ticket>> tickets;

public:
    CinemaSystem();

    const std::vector<Movie>& getMovies() const;
    const std::vector<Showtime>& getShowtimes() const;
    const std::vector<std::unique_ptr<Ticket>>& getTickets() const;
};

#endif
