#include "Showtime.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace {
std::vector<std::string> split(const std::string& text, char delimiter) {
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

std::string join(const std::vector<std::string>& values, char delimiter) {
    std::string result;
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (i > 0) {
            result += delimiter;
        }
        result += values[i];
    }
    return result;
}
}  // namespace

Showtime::Showtime() : rows(0), cols(0) {}

Showtime::Showtime(const std::string& showtimeId,
                   const std::string& movieId,
                   const std::string& date,
                   const std::string& time,
                   const std::string& hall,
                   int rows,
                   int cols,
                   const std::vector<std::string>& soldSeats)
    : showtimeId(showtimeId),
      movieId(movieId),
      date(date),
      time(time),
      hall(hall),
      rows(rows),
      cols(cols),
      soldSeats(soldSeats) {}

std::string Showtime::getShowtimeId() const {
    return showtimeId;
}

std::string Showtime::getMovieId() const {
    return movieId;
}

std::string Showtime::getDate() const {
    return date;
}

std::string Showtime::getTime() const {
    return time;
}

std::string Showtime::getHall() const {
    return hall;
}

int Showtime::getRows() const {
    return rows;
}

int Showtime::getCols() const {
    return cols;
}

std::vector<std::string> Showtime::getSoldSeats() const {
    return soldSeats;
}

bool Showtime::isSeatInRange(const std::string& seatNo) const {
    if (seatNo.size() < 2 || !std::isalpha(static_cast<unsigned char>(seatNo[0]))) {
        return false;
    }

    const char rowChar = static_cast<char>(std::toupper(static_cast<unsigned char>(seatNo[0])));
    const int rowIndex = rowChar - 'A';
    if (rowIndex < 0 || rowIndex >= rows) {
        return false;
    }

    try {
        const int colIndex = std::stoi(seatNo.substr(1)) - 1;
        return colIndex >= 0 && colIndex < cols;
    } catch (const std::exception&) {
        return false;
    }
}

bool Showtime::isSeatSold(const std::string& seatNo) const {
    return std::find(soldSeats.begin(), soldSeats.end(), seatNo) != soldSeats.end();
}

bool Showtime::sellSeat(const std::string& seatNo) {
    if (!isSeatInRange(seatNo) || isSeatSold(seatNo)) {
        return false;
    }

    soldSeats.push_back(seatNo);
    return true;
}

bool Showtime::releaseSeat(const std::string& seatNo) {
    const auto seatIt = std::find(soldSeats.begin(), soldSeats.end(), seatNo);
    if (seatIt == soldSeats.end()) {
        return false;
    }

    soldSeats.erase(seatIt);
    return true;
}

std::string Showtime::toFileString() const {
    return showtimeId + "|" + movieId + "|" + date + "|" + time + "|" + hall + "|" +
           std::to_string(rows) + "|" + std::to_string(cols) + "|" + join(soldSeats, ',');
}

Showtime Showtime::fromFileString(const std::string& line) {
    const std::vector<std::string> parts = split(line, '|');
    if (parts.size() != 8) {
        throw std::invalid_argument("Invalid showtime file line: " + line);
    }

    std::vector<std::string> seats;
    if (!parts[7].empty()) {
        seats = split(parts[7], ',');
    }

    return Showtime(parts[0], parts[1], parts[2], parts[3], parts[4], std::stoi(parts[5]), std::stoi(parts[6]), seats);
}

void Showtime::display() const {
    std::cout << showtimeId << " | 電影ID: " << movieId << " | " << date << " " << time
              << " | " << hall << " | " << rows << "x" << cols << std::endl;
}

void Showtime::displaySeatMap() const {
    std::cout << "========================================" << std::endl;
    std::cout << "座位表 - " << showtimeId << " " << hall << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "    ";

    for (int col = 1; col <= cols; ++col) {
        std::cout << col << "   ";
    }
    std::cout << std::endl;

    for (int row = 0; row < rows; ++row) {
        const char rowChar = static_cast<char>('A' + row);
        std::cout << rowChar << "   ";
        for (int col = 1; col <= cols; ++col) {
            const std::string seatNo = std::string(1, rowChar) + std::to_string(col);
            std::cout << (isSeatSold(seatNo) ? "X" : "O") << "   ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "O = 可選座位" << std::endl;
    std::cout << "X = 已售出座位" << std::endl;
}
