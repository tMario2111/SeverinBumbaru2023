#include "Utility.hpp"

namespace mke
{
	float getRotationToPoint(sf::Vector2f A, sf::Vector2f B)
	{
		return atan2f(B.y - A.y, B.x - A.x);
	}

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

	bool isOnScreen(const sf::Sprite& sprite, const sf::RenderWindow& win)
	{
		sf::FloatRect view_rect{};
		view_rect.left = win.getView().getCenter().x - win.getView().getSize().x / 2;
		view_rect.top = win.getView().getCenter().y - win.getView().getSize().y / 2;
		view_rect.width = win.getView().getSize().x;
		view_rect.height = win.getView().getSize().y;
		return sprite.getGlobalBounds().intersects(view_rect);
	}

	bool isOnScreen(const sf::Text& text, const sf::RenderWindow& win)
	{
		sf::FloatRect view_rect{};
		view_rect.left = win.getView().getCenter().x - win.getView().getSize().x / 2;
		view_rect.top = win.getView().getCenter().y - win.getView().getSize().y / 2;
		view_rect.width = win.getView().getSize().x;
		view_rect.height = win.getView().getSize().y;
		return text.getGlobalBounds().intersects(view_rect);
	}

	std::string addCommasToNumber(std::string number)
	{
		int n = number.length() - 3;
		while (n > 0) {
			number.insert(n, ",");
			n -= 3;
		}
		return number;
	}
}