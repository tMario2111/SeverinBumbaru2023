#include "MainMenuState.hpp"

MainMenuState::MainMenuState(Game& game) :
    game{ game }
{
    setupGui();
}

void MainMenuState::setupGui()
{
    gui = std::make_unique<tgui::Gui>(game.win);

    gui->loadWidgetsFromFile("gui/main_menu.tgui");

    gui->get<tgui::Button>("play_button")->onPress([&]
    {
        game.states.push<GameState>(game);
    });

    gui->get<tgui::Button>("exit_button")->onPress([&]
    {
        game.win.close();
    });
}

void MainMenuState::update()
{
    
}

void MainMenuState::render()
{

}