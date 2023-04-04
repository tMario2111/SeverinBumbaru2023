#include "PlayerSystems.hpp"

namespace SPlayer
{
    void create(Game& game, GameState& game_state)
    {
        auto& registry = game_state.registry;

        const auto entity = registry.create();

        registry.emplace<CPlayer::Base>(entity);

        auto& animated_sprite = registry.emplace<CCore::AnimatedSprite>(entity);
        animated_sprite.sprite = std::make_unique<sf::Sprite>();

        animated_sprite.animations = std::make_unique<CCore::AnimationMap>();
        auto& animations = *animated_sprite.animations;
        SCore::loadAnimationsFromJson(game, *animated_sprite.sprite, animations, game.data["player"]["animations"]);
        animations["idle"]->setSpriteFrame("Steve1");

        auto& sprite = animated_sprite.sprite;
        sprite->setScale(1.75f, 1.75f); // HARDCODE
        sprite->setOrigin(sprite->getLocalBounds().width / 2.f, sprite->getLocalBounds().height / 2.f);
        
        auto& movement = registry.emplace<CPlayer::Movement>(entity);
        movement.movement_speed = 500.f; // HARDCODE
        movement.position = sf::Vector2f{ Map::size_x / 2.f, Map::size_y / 2.f };
    }

    void update(Game& game, GameState& game_state)
    {
        movement(game, game_state);
    }

    void drawToBatch(Game& game, GameState& game_state, mke::SpriteBatch& batch)
    {
        auto& registry = game_state.registry;

        auto view = registry.view<CPlayer::Base, CCore::AnimatedSprite>();
        for (const auto entity : view)
        {
            batch.append(*view.get<CCore::AnimatedSprite>(entity).sprite);
        }
    }

    void movement(Game& game, GameState& game_state)
    {
        auto& registry = game_state.registry;

        auto view = registry.view<CPlayer::Base, CPlayer::Movement, CCore::AnimatedSprite>();
        for (const auto entity : view)
        {
            auto& movement = view.get<CPlayer::Movement>(entity);
            const auto movement_speed = movement.movement_speed;
            auto& position = movement.position;
            auto& animations = *view.get<CCore::AnimatedSprite>(entity).animations;
            auto& sprite = *view.get<CCore::AnimatedSprite>(entity).sprite;

            sf::Vector2f velocity{};

            if (game.input.isKeyPressed(sf::Keyboard::W))
                velocity.y -= movement_speed * game.dt.asSeconds();
            else if (game.input.isKeyPressed(sf::Keyboard::S))
                velocity.y += movement_speed * game.dt.asSeconds();
            if (game.input.isKeyPressed(sf::Keyboard::A))
                velocity.x -= movement_speed * game.dt.asSeconds();
            else if (game.input.isKeyPressed(sf::Keyboard::D))
                velocity.x += movement_speed * game.dt.asSeconds();
            
            if (velocity.x != 0.f && velocity.y != 0.f)
            {
                velocity.x /= mke::SQRT2;
                velocity.y /= mke::SQRT2;
            }

            if (velocity.x == 0.f && velocity.y == 0.f)
                animations["idle"]->run(game.dt);
            else
                animations["walk"]->run(game.dt);

            position += velocity;

            position.x = std::clamp(position.x, 0.f, Map::size_x);
            position.y = std::clamp(position.y, 0.f, Map::size_y);

            sprite.setPosition(position);
            if (velocity.x < 0.f)
                sprite.setScale(-fabsf(sprite.getScale().x), sprite.getScale().y);
            else if (velocity.x > 0.f)
                sprite.setScale(+fabsf(sprite.getScale().x), sprite.getScale().y);

            auto view = game.win.getView();
            view.setCenter(position);
            game.win.setView(view);
        }
    }
}