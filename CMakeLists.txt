cmake_minimum_required(VERSION 3.10)
project(game_of_life_v2.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SFML_DIR G:/Code/SFML-3.0.0/lib/cmake/SFML)

add_executable(game_of_life_v2.0 main.cpp)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio Network)

target_link_libraries(game_of_life_v2.0 PRIVATE SFML::Graphics SFML::Audio SFML::Network)

target_compile_options(game_of_life_v2.0 PRIVATE -Wall -Wextra -Werror)