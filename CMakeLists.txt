cmake_minimum_required(VERSION 3.22.1)
project(task_manager C)

set(CMAKE_C_STANDARD 11)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(task_manager src/main.c
        src/main.c
        src/process_viewer.h
        src/process_viewer.h
        src/process_viewer.c)
target_link_libraries(task_manager ${CURSES_LIBRARIES})
