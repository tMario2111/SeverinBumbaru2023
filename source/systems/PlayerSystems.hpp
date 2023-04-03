#pragma once

#include "../components/PlayerComponents.hpp"

#include "../core/Game.hpp"
#include "../states/GameState.hpp"

#include "../MKE/Utility.hpp"

class Game;
class GameState;

namespace SPlayer
{
    void create(Game& game, GameState& game_state);
    void update(Game& game, GameState& game_state);

    void movement(Game& game, GameState& game_state);
}