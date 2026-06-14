#ifndef CINEMA_SYSTEM_H
#define CINEMA_SYSTEM_H

#include "Movie.h"
#include "Showtime.h"
#include "Ticket.h"

#include <map>
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

    std::string generateNextMovieId() const;
    std::string generateNextShowtimeId() const;
    std::string generateNextTicketId() const;

public:
    CinemaSystem();

    void loadAllData();
    bool saveAllData();

    const std::vector<Movie>& getMovies() const;
    const std::vector<Showtime>& getShowtimes() const;
    const std::vector<std::unique_ptr<Ticket>>& getTickets() const;
    const std::vector<std::string>& getLoadWarnings() const;
    const std::vector<std::string>& getSaveWarnings() const;

    Movie addMovie(const std::string& title, const std::string& genre, int duration);
    std::vector<Movie> searchMovies(const std::string& keyword) const;
    const Movie* findMovieById(const std::string& movieId) const;
    bool deleteMovie(const std::string& movieId, std::string& message);
    bool hasShowtimesForMovie(const std::string& movieId) const;

    Showtime addShowtime(const std::string& movieId,
                         const std::string& date,
                         const std::string& time,
                         const std::string& hall,
                         int rows,
                         int cols);
    std::vector<Showtime> searchShowtimesByMovie(const std::string& keyword) const;
    std::string getMovieTitleById(const std::string& movieId) const;
    const Showtime* findShowtimeById(const std::string& showtimeId) const;
    Showtime* findShowtimeById(const std::string& showtimeId);

    Ticket* purchaseTicket(const std::string& showtimeId,
                           const std::string& seatNo,
                           const std::string& ticketType,
                           std::string& message);
    bool refundTicket(const std::string& ticketId, std::string& message);
    const Ticket* findTicketById(const std::string& ticketId) const;
    int calculateTotalRevenue() const;
    std::map<std::string, int> countTicketsByMovie() const;
    std::map<std::string, int> countTicketsByType() const;
    std::map<std::string, int> calculateRevenueByTicketType() const;

    int getMovieCount() const;
    int getShowtimeCount() const;
    int getTicketCount() const;
};

#endif
