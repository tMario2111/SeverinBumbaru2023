#pragma once

#include "MainMenuState.hpp"
#include "GameState.hpp"

#include "../core/Game.hpp"

#include "../MKE/State.hpp"

#include <SFML/Graphics.hpp>

class Game;

class GameOverState : public mke::State
{
public:
    GameOverState(Game& game);

    void update() override;
    void render() override;
private:
    Game& game;

    bool replay = false;
    bool exit = false;

    void setupGui();
};