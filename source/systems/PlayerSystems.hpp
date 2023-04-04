#pragma once

#include "../components/PlayerComponents.hpp"
#include "../components/CoreComponents.hpp"

#include "../systems/CoreSystems.hpp"

#include "../Map.hpp"

#include "../core/Game.hpp"
#include "../states/GameState.hpp"

#include "../MKE/SpriteBatch.hpp"
#include "../MKE/Utility.hpp"

#include <cmath>

class Game;
class GameState;

namespace SPlayer
{
    void create(Game& game, GameState& game_state);
    void update(Game& game, GameState& game_state);
    void drawToBatch(Game& game, GameState& game_state, mke::SpriteBatch& batch);
    int getScore(Game& game, GameState& game_state);
    void incrementScore(Game& game, GameState& game_state);
    sf::Vector2f getPlayerPosition(Game& game, GameState& game_state);
    sf::Sprite& getPlayerSprite(Game& game, GameState& game_state);

    void movement(Game& game, GameState& game_state);
}