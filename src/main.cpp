#include "CinemaSystem.h"
#include "UIManager.h"

#include <clocale>

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

    CinemaSystem cinemaSystem;
    UIManager uiManager(cinemaSystem);
    uiManager.run();

    return 0;
}
