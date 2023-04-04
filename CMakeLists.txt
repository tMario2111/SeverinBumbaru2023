cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(SeverinBumbaru2023)

add_executable(SeverinBumbaru2023 main.cpp

    #core
    source/core/Game.hpp source/core/Game.cpp
    source/core/GameData.hpp source/core/GameData.cpp

    #mke
    source/MKE/State.hpp source/MKE/StateMachine.hpp
    source/MKE/AssetManager.hpp source/MKE/AssetManager.cpp
    source/MKE/Input.hpp source/MKE/Input.cpp
    source/MKE/Utility.hpp source/MKE/Utility.cpp
    source/MKE/Animation.hpp source/MKE/Animation.cpp
    source/MKE/SpriteBatch source/MKE/SpriteBatch.cpp
    source/MKE/Random.hpp source/MKE/Random.cpp

    #states
    source/states/MainMenuState.hpp source/states/MainMenuState.cpp
    source/states/GameState.hpp source/states/GameState.cpp

    #map
    source/Map.hpp source/Map.cpp

    #fibo
    source/Fibonacci.hpp source/Fibonacci.cpp

    #components
    source/components/PlayerComponents.hpp
    source/components/CoreComponents.hpp
    source/components/GhostComponents.hpp

    #systems
    source/systems/PlayerSystems.hpp source/systems/PlayerSystems.cpp
    source/systems/CoreSystems.hpp source/systems/CoreSystems.cpp
    source/systems/GhostSystems.hpp source/systems/GhostSystems.cpp
)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

target_link_libraries(SeverinBumbaru2023 PRIVATE
    sfml-system sfml-window sfml-graphics
    EnTT::EnTT
    nlohmann_json::nlohmann_json)