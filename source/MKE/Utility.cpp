#include "Utility.hpp"

namespace mke
{
	void centerTextX(sf::Text& text, float x1, float x2)
	{
		sf::Vector2f position{};
		position.x = (x1 + x2) / 2.f - (text.getGlobalBounds().width / 2.f - text.getOrigin().x * text.getScale().x) -
			text.getLocalBounds().left * text.getScale().x;
		position.y = text.getPosition().y;
		text.setPosition(position);
	}

	void centerTextY(sf::Text& text, float y1, float y2)
	{
		sf::Vector2f position{};
		position.x = text.getPosition().x;
		position.y = (y1 + y2) / 2.f - (text.getGlobalBounds().height / 2.f - text.getOrigin().y * text.getScale().y) -
			text.getLocalBounds().top * text.getScale().y;
		text.setPosition(position);
	}

	void centerTextXY(sf::Text& text, float x1, float x2, float y1, float y2)
	{
		centerTextX(text, x1, x2);
		centerTextY(text, y1, y2);
	}
}