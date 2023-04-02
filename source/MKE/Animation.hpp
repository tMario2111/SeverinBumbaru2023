#pragma once

#include "AssetManager.hpp"

#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace mke
{
	/**
	 * @brief A class that manages sprite animations
	 * 
	 */
	class Animation
	{
	public:

		/**
		 * @brief Construct a new Animation object
		 * 
		 */
		Animation() = default;

		/**
		 * @brief Set the Sprite object
		 * 
		 * @param sprite 
		 */
		void setSprite(sf::Sprite& sprite);

		/**
		 * @brief Set the Atlas object
		 * 
		 * @param atlas 
		 */
		void setAtlas(mke::AssetManager::AtlasContent& atlas);

		/**
		 * @brief Load an animation from a json file
		 * 
		 * @param filename 
		 */
		void loadFromFile(const std::string& filename);

		/**
		 * @brief Load an animation from a json object
		 * 
		 * @param json 
		 */
		void loadFromJson(const nlohmann::json& json);

		/**
		 * @brief Add a new frame
		 * 
		 * @param frame_name (the one defined in the json)
		 * @param duration 
		 */
		void addFrame(const std::string& frame_name, sf::Time duration);

		/**
		 * @brief Set the sprite frame manually (useful if animation is not running)
		 * 
		 * @param frame_name 
		 */
		void setSpriteFrame(const std::string& frame_name);

		/**
		 * @brief Set the sprite frame manually (useful if animation is not running)
		 * 
		 * @param index 
		 */
		void setSpriteFrame(unsigned int index);

		/**
		 * @brief Reset the animation
		 * 
		 */
		void reset();

		/**
		 * @brief Run the animation
		 * 
		 * @param dt 
		 */
		void run(const sf::Time dt);

		/**
		 * @brief Get the number of loops that the animation went through
		 * 
		 * @return unsigned int 
		 */
		unsigned int getLoopCount();

	private:
		sf::Sprite* sprite = nullptr;
		mke::AssetManager::AtlasContent* atlas = nullptr;
		sf::Time clock = sf::Time::Zero;
		struct Frame
		{
			sf::IntRect rect;
			sf::Time duration;
		};
		std::vector<Frame> frames;
		unsigned int frames_index = 0;
		unsigned int loops = 0;
	};
}