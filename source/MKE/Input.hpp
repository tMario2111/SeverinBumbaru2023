#pragma once

#include <SFML/Graphics.hpp>

#include <unordered_map>

namespace mke
{

	/**
	 * @brief A class that manages user input
	 * 
	 */
	class Input
	{
	public:

		/**
		 * @brief Process keyboard and mouse events
		 * 
		 * @param event Currently polled event
		 */
		void processEvent(const sf::Event& event);

		/**
		 * @brief Update the input (must be called before the event loop)
		 * 
		 */
		void update();

		/**
		 * @brief Check if a keyboard key is pressed
		 * 
		 * @param key 
		 * @return true 
		 * @return false 
		 */
		bool isKeyPressed(sf::Keyboard::Key key);

		/**
		 * @brief Check if a keyboard key is released
		 * 
		 * @param key 
		 * @return true 
		 * @return false 
		 */
		bool isKeyReleased(sf::Keyboard::Key key);

		/**
		 * @brief Check if a mouse button is pressed
		 * 
		 * @param button 
		 * @return true 
		 * @return false 
		 */
		bool isMouseButtonPressed(sf::Mouse::Button button);

		/**
		 * @brief Check if a mouse button is released
		 * 
		 * @param button 
		 * @return true 
		 * @return false 
		 */
		bool isMouseButtonReleased(sf::Mouse::Button button);

	private:
		enum KeyState
		{
			None,
			Pressed,
			Released
		};
		std::unordered_map<sf::Keyboard::Key, KeyState> keyboard_input;
		std::unordered_map<sf::Mouse::Button, KeyState> mouse_input;
	};
}