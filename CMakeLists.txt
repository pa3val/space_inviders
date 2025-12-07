cmake_minimum_required(VERSION 3.10.0)
project(space_inviders VERSION 0.1.0 LANGUAGES C CXX)

add_executable(space_inviders
 main.cpp
 game_manager.cpp
 entity.cpp)

find_package(Curses REQUIRED)

target_link_libraries(space_inviders PRIVATE ${CURSES_LIBRARIES})