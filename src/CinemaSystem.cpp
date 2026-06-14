#include "CinemaSystem.h"

#include "FileManager.h"

CinemaSystem::CinemaSystem() = default;

void CinemaSystem::loadAllData() {
    loadWarnings.clear();
    movies = FileManager::loadMovies(loadWarnings);
    showtimes = FileManager::loadShowtimes(loadWarnings);
    tickets = FileManager::loadTickets(loadWarnings);
}

bool CinemaSystem::saveAllData() {
    saveWarnings.clear();
    const bool moviesSaved = FileManager::saveMovies(movies, saveWarnings);
    const bool showtimesSaved = FileManager::saveShowtimes(showtimes, saveWarnings);
    const bool ticketsSaved = FileManager::saveTickets(tickets, saveWarnings);
    return moviesSaved && showtimesSaved && ticketsSaved;
}

const std::vector<Movie>& CinemaSystem::getMovies() const {
    return movies;
}

const std::vector<Showtime>& CinemaSystem::getShowtimes() const {
    return showtimes;
}

const std::vector<std::unique_ptr<Ticket>>& CinemaSystem::getTickets() const {
    return tickets;
}

const std::vector<std::string>& CinemaSystem::getLoadWarnings() const {
    return loadWarnings;
}

const std::vector<std::string>& CinemaSystem::getSaveWarnings() const {
    return saveWarnings;
}

int CinemaSystem::getMovieCount() const {
    return static_cast<int>(movies.size());
}

int CinemaSystem::getShowtimeCount() const {
    return static_cast<int>(showtimes.size());
}

int CinemaSystem::getTicketCount() const {
    return static_cast<int>(tickets.size());
}
