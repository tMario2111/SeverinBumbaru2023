#pragma once

#include "../states/MainMenuState.hpp"

#include "../MKE/AssetManager.hpp"
#include "../MKE/Input.hpp"
#include "../MKE/StateMachine.hpp"
#include "../MKE/Random.hpp"
#include "../MKE/SoundManager.hpp"

#include "GameData.hpp"

#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();

    sf::RenderWindow win;
    sf::Time dt;
    mke::AssetManager assets;
    mke::Input input;
    mke::StateMachine<> states;
    mke::Random random;
    mke::SoundManager sounds;
    GameData data;
private:
    sf::Clock win_clock;

    void setupWin();
    void loadAssets();
    void setupStates();
    void winEvents();
    void run();
};