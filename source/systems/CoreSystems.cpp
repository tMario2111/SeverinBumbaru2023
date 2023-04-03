#include "CoreSystems.hpp"

namespace SCore
{
    void loadAnimationsFromJson(Game& game, sf::Sprite& sprite, CCore::AnimationMap& animations, 
        const nlohmann::json& json)
    {
        for (const auto& i : json.items())
        {
            animations[i.key()] = std::make_unique<mke::Animation>(sprite);
            animations[i.key()]->setAtlas(game.assets.getAtlas("atlas"));
            animations[i.key()]->loadFromJson(i.value());
        }
    }
}