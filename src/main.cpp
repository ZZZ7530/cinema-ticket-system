#include "Movie.h"
#include "Showtime.h"
#include "Ticket.h"
#include "User.h"

#include <clocale>
#include <iostream>
#include <memory>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

namespace {
void initializeConsoleEncoding() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::setlocale(LC_ALL, ".UTF-8");
}

void printSectionTitle(const std::string& title) {
    std::cout << "\n========================================" << std::endl;
    std::cout << title << std::endl;
    std::cout << "========================================" << std::endl;
}
}  // namespace

int main() {
    initializeConsoleEncoding();

    std::cout << "電影院售票管理系統啟動成功" << std::endl;
    std::cout << "Iteration 2：核心類別與 OOP 繼承測試" << std::endl;

    printSectionTitle("Movie 類別測試");
    Movie movie("M001", "鬼滅之刃劇場版", "動畫", 120);
    movie.display();
    std::cout << "檔案格式：" << movie.toFileString() << std::endl;

    printSectionTitle("Showtime 類別與座位表測試");
    Showtime showtime("S001", "M001", "2026-01-10", "14:00", "A廳", 3, 6, {"A3", "B2"});
    showtime.display();
    std::cout << "售出 C5：" << (showtime.sellSeat("C5") ? "成功" : "失敗") << std::endl;
    std::cout << "釋放 B2：" << (showtime.releaseSeat("B2") ? "成功" : "失敗") << std::endl;
    showtime.displaySeatMap();
    std::cout << "檔案格式：" << showtime.toFileString() << std::endl;

    printSectionTitle("Ticket 繼承與多型測試");
    std::vector<std::unique_ptr<Ticket>> tickets;
    tickets.push_back(std::make_unique<AdultTicket>("T001", "S001", movie.getTitle(), "A1"));
    tickets.push_back(std::make_unique<StudentTicket>("T002", "S001", movie.getTitle(), "A2"));
    tickets.push_back(std::make_unique<ChildTicket>("T003", "S001", movie.getTitle(), "A3"));
    tickets.push_back(createTicketByType("T004", "S001", movie.getTitle(), "A4", "學生票"));

    int totalPrice = 0;
    for (const auto& ticket : tickets) {
        ticket->display();
        totalPrice += ticket->calculatePrice();
    }
    std::cout << "多型計算總票價：NT$" << totalPrice << std::endl;
    std::cout << "票券檔案格式範例：" << tickets.front()->toFileString() << std::endl;

    printSectionTitle("User 繼承與多型測試");
    std::vector<std::unique_ptr<User>> users;
    users.push_back(std::make_unique<Admin>("系統管理員"));
    users.push_back(std::make_unique<Customer>("一般顧客"));

    for (const auto& user : users) {
        user->display();
    }

    printSectionTitle("Iteration 2 測試完成");
    std::cout << "Movie、Showtime、Ticket、User 類別皆可正常建立與使用。" << std::endl;
    return 0;
}
