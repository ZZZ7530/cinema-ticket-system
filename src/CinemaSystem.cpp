#include "CinemaSystem.h"

CinemaSystem::CinemaSystem() = default;

const std::vector<Movie>& CinemaSystem::getMovies() const {
    return movies;
}

const std::vector<Showtime>& CinemaSystem::getShowtimes() const {
    return showtimes;
}

const std::vector<std::unique_ptr<Ticket>>& CinemaSystem::getTickets() const {
    return tickets;
}
