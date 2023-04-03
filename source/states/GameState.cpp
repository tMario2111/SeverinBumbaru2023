#include "GameState.hpp"

GameState::GameState(Game& game) :
    game{ game },
    map{ game.assets }
{
    SPlayer::create(game, *this);
}

void GameState::update()
{
    SPlayer::update(game, *this);
}

void GameState::render()
{
    game.win.draw(map);
}