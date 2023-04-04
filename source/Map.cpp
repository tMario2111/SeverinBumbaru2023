#include "Map.hpp"

Map::Map(mke::AssetManager& assets) : 
    assets{ assets },
    background{ sf::Quads, 4 },
    border{ sf::LineStrip, 5 }
{
    setupBackground();
    setupBorder();
}

void Map::setupBackground()
{
    background[0].position = sf::Vector2f{ -margin, -margin };
    background[1].position = sf::Vector2f{ size_x + margin, -margin };
    background[2].position = sf::Vector2f{ size_x + margin, size_y + margin };
    background[3].position = sf::Vector2f{ -margin, size_y + margin };
    for (auto i = 0u; i < background.getVertexCount(); i++)
        background[i].texCoords = background[i].position;
}

void Map::setupBorder()
{
    border[0].position = sf::Vector2f{ 0.f, 0.f };
    border[1].position = sf::Vector2f{ size_x, 0.f };
    border[2].position = sf::Vector2f{ size_x, size_y };
    border[3].position = sf::Vector2f{ 0.f, size_y };
    border[4].position = border[0].position;

    for (int i = 0; i < 5; i++)
        border[i].color = sf::Color::Black;
}

sf::Vector2f Map::getRandomPoint(mke::Random& random)
{
    sf::Vector2f pos{};
    pos.x = random.getReal<float>(0.f, size_x);
    pos.y = random.getReal<float>(0.f, size_y);
    return pos;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(background, &assets.getTexture("background"));
    target.draw(border);
}