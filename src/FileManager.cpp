#include "FileManager.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>

const std::string FileManager::dataDirectory = "data";
const std::string FileManager::moviesFile = "data/movies.txt";
const std::string FileManager::showtimesFile = "data/showtimes.txt";
const std::string FileManager::ticketsFile = "data/tickets.txt";

void FileManager::ensureDataFilesExist() {
    std::filesystem::create_directories(dataDirectory);

    const std::vector<std::string> files = {moviesFile, showtimesFile, ticketsFile};
    for (const auto& file : files) {
        if (!std::filesystem::exists(file)) {
            std::ofstream createFile(file);
        }
    }

    seedDefaultDataIfEmpty();
}

void FileManager::seedDefaultDataIfEmpty() {
    if (std::filesystem::exists(moviesFile) && std::filesystem::file_size(moviesFile) == 0) {
        std::ofstream file(moviesFile);
        file << "movieId|title|genre|duration\n";
        file << "M001|鬼滅之刃劇場版|動畫|120\n";
        file << "M002|名偵探柯南劇場版|推理|110\n";
        file << "M003|星際效應|科幻|169\n";
    }

    if (std::filesystem::exists(showtimesFile) && std::filesystem::file_size(showtimesFile) == 0) {
        std::ofstream file(showtimesFile);
        file << "showtimeId|movieId|date|time|hall|rows|cols|soldSeats\n";
        file << "S001|M001|2026-01-10|14:00|A廳|5|6|A3,B2,C5\n";
        file << "S002|M002|2026-01-10|16:30|B廳|5|6|A1,A2\n";
        file << "S003|M003|2026-01-11|19:00|C廳|6|8|\n";
    }

    if (std::filesystem::exists(ticketsFile) && std::filesystem::file_size(ticketsFile) == 0) {
        std::ofstream file(ticketsFile);
        file << "ticketId|showtimeId|movieTitle|seatNo|ticketType|price\n";
        file << "T001|S001|鬼滅之刃劇場版|A3|成人票|320\n";
        file << "T002|S001|鬼滅之刃劇場版|B2|學生票|280\n";
        file << "T003|S002|名偵探柯南劇場版|A1|兒童票|220\n";
    }
}

std::vector<std::string> FileManager::split(const std::string& text, char delimiter) {
    std::vector<std::string> parts;
    std::stringstream ss(text);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        parts.push_back(item);
    }

    if (!text.empty() && text.back() == delimiter) {
        parts.emplace_back("");
    }

    return parts;
}

bool FileManager::shouldSkipLine(const std::string& line, const std::string& headerPrefix) {
    return line.empty() || line.rfind(headerPrefix, 0) == 0;
}

std::vector<Movie> FileManager::loadMovies(std::vector<std::string>& warnings) {
    ensureDataFilesExist();

    std::vector<Movie> movies;
    std::ifstream file(moviesFile);
    if (!file) {
        warnings.push_back("無法讀取 data/movies.txt");
        return movies;
    }

    std::string line;
    int lineNumber = 0;
    while (std::getline(file, line)) {
        ++lineNumber;
        if (shouldSkipLine(line, "movieId|")) {
            continue;
        }

        try {
            movies.push_back(Movie::fromFileString(line));
        } catch (const std::exception& ex) {
            warnings.push_back("data/movies.txt 第 " + std::to_string(lineNumber) + " 行格式錯誤：" + ex.what());
        }
    }

    return movies;
}

std::vector<Showtime> FileManager::loadShowtimes(std::vector<std::string>& warnings) {
    ensureDataFilesExist();

    std::vector<Showtime> showtimes;
    std::ifstream file(showtimesFile);
    if (!file) {
        warnings.push_back("無法讀取 data/showtimes.txt");
        return showtimes;
    }

    std::string line;
    int lineNumber = 0;
    while (std::getline(file, line)) {
        ++lineNumber;
        if (shouldSkipLine(line, "showtimeId|")) {
            continue;
        }

        try {
            showtimes.push_back(Showtime::fromFileString(line));
        } catch (const std::exception& ex) {
            warnings.push_back("data/showtimes.txt 第 " + std::to_string(lineNumber) + " 行格式錯誤：" + ex.what());
        }
    }

    return showtimes;
}

std::vector<std::unique_ptr<Ticket>> FileManager::loadTickets(std::vector<std::string>& warnings) {
    ensureDataFilesExist();

    std::vector<std::unique_ptr<Ticket>> tickets;
    std::ifstream file(ticketsFile);
    if (!file) {
        warnings.push_back("無法讀取 data/tickets.txt");
        return tickets;
    }

    std::string line;
    int lineNumber = 0;
    while (std::getline(file, line)) {
        ++lineNumber;
        if (shouldSkipLine(line, "ticketId|")) {
            continue;
        }

        const std::vector<std::string> parts = split(line, '|');
        if (parts.size() != 6) {
            warnings.push_back("data/tickets.txt 第 " + std::to_string(lineNumber) + " 行格式錯誤：欄位數量不正確");
            continue;
        }

        try {
            tickets.push_back(createTicketByType(parts[0], parts[1], parts[2], parts[3], parts[4]));
        } catch (const std::exception& ex) {
            warnings.push_back("data/tickets.txt 第 " + std::to_string(lineNumber) + " 行格式錯誤：" + ex.what());
        }
    }

    return tickets;
}

bool FileManager::saveMovies(const std::vector<Movie>& movies, std::vector<std::string>& warnings) {
    ensureDataFilesExist();

    std::ofstream file(moviesFile);
    if (!file) {
        warnings.push_back("無法寫入 data/movies.txt");
        return false;
    }

    file << "movieId|title|genre|duration\n";
    for (const auto& movie : movies) {
        file << movie.toFileString() << '\n';
    }
    return true;
}

bool FileManager::saveShowtimes(const std::vector<Showtime>& showtimes, std::vector<std::string>& warnings) {
    ensureDataFilesExist();

    std::ofstream file(showtimesFile);
    if (!file) {
        warnings.push_back("無法寫入 data/showtimes.txt");
        return false;
    }

    file << "showtimeId|movieId|date|time|hall|rows|cols|soldSeats\n";
    for (const auto& showtime : showtimes) {
        file << showtime.toFileString() << '\n';
    }
    return true;
}

bool FileManager::saveTickets(const std::vector<std::unique_ptr<Ticket>>& tickets, std::vector<std::string>& warnings) {
    ensureDataFilesExist();

    std::ofstream file(ticketsFile);
    if (!file) {
        warnings.push_back("無法寫入 data/tickets.txt");
        return false;
    }

    file << "ticketId|showtimeId|movieTitle|seatNo|ticketType|price\n";
    for (const auto& ticket : tickets) {
        if (ticket) {
            file << ticket->toFileString() << '\n';
        }
    }
    return true;
}
