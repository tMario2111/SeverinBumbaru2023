#pragma once

#include "MKE/AssetManager.hpp"

#include <SFML/Graphics.hpp>

class Map : public sf::Drawable
{
public:
    Map(mke::AssetManager& assets);

    constexpr static float map_size_x = 4000.f;
    constexpr static float map_size_y = 4000.f;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    mke::AssetManager& assets;

    sf::VertexArray background;

    void setupBackground();
};