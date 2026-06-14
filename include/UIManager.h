#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <string>
#include <vector>

class CinemaSystem;

class UIManager {
private:
    CinemaSystem& cinemaSystem;

    int readMenuChoice(int minChoice, int maxChoice);
    bool askYesNo(const std::string& question);
    void pause() const;
    void showNotImplemented(const std::string& featureName) const;
    void showLoadWarningsIfAny() const;
    void showWarnings(const std::vector<std::string>& warnings) const;

    void showMainMenu() const;
    void showMovieMenu();
    void showShowtimeMenu();
    void showStatisticsMenu();

public:
    explicit UIManager(CinemaSystem& cinemaSystem);
    void run();
};

#endif
