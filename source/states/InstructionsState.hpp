#pragma once

#include <SFML/Graphics.hpp>

#include "../MKE/State.hpp"

#include "../core/Game.hpp"

class Game;

class InstructionsState : public mke::State
{
public:
    InstructionsState(Game& game);

    void update() override;
    void render() override;
private:
    Game& game;

    void setupGui();
    bool terminate = false;
};