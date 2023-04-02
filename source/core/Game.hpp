#pragma once

#include "../states/MainMenuState.hpp"

#include "../MKE/StateMachine.hpp"

#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();

    sf::RenderWindow win;
    sf::Time dt;
    mke::StateMachine<> states;
private:
    sf::Clock win_clock;

    void setupWin();
    void setupStates();
    void winEvents();
    void run();
};