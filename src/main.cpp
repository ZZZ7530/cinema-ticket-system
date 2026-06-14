#include <clocale>
#include <iostream>

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
}  // namespace

int main() {
    initializeConsoleEncoding();
    std::cout << "電影院售票管理系統啟動成功" << std::endl;
    return 0;
}
