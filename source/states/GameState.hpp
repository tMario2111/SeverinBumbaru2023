#pragma once

#include "GameOverState.hpp"

#include "../Map.hpp"
#include "../Fibonacci.hpp"
#include "../HUD.hpp"

#include "../systems/PlayerSystems.hpp"
#include "../systems/GhostSystems.hpp"

#include "../core/Game.hpp"
#include "../MKE/State.hpp"
#include "../MKE/SpriteBatch.hpp"

#include <entt/entt.hpp>

#include <SFML/Graphics.hpp>

class Game;

class GameState : public mke::State
{
public:
    GameState(Game& game);

    Game& game;
    entt::registry registry;
    Map map;
    Fibonacci fibonacci;
    HUD hud;
    sf::Time timer = sf::seconds(60.f);

    bool game_over = false;

    void update() override;
    void render() override;
private:
    mke::SpriteBatch batch;

    void updateBatch();
};