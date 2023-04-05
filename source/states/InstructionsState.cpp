#include "InstructionsState.hpp"

InstructionsState::InstructionsState(Game& game) : 
    game{ game }
{
    setupGui();
}

void InstructionsState::setupGui()
{
    gui = std::make_unique<tgui::Gui>(game.win);

    gui->loadWidgetsFromFile("gui/instructions.tgui");

    gui->get<tgui::Button>("back_button")->onPress([&]
    {
        terminate = true;
    });
}

void InstructionsState::update()
{
    if (terminate)
    {
        game.states.pop();
        return;
    }
}

void InstructionsState::render()
{

}