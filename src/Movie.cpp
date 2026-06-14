#include "Movie.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace {
std::vector<std::string> split(const std::string& text, char delimiter) {
    std::vector<std::string> parts;
    std::stringstream ss(text);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        parts.push_back(item);
    }

    return parts;
}
}  // namespace

Movie::Movie() : duration(0) {}

Movie::Movie(const std::string& movieId, const std::string& title, const std::string& genre, int duration)
    : movieId(movieId), title(title), genre(genre), duration(duration) {}

std::string Movie::getMovieId() const {
    return movieId;
}

std::string Movie::getTitle() const {
    return title;
}

std::string Movie::getGenre() const {
    return genre;
}

int Movie::getDuration() const {
    return duration;
}

std::string Movie::toFileString() const {
    return movieId + "|" + title + "|" + genre + "|" + std::to_string(duration);
}

Movie Movie::fromFileString(const std::string& line) {
    const std::vector<std::string> parts = split(line, '|');
    if (parts.size() != 4) {
        throw std::invalid_argument("Invalid movie file line: " + line);
    }

    return Movie(parts[0], parts[1], parts[2], std::stoi(parts[3]));
}

void Movie::display() const {
    std::cout << movieId << " | " << title << " | " << genre << " | " << duration << " 分鐘" << std::endl;
}
