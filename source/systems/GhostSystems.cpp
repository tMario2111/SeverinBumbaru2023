#include "GhostSystems.hpp"

namespace SGhost
{
    void spawn(Game& game, GameState& game_state)
    {
        for (int i = 2; i <= 100; i++)
            create(game, game_state, i);
    }

    void update(Game& game, GameState& game_state)
    {
        movement(game, game_state);
        catchGhost(game, game_state);
        killPlayer(game, game_state);
        arrowMovement(game, game_state);
    }

    void drawToBatch(Game& game, GameState& game_state, mke::SpriteBatch& batch)
    {
        auto& registry = game_state.registry;

        auto view = registry.view<CGhost::Base, CCore::AnimatedSprite>();
        for (const auto entity : view)
        {
            auto& sprite = *view.get<CCore::AnimatedSprite>(entity).sprite;
            if (mke::isOnScreen(sprite, game.win))
                batch.append(*view.get<CCore::AnimatedSprite>(entity).sprite);
        }
    }

    void render(Game& game, GameState& game_state)
    {
        auto& registry = game_state.registry;

        auto view = registry.view<CGhost::Tag, CGhost::Base>();
        for (const auto entity : view)
        {
            auto& text = view.get<CGhost::Tag>(entity).text;
            if (mke::isOnScreen(text, game.win))
                game.win.draw(text);
        }

        if (!game_state.arrow_hidden)
            game.win.draw(game_state.arrow);
    }

    void create(Game& game, GameState& game_state, int i)
    {
        auto& registry = game_state.registry;

        const auto entity = registry.create();

        registry.emplace<CGhost::Base>(entity);

        auto& tag = registry.emplace<CGhost::Tag>(entity);
        tag.k = i;
        tag.text.setFont(game.assets.getFont("font"));
        tag.text.setCharacterSize(22);
        if (i % 2 == 0)
            tag.text.setString(mke::addCommasToNumber(std::to_string(game_state.fibonacci.seq[i / 2])));
        else
            tag.text.setString(mke::addCommasToNumber(std::to_string(
                game.random.getInt<unsigned long long>(100, 10000000))));
        tag.text.setOrigin(tag.text.getLocalBounds().width / 2.f, tag.text.getLocalBounds().height / 2.f);

        auto& animated_sprite = registry.emplace<CCore::AnimatedSprite>(entity);
        animated_sprite.sprite = std::make_unique<sf::Sprite>();

        animated_sprite.animations = std::make_unique<CCore::AnimationMap>();
        auto& animations = *animated_sprite.animations;
        SCore::loadAnimationsFromJson(game, *animated_sprite.sprite, animations, game.data["ghost"]["animations"]);
        animations["walk"]->setSpriteFrame("ghost1");

        auto& sprite = animated_sprite.sprite;
        sprite->setScale(3.f, 3.f); // HARDCODE
        sprite->setOrigin(sprite->getLocalBounds().width / 2.f, sprite->getLocalBounds().height / 2.f);

        // POSITION
        {
            int side = game.random.getInt<int>(0, 3);
            sf::Vector2f position;
            if (side == 0)
            {
                position.x = game.random.getReal<float>(-Map::margin, Map::size_x + Map::margin);
                position.y = game.random.getReal<float>(1.5f * (-Map::margin), -Map::margin);
            }
            else if (side == 1)
            {
                position.x = game.random.getReal<float>(Map::size_x + Map::margin, Map::size_x + 1.5f * Map::margin);
                position.y = game.random.getReal<float>(-Map::margin, Map::size_y + Map::margin);
            }
            else if (side == 2)
            {
                position.x = game.random.getReal<float>(-Map::margin, Map::size_x + Map::margin);
                position.y = game.random.getReal<float>(Map::size_y + Map::margin, Map::size_y + 1.5f * Map::margin);
            }
            else
            {
                position.x = game.random.getReal<float>(1.5f * (-Map::margin), -Map::margin);
                position.y = game.random.getReal<float>(-Map::margin, Map::size_y + Map::margin);
            }
            sprite->setPosition(position);
        }

        auto& movement = registry.emplace<CGhost::Movement>(entity);
        movement.min_wait_time = sf::seconds(1.f);
        movement.max_wait_time = sf::seconds(5.f);
        movement.move_radius = 500.f;
        movement.speed = 200.f;

        movement.target = game_state.map.getRandomPoint(game.random);

        const auto angle = mke::getRotationToPoint(sprite->getPosition(), movement.target);
        movement.velocity.x = movement.speed * cosf(angle);
        movement.velocity.y = movement.speed * sinf(angle);
    }

    void movement(Game& game, GameState& game_state)
    {
        auto& registry = game_state.registry;

        auto view = registry.view<CGhost::Base, CGhost::Movement, CCore::AnimatedSprite, CGhost::Tag>();
        for (const auto entity : view)
        {
            auto& movement = view.get<CGhost::Movement>(entity);
            auto& animations = *view.get<CCore::AnimatedSprite>(entity).animations;
            auto& sprite = *view.get<CCore::AnimatedSprite>(entity).sprite;
            auto& text = view.get<CGhost::Tag>(entity).text;

            if (movement.state == CGhost::Movement::State::Moving)
            {
                animations["walk"]->run(game.dt);
                sprite.move(sf::Vector2f{ movement.velocity.x * game.dt.asSeconds(), 
                    movement.velocity.y * game.dt.asSeconds() });

                if (movement.velocity.x < 0.f)
                    sprite.setScale(-fabsf(sprite.getScale().x), sprite.getScale().y);
                else
                    sprite.setScale(+fabsf(sprite.getScale().x), sprite.getScale().y);
                if (mke::squaredDistance(sprite.getPosition(), movement.target) <= 100.f)
                {
                    movement.state = CGhost::Movement::State::Waiting;
                    movement.delay = sf::seconds(game.random.getReal<float>(movement.min_wait_time.asSeconds(), 
                        movement.max_wait_time.asSeconds()));
                }
                if (sprite.getPosition().x <= -2 * Map::margin || sprite.getPosition().y <= -2 * Map::margin ||
                    sprite.getPosition().x >= Map::size_x + 2 * Map::margin || 
                    sprite.getPosition().y >= Map::size_y + 2 * Map::margin)
                        sprite.setPosition(movement.target);
            }
            else if (movement.state == CGhost::Movement::State::Waiting)
            {
                animations["walk"]->run(game.dt);
                movement.clock += game.dt;
                if (movement.clock >= movement.delay)
                {
                    movement.state = CGhost::Movement::State::Moving;
                    movement.clock = sf::Time::Zero;
                    movement.target.x = game.random.getReal<float>(sprite.getPosition().x - movement.move_radius, 
                        sprite.getPosition().x + movement.move_radius);
                    movement.target.y = game.random.getReal<float>(sprite.getPosition().y - movement.move_radius,
                        sprite.getPosition().y + movement.move_radius);

                    movement.target.x = std::clamp(movement.target.x, 0.f, Map::size_x);
                    movement.target.y = std::clamp(movement.target.y, 0.f, Map::size_y);

                    const auto angle = mke::getRotationToPoint(sprite.getPosition(), movement.target);
                    movement.velocity.x = movement.speed * cosf(angle);
                    movement.velocity.y = movement.speed * sinf(angle);
                }
            }
            else if (movement.state == CGhost::Movement::State::Bad)
            {
                animations["bad_ghost_walk"]->run(game.dt);
                float direction = 
                    mke::getRotationToPoint(sprite.getPosition(), SPlayer::getPlayerPosition(game, game_state));
                
                sf::Vector2f velocity{};
                velocity.x = movement.speed * cosf(direction) * game.dt.asSeconds();
                velocity.y = movement.speed * sinf(direction) * game.dt.asSeconds();

                sprite.move(velocity);

                if (SPlayer::getPlayerPosition(game, game_state).x < sprite.getPosition().x)
                    sprite.setScale(-fabsf(sprite.getScale().x), sprite.getScale().y);
                else
                    sprite.setScale(+fabsf(sprite.getScale().x), sprite.getScale().y);
            }
            else // Dying
            {
                animations["dying"]->run(game.dt);
                if (animations["dying"]->getLoopCount() >= 1)
                {
                    registry.destroy(entity);
                    continue;
                }
            }

            text.setPosition(sprite.getPosition().x, sprite.getPosition().y - 40.f);
        }
    }

    void catchGhost(Game& game, GameState& game_state)
    {
        auto& registry = game_state.registry;

        if (!game.input.isMouseButtonReleased(sf::Mouse::Left))
            return;

        const auto mouse_pos = game.win.mapPixelToCoords(sf::Mouse::getPosition(game.win));
        auto view = game_state.registry.view<CGhost::Base, CCore::AnimatedSprite, CGhost::Tag, CGhost::Movement>();
        for (const auto entity : view)
        {
            auto& sprite = *view.get<CCore::AnimatedSprite>(entity).sprite;
            auto& tag = view.get<CGhost::Tag>(entity);
            auto& movement = view.get<CGhost::Movement>(entity);

            if (sprite.getGlobalBounds().contains(mouse_pos))
            {
                if (tag.k % 2 == 0 && tag.k / 2 == SPlayer::getScore(game, game_state) + 3)
                {
                    SPlayer::incrementScore(game, game_state);
                    game_state.timer += sf::seconds(15.f);
                    if (game.random.getInt(0, 1) == 0)
                    {
                        movement.state = CGhost::Movement::State::Dying;
                        create(game, game_state, 99); // Random odd number
                    }
                    else 
                    {
                        movement.state = CGhost::Movement::State::Bad;
                        movement.speed = game.random.getReal<float>(50.f, 200.f);
                    }
                }
                else
                    game_state.timer -= sf::seconds(5.f);
            }
        }
    }

    void killPlayer(Game& game, GameState& game_state)
    {
        auto& registry = game_state.registry;

        auto view = registry.view<CGhost::Movement, CGhost::Base, CCore::AnimatedSprite>();
        for (const auto entity : view)
        {
            if (Collision::PixelPerfectTest(*view.get<CCore::AnimatedSprite>(entity).sprite, 
                SPlayer::getPlayerSprite(game, game_state), 166))
                game_state.game_over = true;
        }
    }

    void arrowMovement(Game& game, GameState& game_state)
    {
        sf::Vector2f ghost_position{};
        {
            auto view = game_state.registry.view<CGhost::Base, CCore::AnimatedSprite, CGhost::Tag>();
            for (const auto entity : view)
            {
                if (view.get<CGhost::Tag>(entity).k % 2 == 0 && 
                    view.get<CGhost::Tag>(entity).k / 2 == SPlayer::getScore(game, game_state) + 3)
                {
                    ghost_position = view.get<CCore::AnimatedSprite>(entity).sprite->getPosition();
                    break;
                }
            }
        }
        auto player_position = SPlayer::getPlayerPosition(game, game_state);
        auto m1 = player_position.x - ghost_position.x;
        auto m2 = player_position.y - ghost_position.y;
        if (fabsf(m1) > fabsf(m2))
        {
            if (m1 < 0.f)
                game_state.arrow.setRotation(0.f);
            else 
                game_state.arrow.setRotation(180.f);
        }
        else
        {
            if (m2 < 0.f)
                game_state.arrow.setRotation(90.f);
            else
                game_state.arrow.setRotation(270.f);
        }

        game_state.arrow.setPosition(player_position.x, player_position.y - 75.f);

        if (mke::squaredDistance(ghost_position, player_position) <= mke::pow2(1200.f))
            game_state.arrow_hidden = true;
        else
            game_state.arrow_hidden = false;
    }
}