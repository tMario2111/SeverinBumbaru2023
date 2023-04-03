#include "GameState.hpp"

GameState::GameState(Game& game) :
    game{ game },
    map{ game.assets }
{
    SPlayer::create(game, *this);
}

void GameState::updateBatch()
{
    batch.clear();

    SPlayer::drawToBatch(game, *this, batch);
}

void GameState::update()
{
    SPlayer::update(game, *this);

    updateBatch();
}

void GameState::render()
{
    game.win.draw(map);
    game.win.draw(batch, &game.assets.getAtlasTexture("atlas"));
}