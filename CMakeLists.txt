cmake_minimum_required(VERSION 3.15)
project(projekt_indywidualny)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)
find_package(SFML 2 COMPONENTS REQUIRED system window graphics network audio)
include_directories(${SDL2_INCLUDE_DIR})

set(SOURCE_FILES src/main.cpp src/CHIP8.cpp src/Graphics.cpp src/Input.cpp src/Timer.cpp src/Beeper.cpp)
add_executable(projekt_indywidualny ${SOURCE_FILES})

target_link_libraries(projekt_indywidualny ${SDL2_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -mwindows)
