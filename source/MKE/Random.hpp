#pragma once

#include <iostream>
#include <random>

namespace mke
{

	/**
	 * @brief A class that wraps <random> and uses std::default_random_engine
	 * 
	 */
	class Random
	{
	public:

		/**
		 * @brief Set a new custom seed
		 * 
		 * @param seed 
		 */
		void setCustomSeed(unsigned long int seed);

		/**
		 * @brief Sets a new unique seed (using std::random_device)
		 * 
		 */
		void setUniqueSeed();

		/**
		 * @brief Get the engine's seed
		 * 
		 * @return unsigned long int 
		 */
		unsigned long int getSeed();

		/**
		 * @brief Get a random integer
		 * 
		 * @tparam T Integer type
		 * @param min Minimum value
		 * @param max Maximum value (must be greater than the minimum)
		 * @return T 
		 */
		template<typename T> T getInt(T min, T max);

		/**
		 * @brief Get a random real number
		 * 
		 * @tparam T Real type
		 * @param min Minimum value
		 * @param max Maximum value (must be greater than the minimum)
		 * @return T 
		 */
		template<typename T> T getReal(T min, T max);

	private:
		std::random_device r;
		std::default_random_engine random_engine;
		unsigned long int seed;
	};

	template<typename T> inline T Random::getInt(T min, T max)
	{
		if (min >= max)
		{
			std::cerr << "Error: mke::Random::getInt(): max must be greater than min\n";
			exit(EXIT_FAILURE);
		}
		return std::uniform_int_distribution<T>(min, max)(random_engine);
	}

	template<typename T> inline T Random::getReal(T min, T max)
	{
		if (min >= max)
		{
			std::cerr << "Error: mke::Random::getReal(): max must be greater than min\n";
			exit(EXIT_FAILURE);
		}
		return std::uniform_real_distribution<T>(min, max)(random_engine);
	}
}