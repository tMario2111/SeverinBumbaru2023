#pragma once

#include "../core/Game.hpp"

#include "../MKE/Animation.hpp"

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

class Game;

namespace SCore
{
    void loadAnimationsFromJson(Game& game, sf::Sprite& sprite, CCore::AnimationMap& animations, 
        const nlohmann::json& json);
}