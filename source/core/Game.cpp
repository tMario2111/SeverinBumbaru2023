#include "Game.hpp"

Game::Game()
{
    random.setUniqueSeed();

    setupWin();
    loadAssets();
    setupStates();

    run();
}

void Game::setupWin()
{
    sf::VideoMode video_mode{};
    video_mode = sf::VideoMode::getDesktopMode();
    video_mode.height++;
    win.create(video_mode, "Fibonacci's evolution", sf::Style::None);
    win.setFramerateLimit(0);
    win.setVerticalSyncEnabled(true);
}

void Game::loadAssets()
{
    assets.loadFont("font", "assets/BigPixelDemo.otf");

    assets.loadTexture("background", "assets/background.png");
    // assets.getTexture("background").setRepeated(true);

    assets.loadAtlas("atlas", "assets/atlas.png");

    assets.loadTexture("arrow", "assets/arrow.png");

    sounds.setMusicFilename("fibonacci", "assets/fibonacci_song.wav");
    sounds.getMusic().setLoop(true);
}

void Game::setupStates()
{
    states.push<MainMenuState>(*this);
}

void Game::winEvents()
{
    input.update();
    dt = win_clock.restart();
    for (sf::Event event{}; win.pollEvent(event);)
    {
        input.processEvent(event);
        if (states.top().gui != nullptr)
            states.top().gui->handleEvent(event);
        switch (event.type)
        {
        case sf::Event::Closed:
            win.close();
            break;
        default:
            break;
        }
    }
    if (input.isKeyPressed(sf::Keyboard::Escape))
        win.close();
}

void Game::run()
{
    while (win.isOpen())
    {
        winEvents();

        states.top().update();

        win.clear();
        states.top().render();
        if (states.top().gui != nullptr)
            states.top().gui->draw();
        win.display();
    }
}