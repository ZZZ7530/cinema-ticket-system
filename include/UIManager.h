#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "Movie.h"
#include "Showtime.h"
#include "Ticket.h"

#include <string>
#include <vector>

class CinemaSystem;

class UIManager {
private:
    CinemaSystem& cinemaSystem;

    int readMenuChoice(int minChoice, int maxChoice);
    int readPositiveInt(const std::string& prompt);
    std::string readRequiredLine(const std::string& prompt);
    bool askYesNo(const std::string& question);
    void pause() const;
    void showNotImplemented(const std::string& featureName) const;
    void showLoadWarningsIfAny() const;
    void showWarnings(const std::vector<std::string>& warnings) const;
    void displayMovieTable(const std::vector<Movie>& movies) const;
    void displayShowtimeTable(const std::vector<Showtime>& showtimes) const;
    void displayTicketTable() const;
    void displayTicket(const Ticket& ticket) const;

    void showMainMenu() const;
    void showMovieMenu();
    void showShowtimeMenu();
    void showStatisticsMenu();

    void addMovie();
    void showAllMovies();
    void searchMovie();
    void deleteMovie();
    void addShowtime();
    void showAllShowtimes();
    void searchShowtimesByMovie();
    void buyTicket();
    void refundTicket();
    void queryTickets();
    void showSeatMap();

public:
    explicit UIManager(CinemaSystem& cinemaSystem);
    void run();
};

#endif
