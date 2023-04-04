#include "GameState.hpp"

GameState::GameState(Game& game) :
    game{ game },
    map{ game.assets },
    hud{ game.win, game.assets, fibonacci }
{
    SPlayer::create(game, *this);

    // Ghost spawn
    SGhost::spawn(game, *this);
}

void GameState::updateBatch()
{
    batch.clear();

    SPlayer::drawToBatch(game, *this, batch);
    SGhost::drawToBatch(game, *this, batch);
}

void GameState::update()
{
    SPlayer::update(game, *this);
    SGhost::update(game, *this);

    hud.setScore(SPlayer::getScore(game, *this));

    updateBatch();
}

void GameState::render()
{
    game.win.draw(map);
    game.win.draw(batch, &game.assets.getAtlasTexture("atlas"));
    SGhost::render(game, *this);
    hud.render();
}