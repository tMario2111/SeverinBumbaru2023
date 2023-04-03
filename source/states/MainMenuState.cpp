#include "MainMenuState.hpp"

MainMenuState::MainMenuState(Game& game) :
    game{ game }
{
    
}

void MainMenuState::update()
{
    game.states.push<GameState>(game);
}

void MainMenuState::render()
{

}