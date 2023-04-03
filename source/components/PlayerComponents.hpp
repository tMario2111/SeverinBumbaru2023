#pragma once

#include <SFML/Graphics.hpp>

namespace CPlayer
{
    struct Base {};

    struct Movement
    {
        sf::Vector2f position;
        float movement_speed;
    };
}