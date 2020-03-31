cmake_minimum_required(VERSION 3.15)
project(projekt_indywidualny)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(projekt_indywidualny src/main.cpp src/constants.h)

target_link_libraries(projekt_indywidualny ${SDL2_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -mwindows)
