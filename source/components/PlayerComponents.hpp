#pragma once

#include <SFML/Graphics.hpp>

namespace CPlayer
{
    struct Base
    {
        int score;
    };

    struct Movement
    {
        sf::Vector2f position;
        float movement_speed;
    };
}