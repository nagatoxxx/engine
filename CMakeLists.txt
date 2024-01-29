cmake_minimum_required(VERSION 3.10)

set(NAME engine)

project(${NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -g")

file(GLOB SOURCE "engine/*.cpp" "graphics/*.cpp" "math/*.cpp" "utility/*.cpp" "main.cpp")

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(${NAME} ${SOURCE})

target_link_libraries(${NAME} PRIVATE sfml-graphics sfml-window sfml-system)
