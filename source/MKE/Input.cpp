#include "Input.hpp"

namespace mke
{
	void Input::processEvent(const sf::Event& event)
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			keyboard_input[event.key.code] = KeyState::Pressed;
			break;
		case sf::Event::KeyReleased:
			keyboard_input[event.key.code] = KeyState::Released;
			break;
		case sf::Event::MouseButtonPressed:
			mouse_input[event.mouseButton.button] = KeyState::Pressed;
			break;
		case sf::Event::MouseButtonReleased:
			mouse_input[event.mouseButton.button] = KeyState::Released;
			break;
		default:
			break;
		}
	}

	void Input::update()
	{
		for (auto& i : keyboard_input)
			if (i.second == KeyState::Released)
				i.second = KeyState::None;
		for (auto& i : mouse_input)
			if (i.second == KeyState::Released)
				i.second = KeyState::None;
	}

	bool Input::isKeyPressed(sf::Keyboard::Key key)
	{
		return keyboard_input[key] == KeyState::Pressed;
	}

	bool Input::isKeyReleased(sf::Keyboard::Key key)
	{
		return keyboard_input[key] == KeyState::Released;
	}

	bool Input::isMouseButtonPressed(sf::Mouse::Button button)
	{
		return mouse_input[button] == KeyState::Pressed;
	}
    
	bool Input::isMouseButtonReleased(sf::Mouse::Button button)
	{
		return mouse_input[button] == KeyState::Released;
	}
}