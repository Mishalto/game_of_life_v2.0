cmake_minimum_required(VERSION 3.28)
project(game_of_life_v2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# set(SFML_DIR "G:/Code/SFML-3.0.0/lib/cmake/SFML")

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)
add_executable(game_of_life_v2.0 src/main.cpp)

# find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio Network)

target_link_libraries(game_of_life_v2.0 PRIVATE SFML::Graphics)

target_include_directories(game_of_life_v2.0 PRIVATE include)

target_compile_options(game_of_life_v2.0 PRIVATE -Wall -Wextra -Werror)
