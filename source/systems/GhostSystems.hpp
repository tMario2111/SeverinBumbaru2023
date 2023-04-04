#pragma once

#include "../components/CoreComponents.hpp"
#include "../components/GhostComponents.hpp"

#include "../Map.hpp"
#include "../Fibonacci.hpp"
#include "../Collision.h"

#include "CoreSystems.hpp"

#include "../MKE/SpriteBatch.hpp"
#include "../MKE/Utility.hpp"

#include "../core/Game.hpp"
#include "../states/GameState.hpp"

class Game;
class GameState;

namespace SGhost
{
    void spawn(Game& game, GameState& game_state);
    void update(Game& game, GameState& game_state);
    void drawToBatch(Game& game, GameState& game_state, mke::SpriteBatch& batch);
    void render(Game& game, GameState& game_state);

    void create(Game& game, GameState& game_state, int i);
    void movement(Game& game, GameState& game_state);
    void catchGhost(Game& game, GameState& game_state);
    void killPlayer(Game& game, GameState& game_state);
    void arrowMovement(Game& game, GameState& game_state);
}