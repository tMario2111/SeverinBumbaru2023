#pragma once

#include <SFML/Audio.hpp>

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace mke
{
	class SoundManager
	{
	public:

		/**
		 * @brief Get the maximum number of sounds that can be played at the same time
		 * 
		 * @return unsigned int 
		 */
		static unsigned int getSoundsLimit();

		/**
		 * @brief Load a sound buffer
		 * 
		 * @param name 
		 * @param filename 
		 */
		void loadSoundBuffer(const std::string& name, const std::string& filename);

		/**
		 * @brief Unload a sound buffer
		 * 
		 * @param name 
		 */
		void unloadSoundBuffer(const std::string& name);

		/**
		 * @brief Play a sound
		 * 
		 * @param name 
		 */
		void playSound(const std::string& name);

		/**
		 * @brief Play a sound
		 * 
		 * @param name 
		 * @param settings Function for sound settings
		 */
		void playSound(const std::string& name, std::function<void(sf::Sound&)> settings);

		/**
		 * @brief Must be called at the start of the main loop so that sounds can be disposed of
		 * 
		 */
		void update();

		/**
		 * @brief Bind a music file to a name
		 * 
		 * @param name 
		 * @param filename 
		 */
		void setMusicFilename(const std::string& name, const std::string& filename);

		/**
		 * @brief Get a music filename
		 * 
		 * @param name 
		 * @return std::string 
		 */
		std::string getMusicFilename(const std::string& name);

		/**
		 * @brief Get a reference to the music
		 * 
		 * @return sf::Music& 
		 */
		sf::Music& getMusic();

		/**
		 * @brief Get the music and play the specified file
		 * 
		 * @param name 
		 * @return sf::Music& 
		 */
		sf::Music& getMusicAs(const std::string& name);

	private:
		static constexpr auto sounds_limit = 255u;
		std::unordered_map<std::string, sf::SoundBuffer> sound_buffers;
		std::vector<std::unique_ptr<sf::Sound>> sounds;
		std::unordered_map<std::string, std::string> music_filenames;
		sf::Music music;
	};
}