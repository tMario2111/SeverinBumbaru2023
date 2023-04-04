#pragma once

#include <SFML/Graphics.hpp>

#include <math.h>
#include <string>

namespace mke
{
	constexpr auto PI = 3.14159f;
	constexpr auto SQRT2 = 1.41421f;
	constexpr auto SQRT3 = 1.73205f;

	/**
	 * @brief Convert radians into degreess
	 * 
	 * @param rad 
	 * @return float 
	 */
	inline float toDeg(float rad) 
	{
		return rad * 180.f / PI; 
	}

	/**
	 * @brief Convert degrees into radians
	 * 
	 * @param deg 
	 * @return float 
	 */
	inline float toRad(float deg) 
	{
		return deg * PI / 180.f; 
	}
	
	/**
	 * @brief Get the square of a float
	 * 
	 * @param n 
	 * @return float 
	 */
	inline float pow2(float n)
	{
		return n * n;
	}

	/**
	 * @brief Get the distance between 2 points
	 * 
	 * @param a First point
	 * @param b Second point
	 * @return
	 */
	inline float distance(sf::Vector2f a, sf::Vector2f b) 
	{
		return sqrtf(pow2(b.x - a.x) + pow2(b.y - a.y));
	}

	/**
	 * @brief Get the squared distance between 2 points (much faster that mke::distance)
	 * 
	 * @param a 
	 * @param b 
	 * @return float 
	 */
	inline float squaredDistance(sf::Vector2f a, sf::Vector2f b)
	{
		return pow2(b.x - a.x) + pow2(b.y - a.y);
	}

	/**
	 * @brief Get the rotation / angle to a point
	 * 
	 * @param a First point
	 * @param b Second point
	 * @return float radians
	 */
	float getRotationToPoint(sf::Vector2f a, sf::Vector2f b);

	/**
	 * @brief Center an sf::Text with any origin on the x axis
	 * 
	 * @param text 
	 * @param x1 
	 * @param x2 
	 */
	void centerTextX(sf::Text& text, float x1, float x2);

	/**
	 * @brief Center an sf::Text with any origin on the y axis
	 * 
	 * @param text 
	 * @param y1 
	 * @param y2 
	 */
	void centerTextY(sf::Text& text, float y1, float y2);

	/**
	 * @brief Center an sf::Text with any origin on the x and y axis
	 * 
	 * @param text 
	 * @param x1 
	 * @param x2 
	 * @param y1 
	 * @param y2 
	 */
	void centerTextXY(sf::Text& text, float x1, float x2, float y1, float y2);

	bool isOnScreen(const sf::Sprite& sprite, const sf::RenderWindow& win);

	bool isOnScreen(const sf::Text& text, const sf::RenderWindow& win);

	std::string addCommasToNumber(std::string number);
}