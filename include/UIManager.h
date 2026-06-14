#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <string>

class CinemaSystem;

class UIManager {
private:
    CinemaSystem& cinemaSystem;

    int readMenuChoice(int minChoice, int maxChoice);
    void pause() const;
    void showNotImplemented(const std::string& featureName) const;

    void showMainMenu() const;
    void showMovieMenu();
    void showShowtimeMenu();
    void showStatisticsMenu();

public:
    explicit UIManager(CinemaSystem& cinemaSystem);
    void run();
};

#endif
