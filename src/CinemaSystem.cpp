#include "CinemaSystem.h"

#include "FileManager.h"

#include <algorithm>
#include <cctype>
#include <exception>
#include <iomanip>
#include <sstream>

CinemaSystem::CinemaSystem() = default;

namespace {
int extractIdNumber(const std::string& id, char expectedPrefix) {
    if (id.size() < 2 || id[0] != expectedPrefix) {
        return 0;
    }

    try {
        return std::stoi(id.substr(1));
    } catch (const std::exception&) {
        return 0;
    }
}

std::string makeId(char prefix, int number) {
    std::ostringstream oss;
    oss << prefix << std::setw(3) << std::setfill('0') << number;
    return oss.str();
}

std::string toLowerAscii(std::string text) {
    std::transform(text.begin(), text.end(), text.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });
    return text;
}

bool containsKeyword(const std::string& text, const std::string& keyword) {
    return toLowerAscii(text).find(toLowerAscii(keyword)) != std::string::npos;
}
}  // namespace

std::string CinemaSystem::generateNextMovieId() const {
    int maxNumber = 0;
    for (const auto& movie : movies) {
        maxNumber = std::max(maxNumber, extractIdNumber(movie.getMovieId(), 'M'));
    }
    return makeId('M', maxNumber + 1);
}

std::string CinemaSystem::generateNextShowtimeId() const {
    int maxNumber = 0;
    for (const auto& showtime : showtimes) {
        maxNumber = std::max(maxNumber, extractIdNumber(showtime.getShowtimeId(), 'S'));
    }
    return makeId('S', maxNumber + 1);
}

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

Movie CinemaSystem::addMovie(const std::string& title, const std::string& genre, int duration) {
    Movie movie(generateNextMovieId(), title, genre, duration);
    movies.push_back(movie);
    return movie;
}

std::vector<Movie> CinemaSystem::searchMovies(const std::string& keyword) const {
    std::vector<Movie> results;
    for (const auto& movie : movies) {
        if (containsKeyword(movie.getMovieId(), keyword) || containsKeyword(movie.getTitle(), keyword)) {
            results.push_back(movie);
        }
    }
    return results;
}

const Movie* CinemaSystem::findMovieById(const std::string& movieId) const {
    const auto it = std::find_if(movies.begin(), movies.end(), [&movieId](const Movie& movie) {
        return movie.getMovieId() == movieId;
    });
    return it == movies.end() ? nullptr : &(*it);
}

bool CinemaSystem::deleteMovie(const std::string& movieId, std::string& message) {
    const auto it = std::find_if(movies.begin(), movies.end(), [&movieId](const Movie& movie) {
        return movie.getMovieId() == movieId;
    });

    if (it == movies.end()) {
        message = "找不到電影 ID：" + movieId;
        return false;
    }

    if (hasShowtimesForMovie(movieId)) {
        message = "此電影已有場次，請先移除相關場次後再刪除。";
        return false;
    }

    movies.erase(it);
    message = "電影已刪除";
    return true;
}

bool CinemaSystem::hasShowtimesForMovie(const std::string& movieId) const {
    return std::any_of(showtimes.begin(), showtimes.end(), [&movieId](const Showtime& showtime) {
        return showtime.getMovieId() == movieId;
    });
}

Showtime CinemaSystem::addShowtime(const std::string& movieId,
                                   const std::string& date,
                                   const std::string& time,
                                   const std::string& hall,
                                   int rows,
                                   int cols) {
    Showtime showtime(generateNextShowtimeId(), movieId, date, time, hall, rows, cols);
    showtimes.push_back(showtime);
    return showtime;
}

std::vector<Showtime> CinemaSystem::searchShowtimesByMovie(const std::string& keyword) const {
    std::vector<Showtime> results;
    const std::vector<Movie> matchedMovies = searchMovies(keyword);

    for (const auto& movie : matchedMovies) {
        for (const auto& showtime : showtimes) {
            if (showtime.getMovieId() == movie.getMovieId()) {
                results.push_back(showtime);
            }
        }
    }

    return results;
}

std::string CinemaSystem::getMovieTitleById(const std::string& movieId) const {
    const Movie* movie = findMovieById(movieId);
    return movie == nullptr ? "(未知電影)" : movie->getTitle();
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
