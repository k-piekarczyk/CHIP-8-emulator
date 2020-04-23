cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME "projekt_indywidualny")
project(${PROJECT_NAME})

set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/libs/SFML-2.5.1/lib/cmake/SFML")

IF(CMAKE_BUILD_TYPE MATCHES Debug)
    file(GLOB ALL_REQUIRED_DLL "libs/required_dll/debug/*.dll")
ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
    file(GLOB ALL_REQUIRED_DLL "libs/required_dll/release/*.dll")
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

file(COPY ${ALL_REQUIRED_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-window sfml-system)

