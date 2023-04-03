#include "Animation.hpp"

namespace mke
{
	Animation::Animation(sf::Sprite& sprite) :
		sprite(sprite)
	{
	}
	void Animation::setAtlas(mke::AssetManager::AtlasContent& atlas)
	{
		this->atlas = &atlas;
		sprite.setTexture(atlas.texture);
	}
	void Animation::loadFromFile(const std::string& filename)
	{
		std::ifstream file(filename);
		if (!file)
		{
			std::cerr << "Error: mke::Animation::loadFromFile(): could not find file with filename \"" 
				<< filename << "\"\n";
			exit(-1);
		}
		nlohmann::json json;
		file >> json;
		for (auto& i : json["frames"].items())
		{
			Frame frame;
			frame.name = i.value()["name"];
			frame.duration = sf::seconds(i.value()["duration"]);
			frames.push_back(frame);
		}
	}
	void Animation::loadFromJson(const nlohmann::json& json)
	{
		for (auto& i : json["frames"].items())
		{
			Frame frame;
			frame.name = i.value()["name"];
			frame.duration = sf::seconds(i.value()["duration"]);
			frames.push_back(frame);
		}
	}
	void Animation::addFrame(const std::string& frame_name, sf::Time duration)
	{
		if (atlas == nullptr)
		{
			std::cerr << "Error: mke::Animation::addFrame(): atlas has to be set before adding frames";
			exit(-1);
		}
		Frame frame;
		frame.name = frame_name;
		frame.duration = duration;
		frames.push_back(frame);
	}
	void Animation::setSpriteFrame(const std::string& frame_name)
	{
		sprite.setTextureRect(atlas->frames[frame_name]);
	}
	void Animation::setSpriteFrame(unsigned int index)
	{
		if (index >= frames.size())
		{
			std::cerr << "Error: mke::Animation::setSpriteFrame(index): index is greater or equal than" <<
				"the number of frames\n";
			exit(-1);
		}
		sprite.setTextureRect(atlas->frames[frames[index].name]);
	}
	void Animation::reset()
	{
		frames_index = 0;
		clock = sf::seconds(0.f);
	}
	void Animation::run(const sf::Time dt)
	{
		clock += dt;
		if (clock > frames[frames_index].duration)
		{
			if (!reversed)
			{
				frames_index++;
				if (frames_index == frames.size())
				{
					frames_index = 0;
					loops++;
				}
			}
			else 
			{
				frames_index--;
				if (frames_index == -1)
				{
					frames_index = frames.size() - 1;
					loops++;
				}
			}
			clock = sf::seconds(0.f);
		}
		sprite.setTextureRect(atlas->frames[frames[frames_index].name]);
	}
	unsigned int Animation::getLoopCount()
	{
		return loops;
	}
	void Animation::setReversed(bool reversed)
	{
		this->reversed = reversed;
	}
}