#include "MainMenuState.hpp"

MainMenuState::MainMenuState(Game& game) :
    game{ game }
{

}

void MainMenuState::update()
{

}

void MainMenuState::render()
{
    sf::RectangleShape rect{ sf::Vector2f{ 200.f, 200.f } };
    game.win.draw(rect);
}