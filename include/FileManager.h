#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "Movie.h"
#include "Showtime.h"
#include "Ticket.h"

#include <memory>
#include <string>
#include <vector>

class FileManager {
private:
    static const std::string dataDirectory;
    static const std::string moviesFile;
    static const std::string showtimesFile;
    static const std::string ticketsFile;

    static void ensureDataFilesExist();
    static void seedDefaultDataIfEmpty();
    static std::vector<std::string> split(const std::string& text, char delimiter);
    static bool shouldSkipLine(const std::string& line, const std::string& headerPrefix);

public:
    static std::vector<Movie> loadMovies(std::vector<std::string>& warnings);
    static std::vector<Showtime> loadShowtimes(std::vector<std::string>& warnings);
    static std::vector<std::unique_ptr<Ticket>> loadTickets(std::vector<std::string>& warnings);

    static bool saveMovies(const std::vector<Movie>& movies, std::vector<std::string>& warnings);
    static bool saveShowtimes(const std::vector<Showtime>& showtimes, std::vector<std::string>& warnings);
    static bool saveTickets(const std::vector<std::unique_ptr<Ticket>>& tickets, std::vector<std::string>& warnings);
};

#endif
