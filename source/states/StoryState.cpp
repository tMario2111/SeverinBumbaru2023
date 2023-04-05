#include "StoryState.hpp"

StoryState::StoryState(Game& game) : 
    game{ game }
{
    setupGui();
}

void StoryState::setupGui()
{
    gui = std::make_unique<tgui::Gui>(game.win);

    gui->loadWidgetsFromFile("gui/story.tgui");

    gui->get<tgui::Button>("back_button")->onPress([&]
    {
        terminate = true;
    });
}

void StoryState::update()
{
    if (terminate)
    {
        game.states.pop();
        return;
    }
}

void StoryState::render()
{

}