cmake_minimum_required(VERSION 3.10)
project(GaDaeroJourney)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(GaDaeroJourney src/main.cpp src/game.cpp src/character.cpp src/item.cpp src/path.cpp src/event.cpp)

target_link_libraries(GaDaeroJourney SDL2 SDL2_image SDL2_mixer SDL2_ttf)