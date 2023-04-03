#pragma once

#include "../Map.hpp"

#include "../systems/PlayerSystems.hpp"

#include "../core/Game.hpp"
#include "../MKE/State.hpp"

#include <entt/entt.hpp>

#include <SFML/Graphics.hpp>

class Game;

class GameState : public mke::State
{
public:
    GameState(Game& game);

    Game& game;
    entt::registry registry;

    void update() override;
    void render() override;
private:
    Map map;
};