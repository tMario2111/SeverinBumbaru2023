#pragma once

#include <SFML/Graphics.hpp>

#include "../MKE/State.hpp"

#include "../core/Game.hpp"

class Game;

class StoryState : public mke::State
{
public:
    StoryState(Game& game);

    void update() override;
    void render() override;
private:
    Game& game;

    void setupGui();
    bool terminate = false;
};