#include "SpriteBatch.hpp"

namespace mke
{
	SpriteBatch::SpriteBatch() :
		batch{ sf::PrimitiveType::Quads } {}

	void SpriteBatch::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(batch, states);
	}

	void SpriteBatch::append(const sf::Sprite& sprite)
	{
		const auto texture_rect = static_cast<sf::FloatRect>(sprite.getTextureRect());
		std::array<sf::Vertex, 4> verts{};

		verts[0].texCoords = { texture_rect.left, texture_rect.top };
		verts[1].texCoords = { texture_rect.left + texture_rect.width, texture_rect.top };
		verts[2].texCoords = { texture_rect.left + texture_rect.width, texture_rect.top + texture_rect.height };
		verts[3].texCoords = { texture_rect.left, texture_rect.top + texture_rect.height };

		verts[0].position = sprite.getTransform().transformPoint(0.f, 0.f);
		verts[1].position = sprite.getTransform().transformPoint(texture_rect.width, 0.f);
		verts[2].position = sprite.getTransform().transformPoint(texture_rect.width, texture_rect.height);
		verts[3].position = sprite.getTransform().transformPoint(0.f, texture_rect.height);

		for (auto& vert : verts)
		{
			vert.color = sprite.getColor();
			batch.append(vert);
		}
	}

	void SpriteBatch::clear()
	{
		batch.clear();
	}
}