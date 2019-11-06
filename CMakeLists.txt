cmake_minimum_required(VERSION 3.15)
project(opob)

set(CMAKE_CXX_STANDARD 17)

add_executable(opob main.cpp func.cpp func.h)

set(SFML_INCLUDE_DIR "/usr/local/include/SFML")
set(SFML_LIBRARY_DIR "/usr/local/lib")
set(SFML_DIR "/usr/local/lib/cmake")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
target_link_libraries (opob sfml-graphics sfml-window sfml-system)
