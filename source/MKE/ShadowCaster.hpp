#pragma once

#include "Utility.hpp"

#include <SFML/Graphics.hpp>

#include <algorithm>
#include <iostream>
#include <math.h>
#include <string>
#include <utility>
#include <vector>

namespace mke
{
	/**
	 * @brief A shadow casting class
	 * 
	 */
	class ShadowCaster : public sf::Drawable
	{
	public:

		ShadowCaster(sf::RenderWindow& win);

		/**
		 * @brief The vector of edges that are used by the shadow caster. Modify this vector according to your edges
		 * 
		 */
		std::vector<std::pair<sf::Vector2f, sf::Vector2f>> edges;

		/**
		 * @brief Set the rays' radius
		 * 
		 * @param radius The maximum lenght of a ray
		 */
		void setRadius(float radius);

		/**
		 * @brief Get the radius
		 * 
		 * @return float 
		 */
		float getRadius();

		/**
		 * @brief Update the shadow caster (must be called every frame)
		 * 
		 * @param reference_point The point that the rays are casted from (the player position for example)
		 */
		void update(sf::Vector2f reference_point);

		/**
		 * @brief Draw function (inherited from sf::Drawable)
		 * 
		 * @param target 
		 * @param states 
		 */
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		sf::RenderWindow& win;
		struct Ray
		{
			float angle;
			sf::Vector2f position;
		};
		std::vector<Ray> rays;
		float radius;
		std::string shader_data;
		sf::Shader shader;
		sf::VertexArray vision_triangle_fan;
		sf::RenderTexture render_texture;
		bool getLineIntersection(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4, sf::Vector2f& p5);
		void calculateVisibility(sf::Vector2f reference_point);
		void createTriangleFan(sf::Vector2f reference_point);
		void drawToRenderTexture();
	};
}
