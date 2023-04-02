cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(SeverinBumbaru2023)

add_executable(SeverinBumbaru2023 main.cpp

    #core
    source/core/Game.hpp source/core/Game.cpp

    #mke
    source/mke/State.hpp source/mke/StateMachine.hpp

    #states
    source/states/MainMenuState.hpp source/states/MainMenuState.cpp
)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

target_link_libraries(SeverinBumbaru2023 PRIVATE sfml-system sfml-window sfml-graphics)