#ifndef SHOWTIME_H
#define SHOWTIME_H

#include <string>
#include <vector>

class Showtime {
private:
    std::string showtimeId;
    std::string movieId;
    std::string date;
    std::string time;
    std::string hall;
    int rows;
    int cols;
    std::vector<std::string> soldSeats;

    bool isSeatInRange(const std::string& seatNo) const;

public:
    Showtime();
    Showtime(const std::string& showtimeId,
             const std::string& movieId,
             const std::string& date,
             const std::string& time,
             const std::string& hall,
             int rows,
             int cols,
             const std::vector<std::string>& soldSeats = {});

    std::string getShowtimeId() const;
    std::string getMovieId() const;
    std::string getDate() const;
    std::string getTime() const;
    std::string getHall() const;
    int getRows() const;
    int getCols() const;
    std::vector<std::string> getSoldSeats() const;

    bool isSeatValid(const std::string& seatNo) const;
    bool isSeatSold(const std::string& seatNo) const;
    bool sellSeat(const std::string& seatNo);
    bool releaseSeat(const std::string& seatNo);

    std::string toFileString() const;
    static Showtime fromFileString(const std::string& line);
    void display() const;
    void displaySeatMap() const;
};

#endif
