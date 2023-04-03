#pragma once

#include "../MKE/Animation.hpp"

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>
#include <unordered_map>

namespace CCore
{
    using AnimationMap = std::unordered_map<std::string, std::unique_ptr<mke::Animation>>;

    struct AnimatedSprite
    {
        AnimatedSprite() = default;
        std::unique_ptr<sf::Sprite> sprite;
        std::unique_ptr<AnimationMap> animations;
    };
}