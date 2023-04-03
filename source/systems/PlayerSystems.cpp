#include "PlayerSystems.hpp"

namespace SPlayer
{
    void create(Game& game, GameState& game_state)
    {
        auto& registry = game_state.registry;

        const auto entity = registry.create();

        registry.emplace<CPlayer::Base>(entity);
        
        auto& movement = registry.emplace<CPlayer::Movement>(entity);
        movement.movement_speed = 500.f;
    }

    void update(Game& game, GameState& game_state)
    {
        movement(game, game_state);
    }

    void movement(Game& game, GameState& game_state)
    {
        auto& registry = game_state.registry;

        auto view = registry.view<CPlayer::Base, CPlayer::Movement>();
        for (const auto entity : view)
        {
            auto& movement = view.get<CPlayer::Movement>(entity);
            const auto movement_speed = movement.movement_speed;
            auto& position = movement.position;

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

            position += velocity;

            auto view = game.win.getView();
            view.setCenter(position);
            game.win.setView(view);
        }
    }
}