cmake_minimum_required(VERSION 3.16)

project(CinemaTicketSystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(cinema_ticket_system
    src/main.cpp
    src/CinemaSystem.cpp
    src/FileManager.cpp
    src/Movie.cpp
    src/Showtime.cpp
    src/Ticket.cpp
    src/UIManager.cpp
    src/User.cpp
)

target_include_directories(cinema_ticket_system PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(cinema_ticket_system PRIVATE /utf-8)
elseif(MINGW OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(cinema_ticket_system PRIVATE
        -finput-charset=UTF-8
        -fexec-charset=UTF-8
    )
endif()
