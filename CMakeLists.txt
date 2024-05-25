cmake_minimum_required(VERSION 3.16)
project(Seletkov_KV_91_game_maze)

set(CMAKE_CXX_STANDARD 14)

set(SFML_INCLUDE_DIR "E://Dislavok//Libraries//SFML-2.5.1//include//SFML")
set(SFML_LIBRARY_DIR "E://Dislavok//Libraries//SFML-2.5.1//lib")
set(SFML_DIR "E://Dislavok//Libraries//SFML-2.5.1//lib//cmake//SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_executable(Seletkov_KV_91_game_maze main.cpp)
target_link_libraries (Seletkov_KV_91_game_maze sfml-graphics sfml-window sfml-system sfml-audio)