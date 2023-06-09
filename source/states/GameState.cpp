#include "GameState.hpp"

GameState::GameState(Game& game) :
    game{ game },
    map{ game.assets },
    hud{ game.win, game.assets, fibonacci }
{
    game.sounds.getMusicAs("fibonacci").setVolume(50.f);
    game.sounds.getMusic().play();

    SPlayer::create(game, *this);
    setupArrow();

    // Ghost spawn
    SGhost::spawn(game, *this);
}

void GameState::setupArrow()
{
    arrow.setTexture(game.assets.getTexture("arrow"));
    arrow.setScale(0.1f, 0.1f);
    arrow.setOrigin(arrow.getLocalBounds().width / 2.f, arrow.getLocalBounds().height / 2.f);
}

void GameState::updateBatch()
{
    batch.clear();

    SPlayer::drawToBatch(game, *this, batch);
    SGhost::drawToBatch(game, *this, batch);
}

void GameState::update()
{
    if (game_over)
    {
        game.sounds.getMusic().stop();
        game.states.push<GameOverState>(game);
        return;
    }

    SPlayer::update(game, *this);
    SGhost::update(game, *this);

    hud.setScore(SPlayer::getScore(game, *this));

    timer -= game.dt;
    hud.setTimer(timer.asSeconds());
    if (timer.asSeconds() <= 0.f)
        game_over = true;

    updateBatch();
}

void GameState::render()
{
    game.win.draw(map);
    game.win.draw(batch, &game.assets.getAtlasTexture("atlas"));
    SGhost::render(game, *this);
    hud.render();
}