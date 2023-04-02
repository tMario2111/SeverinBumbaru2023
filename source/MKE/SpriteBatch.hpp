#pragma once

#include <SFML/Graphics.hpp>

#include <array>

namespace mke
{
	class SpriteBatch : public sf::Drawable
	{
	public:
		
		SpriteBatch();

		/**
		 * @brief 
		 * 
		 * @param target 
		 * @param states The texture must be passed through render states
		 */
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		/**
		 * @brief Append a sprite to the batch
		 * 
		 * @param sprite 
		 */
		void append(const sf::Sprite& sprite);

		/**
		 * @brief Clear the batch
		 * 
		 */
		void clear();

	private:
		sf::VertexArray batch;
	};
}