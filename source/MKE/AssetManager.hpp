#pragma once

#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace mke
{
	/**
	 * @brief A class that manages assets
	 * 
	 */
	class AssetManager
	{
	public:

		/**
		 * @brief Load a texture from a file
		 * 
		 * @param name 
		 * @param filename 
		 */
		void loadTexture(const std::string& name, const std::string& filename);

		/**
		 * @brief Insert a texture
		 * 
		 * @param name 
		 * @param texture 
		 */
		void loadTexture(const std::string& name, const sf::Texture& texture);

		/**
		 * @brief Get a reference to a texture
		 * 
		 * @param name 
		 * @return sf::Texture& 
		 */
		sf::Texture& getTexture(const std::string& name);

		/**
		 * @brief Unload a texture
		 * 
		 * @param name 
		 */
		void unloadTexture(const std::string& name);

		/**
		 * @brief A struct that stores the atlas texture and its frames
		 * 
		 */
		struct AtlasContent
		{
			sf::Texture texture;
			std::unordered_map<std::string, sf::IntRect> frames;
		};

		/**
		 * @brief Load an atlas from a file
		 * 
		 * @param name 
		 * @param filename The image file and the json file must have the same path and name (excepting extensions)
		 */
		void loadAtlas(const std::string& name, const std::string& filename);

		/**
		 * @brief Get a reference to the contents of an atlas
		 * 
		 * @param name 
		 * @return AtlasContent& 
		 */
		AtlasContent& getAtlas(const std::string& name);

		/**
		 * @brief Get a frame of an atlas
		 * 
		 * @param atlas_name 
		 * @param frame_name Defined in the json file
		 * @return sf::IntRect 
		 */
		sf::IntRect getAtlasFrame(const std::string& atlas_name, const std::string& frame_name);

		/**
		 * @brief Get the texture of an atlas
		 * 
		 * @param name 
		 * @return sf::Texture& 
		 */
		sf::Texture& getAtlasTexture(const std::string& name);

		/**
		 * @brief Unload an atlas
		 * 
		 * @param name 
		 */
		void unloadAtlas(const std::string& name);

		/**
		 * @brief Load a font
		 * 
		 * @param name 
		 * @param filename 
		 */
		void loadFont(const std::string& name, const std::string& filename);
		
		/**
		 * @brief Get a refence to a font
		 * 
		 * @param name 
		 * @return sf::Font& 
		 */
		sf::Font& getFont(const std::string& name);

		/**
		 * @brief Unload a font
		 * 
		 * @param name 
		 */
		void unloadFont(const std::string& name);

		/**
		 * @brief A manager for custom assets
		 * 
		 * @tparam T Asset type
		 */
		template<typename T> class CustomManager
		{
		public:

			/**
			 * @brief Load a new assets
			 * 
			 * @tparam Args Asset constructor arguments
			 * @param name 
			 * @param args 
			 * @return T& A reference to the assets
			 */
			template<typename... Args>
			T& loadNew(const std::string& name, Args &&... args);

			/**
			 * @brief Get a reference to an asset
			 * 
			 * @param name 
			 * @return T& 
			 */
			T& get(const std::string& name);

			/**
			 * @brief Unload an asset
			 * 
			 * @param name 
			 */
			void unload(const std::string& name);

		private:
			std::unordered_map<std::string, std::unique_ptr<T>> map;
		};

	private:
		std::unordered_map<std::string, sf::Texture> textures;
		std::unordered_map<std::string, AtlasContent> atlases;
		std::unordered_map<std::string, sf::Font> fonts;
	
	};

	template<typename T>
	template<typename ...Args>
	inline T& AssetManager::CustomManager<T>::loadNew(const std::string& name, Args && ...args)
	{
		if (map.count(name) == 1)
		{
			std::cerr << "Error: mke::AssetManager::CustomManager::loadNew(): asset with name \"" << name << "\" "
				<< "already exists";
			std::exit(EXIT_FAILURE);
		}
		map[name] = std::make_unique<T>(std::forward<Args>(args)...);
		return *map[name].get();
	}

	template<typename T>
	inline T& AssetManager::CustomManager<T>::get(const std::string& name)
	{
		return *map[name].get();
	}

	template<typename T>
	inline void AssetManager::CustomManager<T>::unload(const std::string& name)
	{
		map.erase(name);
	}
}