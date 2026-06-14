#include "UIManager.h"

#include "CinemaSystem.h"

#include <iostream>
#include <limits>
#include <string>

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

void UIManager::showMainMenu() const {
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "        電影院售票管理系統" << std::endl;
    std::cout << "========================================" << std::endl;
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
                showNotImplemented("新增電影");
                break;
            case 2:
                showNotImplemented("顯示所有電影");
                break;
            case 3:
                showNotImplemented("查詢電影");
                break;
            case 4:
                showNotImplemented("刪除電影");
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
                showNotImplemented("新增電影場次");
                break;
            case 2:
                showNotImplemented("顯示所有場次");
                break;
            case 3:
                showNotImplemented("查詢指定電影場次");
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
                showNotImplemented("儲存資料");
                break;
            case 0:
                std::cout << std::endl;
                std::cout << "感謝使用電影院售票管理系統，再見！" << std::endl;
                running = false;
                break;
        }
    }
}
