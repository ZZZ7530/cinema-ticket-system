#include "UIManager.h"

#include "CinemaSystem.h"

#include <iostream>
#include <limits>
#include <string>
#include <vector>

UIManager::UIManager(CinemaSystem& cinemaSystem) : cinemaSystem(cinemaSystem) {}

int UIManager::readMenuChoice(int minChoice, int maxChoice) {
    int choice = -1;

    while (true) {
        std::cout << "請輸入選項：";
        if (std::cin >> choice) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (choice >= minChoice && choice <= maxChoice) {
                return choice;
            }
            std::cout << "[錯誤] 沒有這個選項，請重新輸入。" << std::endl;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[錯誤] 請輸入數字選項。" << std::endl;
        }
    }
}

int UIManager::readPositiveInt(const std::string& prompt) {
    int value = 0;

    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (value > 0) {
                return value;
            }
            std::cout << "[錯誤] 請輸入正整數。" << std::endl;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[錯誤] 請輸入數字。" << std::endl;
        }
    }
}

std::string UIManager::readRequiredLine(const std::string& prompt) {
    std::string value;

    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);
        if (!value.empty()) {
            return value;
        }
        std::cout << "[錯誤] 輸入不能為空。" << std::endl;
    }
}

bool UIManager::askYesNo(const std::string& question) {
    while (true) {
        std::cout << question << " (y/n)：";
        std::string answer;
        std::getline(std::cin, answer);

        if (answer == "y" || answer == "Y") {
            return true;
        }
        if (answer == "n" || answer == "N") {
            return false;
        }

        std::cout << "[錯誤] 請輸入 y 或 n。" << std::endl;
    }
}

void UIManager::pause() const {
    std::cout << std::endl;
    std::cout << "按 Enter 返回...";
    std::cin.get();
}

void UIManager::showNotImplemented(const std::string& featureName) const {
    std::cout << std::endl;
    std::cout << "[提示] " << featureName << " 功能尚未實作，將於後續 Iteration 完成。" << std::endl;
    pause();
}

void UIManager::showLoadWarningsIfAny() const {
    if (!cinemaSystem.getLoadWarnings().empty()) {
        std::cout << std::endl;
        std::cout << "[警告] 載入資料時發現以下問題：" << std::endl;
        showWarnings(cinemaSystem.getLoadWarnings());
    }
}

void UIManager::showWarnings(const std::vector<std::string>& warnings) const {
    for (const auto& warning : warnings) {
        std::cout << "[警告] " << warning << std::endl;
    }
}

void UIManager::displayMovieTable(const std::vector<Movie>& movies) const {
    if (movies.empty()) {
        std::cout << "[提示] 目前沒有電影資料" << std::endl;
        return;
    }

    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << "ID | 片名 | 類型 | 片長" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;
    for (const auto& movie : movies) {
        std::cout << movie.getMovieId() << " | "
                  << movie.getTitle() << " | "
                  << movie.getGenre() << " | "
                  << movie.getDuration() << " 分鐘" << std::endl;
    }
    std::cout << "------------------------------------------------------------" << std::endl;
}

void UIManager::displayShowtimeTable(const std::vector<Showtime>& showtimes) const {
    if (showtimes.empty()) {
        std::cout << "[提示] 此電影目前沒有場次" << std::endl;
        return;
    }

    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    std::cout << "場次ID | 電影名稱 | 日期 | 時間 | 影廳 | 座位數 | 已售出" << std::endl;
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    for (const auto& showtime : showtimes) {
        const int totalSeats = showtime.getRows() * showtime.getCols();
        const int soldCount = static_cast<int>(showtime.getSoldSeats().size());
        std::cout << showtime.getShowtimeId() << " | "
                  << cinemaSystem.getMovieTitleById(showtime.getMovieId()) << " | "
                  << showtime.getDate() << " | "
                  << showtime.getTime() << " | "
                  << showtime.getHall() << " | "
                  << totalSeats << " | "
                  << soldCount << std::endl;
    }
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
}

void UIManager::showMainMenu() const {
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "        電影院售票管理系統" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "資料狀態：電影 " << cinemaSystem.getMovieCount()
              << " 筆｜場次 " << cinemaSystem.getShowtimeCount()
              << " 筆｜票券 " << cinemaSystem.getTicketCount() << " 筆" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "1. 電影管理" << std::endl;
    std::cout << "2. 場次管理" << std::endl;
    std::cout << "3. 購買電影票" << std::endl;
    std::cout << "4. 退票" << std::endl;
    std::cout << "5. 查詢票券" << std::endl;
    std::cout << "6. 查看座位表" << std::endl;
    std::cout << "7. 營收統計" << std::endl;
    std::cout << "8. 儲存資料" << std::endl;
    std::cout << "0. 離開系統" << std::endl;
    std::cout << "========================================" << std::endl;
}

void UIManager::addMovie() {
    std::cout << std::endl;
    std::cout << "========== 新增電影 ==========" << std::endl;
    const std::string title = readRequiredLine("請輸入片名：");
    const std::string genre = readRequiredLine("請輸入類型：");
    const int duration = readPositiveInt("請輸入片長（分鐘）：");

    const Movie movie = cinemaSystem.addMovie(title, genre, duration);
    std::cout << "[成功] 電影新增完成，電影 ID：" << movie.getMovieId() << std::endl;
    pause();
}

void UIManager::showAllMovies() {
    std::cout << std::endl;
    std::cout << "========== 所有電影 ==========" << std::endl;
    displayMovieTable(cinemaSystem.getMovies());
    pause();
}

void UIManager::searchMovie() {
    std::cout << std::endl;
    std::cout << "========== 查詢電影 ==========" << std::endl;
    const std::string keyword = readRequiredLine("請輸入電影 ID 或片名關鍵字：");
    const std::vector<Movie> results = cinemaSystem.searchMovies(keyword);

    if (results.empty()) {
        std::cout << "[錯誤] 找不到電影" << std::endl;
    } else {
        displayMovieTable(results);
    }
    pause();
}

void UIManager::deleteMovie() {
    std::cout << std::endl;
    std::cout << "========== 刪除電影 ==========" << std::endl;
    const std::string movieId = readRequiredLine("請輸入要刪除的電影 ID：");

    const Movie* movie = cinemaSystem.findMovieById(movieId);
    if (movie == nullptr) {
        std::cout << "[錯誤] 找不到電影" << std::endl;
        pause();
        return;
    }

    if (cinemaSystem.hasShowtimesForMovie(movieId)) {
        std::cout << "[錯誤] 此電影已有場次，禁止刪除。請先移除相關場次後再刪除。" << std::endl;
        pause();
        return;
    }

    std::vector<Movie> preview = {*movie};
    displayMovieTable(preview);
    if (!askYesNo("確定要刪除此電影嗎")) {
        std::cout << "[提示] 已取消刪除" << std::endl;
        pause();
        return;
    }

    std::string message;
    if (cinemaSystem.deleteMovie(movieId, message)) {
        std::cout << "[成功] 電影已刪除" << std::endl;
    } else {
        std::cout << "[錯誤] " << message << std::endl;
    }
    pause();
}

void UIManager::addShowtime() {
    std::cout << std::endl;
    std::cout << "========== 新增電影場次 ==========" << std::endl;
    if (cinemaSystem.getMovies().empty()) {
        std::cout << "[錯誤] 目前沒有電影資料，請先新增電影。" << std::endl;
        pause();
        return;
    }

    displayMovieTable(cinemaSystem.getMovies());
    const std::string movieId = readRequiredLine("請輸入電影 ID：");
    if (cinemaSystem.findMovieById(movieId) == nullptr) {
        std::cout << "[錯誤] 電影 ID 不存在" << std::endl;
        pause();
        return;
    }

    const std::string date = readRequiredLine("請輸入日期（例如 2026-01-12）：");
    const std::string time = readRequiredLine("請輸入時間（例如 18:30）：");
    const std::string hall = readRequiredLine("請輸入影廳（例如 A廳）：");
    const int rows = readPositiveInt("請輸入座位列數 rows：");
    const int cols = readPositiveInt("請輸入座位行數 cols：");

    const Showtime showtime = cinemaSystem.addShowtime(movieId, date, time, hall, rows, cols);
    std::cout << "[成功] 場次新增完成，場次 ID：" << showtime.getShowtimeId() << std::endl;
    pause();
}

void UIManager::showAllShowtimes() {
    std::cout << std::endl;
    std::cout << "========== 所有場次 ==========" << std::endl;
    displayShowtimeTable(cinemaSystem.getShowtimes());
    pause();
}

void UIManager::searchShowtimesByMovie() {
    std::cout << std::endl;
    std::cout << "========== 查詢指定電影場次 ==========" << std::endl;
    const std::string keyword = readRequiredLine("請輸入電影 ID 或片名關鍵字：");
    const std::vector<Movie> movies = cinemaSystem.searchMovies(keyword);

    if (movies.empty()) {
        std::cout << "[錯誤] 找不到電影" << std::endl;
        pause();
        return;
    }

    const std::vector<Showtime> showtimes = cinemaSystem.searchShowtimesByMovie(keyword);
    displayShowtimeTable(showtimes);
    pause();
}

void UIManager::showMovieMenu() {
    while (true) {
        std::cout << std::endl;
        std::cout << "========== 電影管理 ==========" << std::endl;
        std::cout << "1. 新增電影" << std::endl;
        std::cout << "2. 顯示所有電影" << std::endl;
        std::cout << "3. 查詢電影" << std::endl;
        std::cout << "4. 刪除電影" << std::endl;
        std::cout << "0. 返回主選單" << std::endl;

        const int choice = readMenuChoice(0, 4);
        switch (choice) {
            case 1:
                addMovie();
                break;
            case 2:
                showAllMovies();
                break;
            case 3:
                searchMovie();
                break;
            case 4:
                deleteMovie();
                break;
            case 0:
                return;
        }
    }
}

void UIManager::showShowtimeMenu() {
    while (true) {
        std::cout << std::endl;
        std::cout << "========== 場次管理 ==========" << std::endl;
        std::cout << "1. 新增電影場次" << std::endl;
        std::cout << "2. 顯示所有場次" << std::endl;
        std::cout << "3. 查詢指定電影場次" << std::endl;
        std::cout << "0. 返回主選單" << std::endl;

        const int choice = readMenuChoice(0, 3);
        switch (choice) {
            case 1:
                addShowtime();
                break;
            case 2:
                showAllShowtimes();
                break;
            case 3:
                searchShowtimesByMovie();
                break;
            case 0:
                return;
        }
    }
}

void UIManager::showStatisticsMenu() {
    while (true) {
        std::cout << std::endl;
        std::cout << "========== 營收統計 ==========" << std::endl;
        std::cout << "1. 查看總營收" << std::endl;
        std::cout << "2. 查看各電影售票數量" << std::endl;
        std::cout << "3. 查看各票種銷售數量" << std::endl;
        std::cout << "0. 返回主選單" << std::endl;

        const int choice = readMenuChoice(0, 3);
        switch (choice) {
            case 1:
                showNotImplemented("查看總營收");
                break;
            case 2:
                showNotImplemented("查看各電影售票數量");
                break;
            case 3:
                showNotImplemented("查看各票種銷售數量");
                break;
            case 0:
                return;
        }
    }
}

void UIManager::run() {
    cinemaSystem.loadAllData();
    showLoadWarningsIfAny();

    bool running = true;
    while (running) {
        showMainMenu();
        const int choice = readMenuChoice(0, 8);

        switch (choice) {
            case 1:
                showMovieMenu();
                break;
            case 2:
                showShowtimeMenu();
                break;
            case 3:
                showNotImplemented("購買電影票");
                break;
            case 4:
                showNotImplemented("退票");
                break;
            case 5:
                showNotImplemented("查詢票券");
                break;
            case 6:
                showNotImplemented("查看座位表");
                break;
            case 7:
                showStatisticsMenu();
                break;
            case 8:
                if (cinemaSystem.saveAllData()) {
                    std::cout << std::endl;
                    std::cout << "[成功] 資料已儲存" << std::endl;
                } else {
                    std::cout << std::endl;
                    showWarnings(cinemaSystem.getSaveWarnings());
                    std::cout << "[警告] 資料儲存未完全成功，請檢查 data/ 檔案狀態。" << std::endl;
                }
                pause();
                break;
            case 0:
                std::cout << std::endl;
                if (askYesNo("離開系統前是否儲存資料")) {
                    if (cinemaSystem.saveAllData()) {
                        std::cout << "[成功] 資料已儲存" << std::endl;
                    } else {
                        showWarnings(cinemaSystem.getSaveWarnings());
                        std::cout << "[警告] 資料儲存未完全成功。" << std::endl;
                    }
                }
                std::cout << "感謝使用電影院售票管理系統，再見！" << std::endl;
                running = false;
                break;
        }
    }
}
