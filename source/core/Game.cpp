#include "Game.hpp"

Game::Game()
{
    setupWin();
    setupStates();

    run();
}

void Game::setupWin()
{
    win.create(sf::VideoMode{ 800, 800 }, "Severin Bumbaru 2023", sf::Style::Close);
    win.setFramerateLimit(0);
    win.setVerticalSyncEnabled(true);
}

void Game::setupStates()
{
    states.push<MainMenuState>(*this);
}

void Game::winEvents()
{
    dt = win_clock.restart();
    for (sf::Event event{}; win.pollEvent(event);)
        switch (event.type)
        {
        case sf::Event::Closed:
            win.close();
            break;
        default:
            break;
        }
}

void Game::run()
{
    while (win.isOpen())
    {
        winEvents();

        states.top().update();

        win.clear();
        states.top().render();
        win.display();
    }
}