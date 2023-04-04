#pragma once

#include <SFML/Graphics.hpp>

namespace CGhost
{
    struct Base
    {

    };

    struct Movement
    {
        sf::Time min_wait_time;
        sf::Time max_wait_time;

        sf::Time clock;
        sf::Time delay;

        enum State
        {
            Moving,
            Waiting
        } state = State::Moving;

        sf::Vector2f target;
        sf::Vector2f velocity;

        float move_radius;
        float speed;
    };

    struct Tag
    {
        int k;
        sf::Text text;
    };
}