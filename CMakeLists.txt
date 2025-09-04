cmake_minimum_required(VERSION 3.10)


project(rminesweeper)

add_executable(minesweeper minesweeper.c)
add_library(cells SHARED headers/cells.c)
add_library(buttons SHARED headers/buttons.c)

target_link_libraries(minesweeper PRIVATE raylib cells buttons)