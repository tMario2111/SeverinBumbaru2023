#include "GameOverState.hpp"

GameOverState::GameOverState(Game& game) :
    game{ game }
{
    setupGui();
}

void GameOverState::setupGui()
{
    gui = std::make_unique<tgui::Gui>(game.win);

    gui->loadWidgetsFromFile("gui/game_over.tgui");

    gui->get<tgui::Button>("exit_button")->onPress([&]
    {
        exit = true;
    });
}

void GameOverState::update()
{
    if (replay)
    {
        game.states.popStatesUntil<MainMenuState>();
        game.states.push<GameState>(game);
        return;
    }
    if (exit)
    {
        game.states.popStatesUntil<MainMenuState>();
        return;
    }
}

void GameOverState::render()
{

}