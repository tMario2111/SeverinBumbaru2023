#include "Random.hpp"

namespace mke
{
	void Random::setCustomSeed(unsigned long int seed)
	{
		random_engine.seed(seed);
		this->seed = seed;
	}

	void Random::setUniqueSeed()
	{
		this->seed = r();
		random_engine.seed(this->seed);
	}

	unsigned long int Random::getSeed()
	{
		return this->seed;
	}
}