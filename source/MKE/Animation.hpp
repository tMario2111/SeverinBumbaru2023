#pragma once

#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

#include "AssetManager.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace mke
{
	class Animation
	{
	public:
		Animation(sf::Sprite& sprite);
		void setAtlas(mke::AssetManager::AtlasContent& atlas);
		void loadFromFile(const std::string& filename);
		void loadFromJson(const nlohmann::json& json);
		void addFrame(const std::string& frame_name, sf::Time duration);
		void setSpriteFrame(const std::string& frame_name);
		void setSpriteFrame(unsigned int index);
		void reset();
		void run(const sf::Time dt);
		unsigned int getLoopCount();
		void setReversed(bool reversed);
        
	private:
		sf::Sprite& sprite;
		mke::AssetManager::AtlasContent* atlas = nullptr;
		sf::Time clock = sf::seconds(0.f);
		bool reversed = false;
		struct Frame
		{
			std::string name;
			sf::Time duration;
		};
		std::vector<Frame> frames;
		int frames_index = 0;
		unsigned int loops = 0;
	};
}