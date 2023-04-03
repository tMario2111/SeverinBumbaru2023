#include "GameState.hpp"

GameState::GameState(Game& game) :
    game{ game },
    map{ game.assets }
{

}

void GameState::update()
{

}

void GameState::render()
{
    game.win.draw(map);
}