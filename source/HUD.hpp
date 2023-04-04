#pragma once

#include "Fibonacci.hpp"

#include "MKE/AssetManager.hpp"
#include "MKE/Utility.hpp"

#include <SFML/Graphics.hpp>

#include <string>

class HUD
{
public:
    HUD(sf::RenderWindow& win, mke::AssetManager& assets, Fibonacci& fibonacci);

    void setScore(int score);
    void render();
private:
    sf::RenderWindow& win;
    mke::AssetManager& assets;
    Fibonacci& fibonacci;

    sf::Text sequence;
};