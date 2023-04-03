#pragma once

#include "../Map.hpp"

#include "../core/Game.hpp"

#include "../MKE/State.hpp"

#include <SFML/Graphics.hpp>

class Game;

class GameState : public mke::State
{
public:
    GameState(Game& game);

    void update() override;
    void render() override;
private:
    Game& game;
    Map map;
};