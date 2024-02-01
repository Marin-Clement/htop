cmake_minimum_required(VERSION 3.22.1)
project(gestionnaire_taches C)

set(CMAKE_C_STANDARD 11)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(gestionnaire_taches src/main.c
        src/main.c
        src/process_viewer.h
        src/process_viewer.h
        src/process_viewer.c)
target_link_libraries(gestionnaire_taches ${CURSES_LIBRARIES})
