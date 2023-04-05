#pragma once

#include "GameState.hpp"
#include "StoryState.hpp"
#include "InstructionsState.hpp"

#include "../core/Game.hpp"

#include "../MKE/State.hpp"

#include <SFML/Graphics.hpp>

class Game;

class MainMenuState : public mke::State
{
public:
    MainMenuState(Game& game);

    void update() override;
    void render() override;
private:
    Game& game;

    void setupGui();
};