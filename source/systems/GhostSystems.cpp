#include "GhostSystems.hpp"

namespace SGhost
{
    void spawn(Game& game, GameState& game_state)
    {
        for (int i = 0; i < 100; i++)
            create(game, game_state);
    }

    void update(Game& game, GameState& game_state)
    {
        movement(game, game_state);
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

    void create(Game& game, GameState& game_state)
    {
        auto& registry = game_state.registry;

        const auto entity = registry.create();

        registry.emplace<CGhost::Base>(entity);

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

        auto view = registry.view<CGhost::Base, CGhost::Movement, CCore::AnimatedSprite>();
        for (const auto entity : view)
        {
            auto& movement = view.get<CGhost::Movement>(entity);
            auto& animations = *view.get<CCore::AnimatedSprite>(entity).animations;
            auto& sprite = *view.get<CCore::AnimatedSprite>(entity).sprite;

            animations["walk"]->run(game.dt);

            if (movement.state == CGhost::Movement::State::Moving)
            {
                sprite.move(sf::Vector2f{ movement.velocity.x * game.dt.asSeconds(), 
                    movement.velocity.y * game.dt.asSeconds() });

                if (movement.velocity.x < 0.f)
                    sprite.setScale(-fabsf(sprite.getScale().x), sprite.getScale().y);
                else
                    sprite.setScale(+fabsf(sprite.getScale().x), sprite.getScale().y);
                if (mke::squaredDistance(sprite.getPosition(), movement.target) <= 5.f)
                {
                    movement.state = CGhost::Movement::State::Waiting;
                    movement.delay = sf::seconds(game.random.getReal<float>(movement.min_wait_time.asSeconds(), 
                        movement.max_wait_time.asSeconds()));
                }
            }
            else // State::Waiting
            {
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
        }
    }
}