#ifndef MOVIE_H
#define MOVIE_H

#include <string>

class Movie {
private:
    std::string movieId;
    std::string title;
    std::string genre;
    int duration;

public:
    Movie();
    Movie(const std::string& movieId, const std::string& title, const std::string& genre, int duration);

    std::string getMovieId() const;
    std::string getTitle() const;
    std::string getGenre() const;
    int getDuration() const;

    std::string toFileString() const;
    static Movie fromFileString(const std::string& line);
    void display() const;
};

#endif
