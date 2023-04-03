#include "Map.hpp"

Map::Map(mke::AssetManager& assets) : 
    assets{ assets },
    background{ sf::Quads, 4 }
{
    setupBackground();
}

void Map::setupBackground()
{
    background[0].position = sf::Vector2f{ 0.f, 0.f };
    background[1].position = sf::Vector2f{ map_size_x, 0.f };
    background[2].position = sf::Vector2f{ map_size_x, map_size_y };
    background[3].position = sf::Vector2f{ 0.f, map_size_y };
    for (auto i = 0u; i < background.getVertexCount(); i++)
        background[i].texCoords = background[i].position;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(background, &assets.getTexture("background"));
}