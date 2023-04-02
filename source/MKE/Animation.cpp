#include "Animation.hpp"

namespace mke
{
	void Animation::setSprite(sf::Sprite& sprite)
	{
		this->sprite = &sprite;
		if (this->atlas != nullptr)
			this->sprite->setTexture(this->atlas->texture);
	}

	void Animation::setAtlas(mke::AssetManager::AtlasContent& atlas)
	{
		this->atlas = &atlas;
		if (this->sprite != nullptr)
			this->sprite->setTexture(atlas.texture);
	}

	void Animation::loadFromFile(const std::string& filename)
	{
		std::ifstream file{ filename };
		if (!file)
		{
			std::cerr << "Error: mke::Animation::loadFromFile(): could not find file with filename \"" 
				<< filename << "\"\n";
			exit(EXIT_FAILURE);
		}

		nlohmann::json json{};
		file >> json;
		for (const auto& i : json["frames"].items())
		{
			Frame frame{};
			frame.rect = atlas->frames[i.value()["name"]];
			frame.duration = sf::seconds(i.value()["duration"]);
			frames.push_back(frame);
		}
	}

	void Animation::loadFromJson(const nlohmann::json& json)
	{
		for (const auto& i : json["frames"].items())
		{
			Frame frame{};
			frame.rect = atlas->frames[i.value()["name"]];
			frame.duration = sf::seconds(i.value()["duration"]);
			frames.push_back(frame);
		}
	}

	void Animation::addFrame(const std::string& frame_name, sf::Time duration)
	{
		if (atlas == nullptr)
		{
			std::cerr << "Error: mke::Animation::addFrame(): atlas has to be set before adding frames";
			exit(EXIT_FAILURE);
		}

		Frame frame{};
		frame.rect = atlas->frames["frame_name"];
		frame.duration = duration;
		frames.push_back(frame);
	}

	void Animation::setSpriteFrame(const std::string& frame_name)
	{
		if (atlas->frames.count(frame_name) == 0)
		{
			std::cerr << "Error: mke::Animation::setSpriteFrame(): frame with name \"" << frame_name <<
				"\" does not exist";
			exit(EXIT_FAILURE);
		}
		sprite->setTextureRect(atlas->frames[frame_name]);
	}

	void Animation::setSpriteFrame(unsigned int index)
	{
		if (index >= frames.size())
		{
			std::cerr << "Error: mke::Animation::setSpriteFrame(index): index is greater or equal than" <<
				"the number of frames\n";
			exit(EXIT_FAILURE);
		}
		sprite->setTextureRect(frames[index].rect);
	}

	void Animation::reset()
	{
		frames_index = 0;
		clock = sf::Time::Zero;
	}

	void Animation::run(const sf::Time dt)
	{
		clock += dt;
		if (clock >= frames[frames_index].duration)
		{
			frames_index++;
			if (frames_index == frames.size())
			{
				frames_index = 0;
				loops++;
			}
			clock = sf::Time::Zero;
		}
		sprite->setTextureRect(frames[frames_index].rect);
	}

	unsigned int Animation::getLoopCount()
	{
		return loops;
	}
}