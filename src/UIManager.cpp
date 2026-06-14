#include "UIManager.h"

#include "CinemaSystem.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <vector>

namespace {
const std::string RESET = "\033[0m";
const std::string CYAN = "\033[96m";
const std::string BLUE = "\033[94m";
const std::string GREEN = "\033[92m";
const std::string RED = "\033[91m";
const std::string YELLOW = "\033[93m";
const std::string DIM = "\033[2m";

std::string normalizeSeatNo(std::string seatNo) {
    if (!seatNo.empty()) {
        seatNo[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(seatNo[0])));
    }
    return seatNo;
}

bool isPositiveNumberText(const std::string& text) {
    return !text.empty() && std::all_of(text.begin(), text.end(), [](unsigned char ch) {
        return std::isdigit(ch);
    });
}
}  // namespace

UIManager::UIManager(CinemaSystem& cinemaSystem) : cinemaSystem(cinemaSystem) {}

std::string UIManager::colorText(const std::string& text, const std::string& colorCode) const {
    return colorCode + text + RESET;
}

void UIManager::printDivider() const {
    std::cout << colorText("────────────────────────────────────────", DIM) << std::endl;
}

void UIManager::printPageTitle(const std::string& title) const {
    std::cout << std::endl;
    std::cout << colorText("────────────────────────────────────────", BLUE) << std::endl;
    std::cout << colorText(title, CYAN) << std::endl;
    std::cout << colorText("────────────────────────────────────────", BLUE) << std::endl;
}

void UIManager::printBoxTitle(const std::string& title) const {
    std::cout << colorText("╔════════════════════════════════════╗", CYAN) << std::endl;
    std::cout << colorText("║          " + title, CYAN) << std::endl;
    std::cout << colorText("╚════════════════════════════════════╝", CYAN) << std::endl;
}

void UIManager::printSuccess(const std::string& message) const {
    std::cout << colorText("[成功] " + message, GREEN) << std::endl;
}

void UIManager::printError(const std::string& message) const {
    std::cout << colorText("[錯誤] " + message, RED) << std::endl;
}

void UIManager::printWarning(const std::string& message) const {
    std::cout << colorText("[警告] " + message, YELLOW) << std::endl;
}

void UIManager::printInfo(const std::string& message) const {
    std::cout << colorText("[提示] " + message, CYAN) << std::endl;
}

void UIManager::printMainMenu() const {
    std::cout << std::endl;
    std::cout << colorText("╔══════════════════════════════════════════════╗", CYAN) << std::endl;
    std::cout << colorText("║              電影院售票管理系統              ║", CYAN) << std::endl;
    std::cout << colorText("╠══════════════════════════════════════════════╣", CYAN) << std::endl;
    std::cout << "║ 資料狀態：電影 " << cinemaSystem.getMovieCount()
              << " 筆｜場次 " << cinemaSystem.getShowtimeCount()
              << " 筆｜票券 " << cinemaSystem.getTicketCount() << " 筆     ║" << std::endl;
    std::cout << colorText("╠══════════════════════════════════════════════╣", CYAN) << std::endl;
    std::cout << "║  " << colorText("1", YELLOW) << ". 電影管理                                 ║" << std::endl;
    std::cout << "║  " << colorText("2", YELLOW) << ". 場次管理                                 ║" << std::endl;
    std::cout << "║  " << colorText("3", YELLOW) << ". 購買電影票                               ║" << std::endl;
    std::cout << "║  " << colorText("4", YELLOW) << ". 退票                                     ║" << std::endl;
    std::cout << "║  " << colorText("5", YELLOW) << ". 查詢票券                                 ║" << std::endl;
    std::cout << "║  " << colorText("6", YELLOW) << ". 查看座位表                               ║" << std::endl;
    std::cout << "║  " << colorText("7", YELLOW) << ". 營收統計                                 ║" << std::endl;
    std::cout << "║  " << colorText("8", YELLOW) << ". 儲存資料                                 ║" << std::endl;
    std::cout << "║  " << colorText("0", YELLOW) << ". 離開系統                                 ║" << std::endl;
    std::cout << colorText("╚══════════════════════════════════════════════╝", CYAN) << std::endl;
}

void UIManager::printSubMenu(const std::string& title, const std::vector<std::string>& items) const {
    std::cout << std::endl;
    std::cout << colorText("╔══════════════════════╗", CYAN) << std::endl;
    std::cout << colorText("║       " + title + "        ║", CYAN) << std::endl;
    std::cout << colorText("╠══════════════════════╣", CYAN) << std::endl;
    for (const auto& item : items) {
        const std::size_t dotPos = item.find('.');
        if (dotPos != std::string::npos) {
            std::cout << "║  " << colorText(item.substr(0, dotPos), YELLOW)
                      << item.substr(dotPos) << "        ║" << std::endl;
        } else {
            std::cout << "║  " << item << "        ║" << std::endl;
        }
    }
    std::cout << colorText("╚══════════════════════╝", CYAN) << std::endl;
}

int UIManager::readMenuChoice(int minChoice, int maxChoice) {
    int choice = -1;

    while (true) {
        std::cout << "請輸入選項：";
        if (std::cin >> choice) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (choice >= minChoice && choice <= maxChoice) {
                return choice;
            }
            printError("請輸入有效的數字選項。");
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            printError("請輸入有效的數字選項。");
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
            printError("請輸入正整數。");
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            printError("請輸入有效的數字。");
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
        printError("輸入不能為空。");
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

        printError("請輸入 y 或 n。");
    }
}

void UIManager::pause() const {
    std::cout << std::endl;
    std::cout << colorText("按 Enter 返回...", DIM);
    std::cin.get();
}

void UIManager::showNotImplemented(const std::string& featureName) const {
    std::cout << std::endl;
    printInfo(featureName + " 功能尚未實作，將於後續 Iteration 完成。");
    pause();
}

void UIManager::showLoadWarningsIfAny() const {
    if (!cinemaSystem.getLoadWarnings().empty()) {
        std::cout << std::endl;
        printWarning("載入資料時發現以下問題：");
        showWarnings(cinemaSystem.getLoadWarnings());
    }
}

void UIManager::showWarnings(const std::vector<std::string>& warnings) const {
    for (const auto& warning : warnings) {
        printWarning(warning);
    }
}

void UIManager::displayMovieTable(const std::vector<Movie>& movies) const {
    if (movies.empty()) {
        printInfo("目前沒有電影資料");
        return;
    }

    for (const auto& movie : movies) {
        printDivider();
        std::cout << "電影 ID：" << movie.getMovieId() << std::endl;
        std::cout << "片名：" << movie.getTitle() << std::endl;
        std::cout << "類型：" << movie.getGenre() << std::endl;
        std::cout << "片長：" << movie.getDuration() << " 分鐘" << std::endl;
    }
    printDivider();
}

void UIManager::displayShowtimeTable(const std::vector<Showtime>& showtimes) const {
    if (showtimes.empty()) {
        printInfo("此電影目前沒有場次");
        return;
    }

    for (const auto& showtime : showtimes) {
        const int totalSeats = showtime.getRows() * showtime.getCols();
        const int soldCount = static_cast<int>(showtime.getSoldSeats().size());
        printDivider();
        std::cout << "場次 ID：" << showtime.getShowtimeId() << std::endl;
        std::cout << "電影：" << cinemaSystem.getMovieTitleById(showtime.getMovieId()) << std::endl;
        std::cout << "日期時間：" << showtime.getDate() << " " << showtime.getTime() << std::endl;
        std::cout << "影廳：" << showtime.getHall() << std::endl;
        std::cout << "座位數：" << totalSeats << "，已售出：" << soldCount << std::endl;
    }
    printDivider();
}

void UIManager::displayTicket(const Ticket& ticket) const {
    std::cout << "票號：" << ticket.getTicketId() << std::endl;
    std::cout << "電影：" << ticket.getMovieTitle() << std::endl;
    std::cout << "場次：" << ticket.getShowtimeId() << std::endl;
    std::cout << "座位：" << ticket.getSeatNo() << std::endl;
    std::cout << "票種：" << ticket.getTicketType() << std::endl;
    std::cout << "票價：NT$" << ticket.calculatePrice() << std::endl;
}

void UIManager::displayTicketTable() const {
    const auto& tickets = cinemaSystem.getTickets();
    if (tickets.empty()) {
        printInfo("目前沒有已售出票券");
        return;
    }

    for (const auto& ticket : tickets) {
        if (ticket) {
            printDivider();
            displayTicket(*ticket);
        }
    }
    printDivider();
}

void UIManager::displaySeatMap(const Showtime& showtime) const {
    std::cout << std::endl;
    std::cout << colorText("╔════════════════════════════════════╗", CYAN) << std::endl;
    std::cout << colorText("║          座位表 - " + showtime.getShowtimeId() + " " + showtime.getHall() + "         ║", CYAN) << std::endl;
    std::cout << colorText("╚════════════════════════════════════╝", CYAN) << std::endl;
    std::cout << std::endl;
    std::cout << "        ";
    for (int col = 1; col <= showtime.getCols(); ++col) {
        std::cout << col << "   ";
    }
    std::cout << std::endl;

    for (int row = 0; row < showtime.getRows(); ++row) {
        const char rowChar = static_cast<char>('A' + row);
        std::cout << "   " << rowChar << "    ";
        for (int col = 1; col <= showtime.getCols(); ++col) {
            const std::string seatNo = std::string(1, rowChar) + std::to_string(col);
            if (showtime.isSeatSold(seatNo)) {
                std::cout << colorText("X", RED) << "   ";
            } else {
                std::cout << colorText("O", GREEN) << "   ";
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "說明：" << colorText("O = 可選座位", GREEN)
              << "，" << colorText("X = 已售出座位", RED) << std::endl;
}

void UIManager::showMainMenu() const {
    printMainMenu();
}

void UIManager::addMovie() {
    printPageTitle("[電影管理] 新增電影");
    const std::string title = readRequiredLine("請輸入片名：");
    const std::string genre = readRequiredLine("請輸入類型：");
    const int duration = readPositiveInt("請輸入片長（分鐘）：");

    const Movie movie = cinemaSystem.addMovie(title, genre, duration);
    printSuccess("電影新增完成，電影 ID：" + movie.getMovieId());
    pause();
}

void UIManager::showAllMovies() {
    printPageTitle("[電影管理] 顯示所有電影");
    displayMovieTable(cinemaSystem.getMovies());
    pause();
}

void UIManager::searchMovie() {
    printPageTitle("[電影管理] 查詢電影");
    const std::string keyword = readRequiredLine("請輸入電影 ID 或片名關鍵字：");
    const std::vector<Movie> results = cinemaSystem.searchMovies(keyword);

    if (results.empty()) {
        printError("找不到指定 ID 或片名關鍵字。");
    } else {
        displayMovieTable(results);
    }
    pause();
}

void UIManager::deleteMovie() {
    printPageTitle("[電影管理] 刪除電影");
    const std::string movieId = readRequiredLine("請輸入要刪除的電影 ID：");

    const Movie* movie = cinemaSystem.findMovieById(movieId);
    if (movie == nullptr) {
        printError("找不到指定 ID。");
        pause();
        return;
    }

    if (cinemaSystem.hasShowtimesForMovie(movieId)) {
        printWarning("此電影已有場次，禁止刪除。請先移除相關場次後再刪除。");
        pause();
        return;
    }

    std::vector<Movie> preview = {*movie};
    displayMovieTable(preview);
    if (!askYesNo("確定要刪除此電影嗎")) {
        printInfo("已取消刪除");
        pause();
        return;
    }

    std::string message;
    if (cinemaSystem.deleteMovie(movieId, message)) {
        printSuccess("電影已刪除");
    } else {
        printError(message);
    }
    pause();
}

void UIManager::addShowtime() {
    printPageTitle("[場次管理] 新增電影場次");
    if (cinemaSystem.getMovies().empty()) {
        printError("目前沒有電影資料，請先新增電影。");
        pause();
        return;
    }

    displayMovieTable(cinemaSystem.getMovies());
    const std::string movieId = readRequiredLine("請輸入電影 ID：");
    if (cinemaSystem.findMovieById(movieId) == nullptr) {
        printError("找不到指定 ID。");
        pause();
        return;
    }

    const std::string date = readRequiredLine("請輸入日期（例如 2026-01-12）：");
    const std::string time = readRequiredLine("請輸入時間（例如 18:30）：");
    const std::string hall = readRequiredLine("請輸入影廳（例如 A廳）：");
    const int rows = readPositiveInt("請輸入座位列數 rows：");
    const int cols = readPositiveInt("請輸入座位行數 cols：");

    const Showtime showtime = cinemaSystem.addShowtime(movieId, date, time, hall, rows, cols);
    printSuccess("場次新增完成，場次 ID：" + showtime.getShowtimeId());
    pause();
}

void UIManager::showAllShowtimes() {
    printPageTitle("[場次管理] 顯示所有場次");
    displayShowtimeTable(cinemaSystem.getShowtimes());
    pause();
}

void UIManager::searchShowtimesByMovie() {
    printPageTitle("[場次管理] 查詢指定電影場次");
    const std::string keyword = readRequiredLine("請輸入電影 ID 或片名關鍵字：");
    const std::vector<Movie> movies = cinemaSystem.searchMovies(keyword);

    if (movies.empty()) {
        printError("找不到指定 ID 或片名關鍵字。");
        pause();
        return;
    }

    const std::vector<Showtime> showtimes = cinemaSystem.searchShowtimesByMovie(keyword);
    displayShowtimeTable(showtimes);
    pause();
}

void UIManager::buyTicket() {
    printPageTitle("[購票流程] 選擇電影");
    const auto& movies = cinemaSystem.getMovies();
    if (movies.empty()) {
        printError("目前沒有電影資料");
        pause();
        return;
    }

    printInfo("可輸入電影 ID，或輸入左側序號選擇電影。");
    printDivider();
    for (std::size_t i = 0; i < movies.size(); ++i) {
        const Movie& movie = movies[i];
        std::cout << colorText(std::to_string(i + 1) + ".", YELLOW) << " "
                  << movie.getMovieId() << "｜" << movie.getTitle()
                  << "｜" << movie.getGenre() << "｜" << movie.getDuration() << " 分鐘" << std::endl;
    }
    printDivider();

    const std::string movieInput = readRequiredLine("請輸入電影 ID 或序號：");
    std::string movieId = movieInput;
    if (isPositiveNumberText(movieInput)) {
        const int index = std::stoi(movieInput);
        if (index >= 1 && index <= static_cast<int>(movies.size())) {
            movieId = movies[static_cast<std::size_t>(index - 1)].getMovieId();
        }
    }

    if (cinemaSystem.findMovieById(movieId) == nullptr) {
        printError("找不到指定 ID。");
        pause();
        return;
    }

    printPageTitle("[購票流程] 選擇場次");
    const std::vector<Showtime> showtimes = cinemaSystem.searchShowtimesByMovie(movieId);
    if (showtimes.empty()) {
        printInfo("此電影目前沒有場次");
        pause();
        return;
    }

    displayShowtimeTable(showtimes);
    const std::string showtimeId = readRequiredLine("請輸入場次 ID：");
    const Showtime* showtime = cinemaSystem.findShowtimeById(showtimeId);
    if (showtime == nullptr) {
        printError("找不到指定 ID。");
        pause();
        return;
    }
    if (showtime->getMovieId() != movieId) {
        printError("此場次不屬於所選電影。");
        pause();
        return;
    }

    printPageTitle("[購票流程] 選擇座位");
    displaySeatMap(*showtime);
    const std::string seatNo = normalizeSeatNo(readRequiredLine("請輸入座位（例如 A3）："));
    if (!showtime->isSeatValid(seatNo)) {
        printError("座位格式錯誤或超出範圍。");
        pause();
        return;
    }
    if (showtime->isSeatSold(seatNo)) {
        printWarning("此座位已售出，請選擇其他座位。");
        pause();
        return;
    }

    printPageTitle("[購票流程] 選擇票種");
    std::cout << colorText("1", YELLOW) << ". 成人票 320" << std::endl;
    std::cout << colorText("2", YELLOW) << ". 學生票 280" << std::endl;
    std::cout << colorText("3", YELLOW) << ". 兒童票 220" << std::endl;
    const int ticketTypeChoice = readMenuChoice(1, 3);

    std::string ticketType;
    if (ticketTypeChoice == 1) {
        ticketType = "成人票";
    } else if (ticketTypeChoice == 2) {
        ticketType = "學生票";
    } else {
        ticketType = "兒童票";
    }

    std::unique_ptr<Ticket> preview = createTicketByType("預覽票號", showtimeId, cinemaSystem.getMovieTitleById(movieId), seatNo, ticketType);
    printPageTitle("[購票流程] 確認票券");
    displayTicket(*preview);

    if (!askYesNo("是否確認購買")) {
        printInfo("已取消購買");
        pause();
        return;
    }

    std::string message;
    Ticket* ticket = cinemaSystem.purchaseTicket(showtimeId, seatNo, ticketType, message);
    if (ticket == nullptr) {
        printError(message);
    } else {
        std::cout << std::endl;
        std::cout << colorText("╔════════════════════════════╗", GREEN) << std::endl;
        std::cout << colorText("║         購票完成           ║", GREEN) << std::endl;
        std::cout << colorText("╚════════════════════════════╝", GREEN) << std::endl;
        displayTicket(*ticket);
    }
    pause();
}

void UIManager::refundTicket() {
    printPageTitle("[退票] 依票號退票");
    const std::string ticketId = readRequiredLine("請輸入票號：");
    const Ticket* ticket = cinemaSystem.findTicketById(ticketId);
    if (ticket == nullptr) {
        printError("找不到票券");
        pause();
        return;
    }

    displayTicket(*ticket);
    if (!askYesNo("是否確認退票")) {
        printInfo("已取消退票");
        pause();
        return;
    }

    std::string message;
    if (cinemaSystem.refundTicket(ticketId, message)) {
        printSuccess("退票完成，座位已釋放。");
    } else {
        printError(message);
    }
    pause();
}

void UIManager::queryTickets() {
    while (true) {
        printSubMenu("查詢票券", {
            "1. 依票號查詢",
            "2. 顯示所有已售出票券",
            "0. 返回主選單"
        });
        const int choice = readMenuChoice(0, 2);

        if (choice == 0) {
            return;
        }
        if (choice == 1) {
            printPageTitle("[查詢票券] 依票號查詢");
            const std::string ticketId = readRequiredLine("請輸入票號：");
            const Ticket* ticket = cinemaSystem.findTicketById(ticketId);
            if (ticket == nullptr) {
                printError("找不到票券");
            } else {
                displayTicket(*ticket);
            }
            pause();
        } else if (choice == 2) {
            printPageTitle("[查詢票券] 所有已售出票券");
            displayTicketTable();
            pause();
        }
    }
}

void UIManager::showSeatMap() {
    printPageTitle("[座位表] 選擇場次");
    const auto& showtimes = cinemaSystem.getShowtimes();
    if (showtimes.empty()) {
        printInfo("目前沒有場次資料");
        pause();
        return;
    }

    displayShowtimeTable(showtimes);
    const std::string showtimeId = readRequiredLine("請輸入場次 ID：");
    const Showtime* showtime = cinemaSystem.findShowtimeById(showtimeId);
    if (showtime == nullptr) {
        printError("找不到指定 ID。");
        pause();
        return;
    }

    displaySeatMap(*showtime);
    pause();
}

void UIManager::showTotalRevenue() {
    printPageTitle("[營收統計] 查看總營收");
    std::cout << "目前總營收：NT$" << cinemaSystem.calculateTotalRevenue() << std::endl;
    pause();
}

void UIManager::showMovieTicketCounts() {
    printPageTitle("[營收統計] 各電影售票數量");
    const std::map<std::string, int> counts = cinemaSystem.countTicketsByMovie();
    if (counts.empty()) {
        printInfo("目前尚無售票資料");
        pause();
        return;
    }

    printDivider();
    for (const auto& entry : counts) {
        std::cout << "電影：" << entry.first << std::endl;
        std::cout << "售票張數：" << entry.second << " 張" << std::endl;
        printDivider();
    }
    pause();
}

void UIManager::showTicketTypeCounts() {
    printPageTitle("[營收統計] 各票種銷售數量");
    const std::map<std::string, int> counts = cinemaSystem.countTicketsByType();
    const std::map<std::string, int> revenue = cinemaSystem.calculateRevenueByTicketType();
    if (counts.empty()) {
        printInfo("目前尚無售票資料");
        pause();
        return;
    }

    const std::vector<std::string> ticketTypes = {"成人票", "學生票", "兒童票"};
    for (const auto& ticketType : ticketTypes) {
        const auto countIt = counts.find(ticketType);
        const auto revenueIt = revenue.find(ticketType);
        const int count = countIt == counts.end() ? 0 : countIt->second;
        const int subtotal = revenueIt == revenue.end() ? 0 : revenueIt->second;
        std::cout << ticketType << "：" << count << " 張，小計 NT$" << subtotal << std::endl;
    }
    pause();
}

void UIManager::showMovieMenu() {
    while (true) {
        printSubMenu("電影管理", {
            "1. 新增電影",
            "2. 顯示所有電影",
            "3. 查詢電影",
            "4. 刪除電影",
            "0. 返回主選單"
        });

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
        printSubMenu("場次管理", {
            "1. 新增電影場次",
            "2. 顯示所有場次",
            "3. 查詢指定電影場次",
            "0. 返回主選單"
        });

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
        printSubMenu("營收統計", {
            "1. 查看總營收",
            "2. 查看各電影售票數量",
            "3. 查看各票種銷售數量",
            "0. 返回主選單"
        });

        const int choice = readMenuChoice(0, 3);
        switch (choice) {
            case 1:
                showTotalRevenue();
                break;
            case 2:
                showMovieTicketCounts();
                break;
            case 3:
                showTicketTypeCounts();
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
                buyTicket();
                break;
            case 4:
                refundTicket();
                break;
            case 5:
                queryTickets();
                break;
            case 6:
                showSeatMap();
                break;
            case 7:
                showStatisticsMenu();
                break;
            case 8:
                if (cinemaSystem.saveAllData()) {
                    std::cout << std::endl;
                    printSuccess("資料已儲存");
                } else {
                    std::cout << std::endl;
                    showWarnings(cinemaSystem.getSaveWarnings());
                    printWarning("資料儲存未完全成功，請檢查 data/ 檔案狀態。");
                }
                pause();
                break;
            case 0:
                std::cout << std::endl;
                if (askYesNo("離開系統前是否儲存資料")) {
                    if (cinemaSystem.saveAllData()) {
                        printSuccess("資料已儲存");
                    } else {
                        showWarnings(cinemaSystem.getSaveWarnings());
                        printWarning("資料儲存未完全成功。");
                    }
                }
                printInfo("感謝使用電影院售票管理系統，再見！");
                running = false;
                break;
        }
    }
}
