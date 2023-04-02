#pragma once

namespace mke
{

	/**
	 * @brief The default state class used by mke::StateMachine
	 * 
	 */
	class State
	{
	public:
		virtual ~State() = default;

		virtual void update() = 0;
		virtual void render() = 0;
	};
}