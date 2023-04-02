#pragma once

#include "State.hpp"

#include <algorithm>
#include <iostream>
#include <memory>
#include <optional>
#include <type_traits>
#include <typeinfo>
#include <vector>

namespace mke
{

	/**
	 * @brief A state machine class
	 * 
	 * @tparam Base The state class (by default it's mke::State)
	 */
	template<typename Base = State> class StateMachine
	{
	public:

		/**
		 * @brief Push a new state to the stack
		 * 
		 * @tparam T State type
		 * @tparam Args 
		 * @param args State constructor arguments
		 */
		template<typename T, typename... Args, typename std::enable_if_t<std::is_base_of<Base, T>::value, bool> = true>
		void push(Args &&... args);

		/**
		 * @brief Remove the state at the top of the stack
		 * 
		 */
		void pop();

		/**
		 * @brief Pop states until a state of type 'T' is reached
		 * 
		 * @tparam T State type
		 */
		template<typename T, typename std::enable_if_t<std::is_base_of<Base, T>::value, bool> = true>
		void popStatesUntil();

		/**
		 * @brief Get a reference to the state at the top of the stack
		 * 
		 * @return Base& 
		 */
		Base& top();

		/**
		 * @brief Get the size of the stack
		 * 
		 * @return size_t 
		 */
		size_t size();

		/**
		 * @brief Get a reference to the first state of type 'T' that isn't at the top of the stack
		 * 
		 * @tparam T State type
		 * @return T& 
		 */
		template<typename T, std::enable_if_t<std::is_base_of<Base, T>::value, bool> = true>
		T& peekFirst();

		/**
		 * @brief Try getting a reference to the first state of type 'T' that isn't at the top of the stack
		 * 
		 * @tparam T State type
		 * @return std::optional<std::reference_wrapper<T>> Optional containing state
		 */
		template<typename T, std::enable_if_t<std::is_base_of<Base, T>::value, bool> = true>
		std::optional<std::reference_wrapper<T>> tryPeekFirst();

	private:
		std::vector<std::unique_ptr<Base>> states;
	};

	template<typename Base>
	template<typename T, typename... Args, typename std::enable_if_t<std::is_base_of<Base, T>::value, bool>>
	inline void StateMachine<Base>::push(Args && ...args)
	{
		states.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	}

	template<typename Base>
	template<typename T, typename std::enable_if_t<std::is_base_of<Base, T>::value, bool>>
	inline void StateMachine<Base>::popStatesUntil()
	{
		const auto it = std::find_if(states.begin(), states.end(), [](const auto& state)
		{
			return typeid(T) == typeid(*state.get());
		});
		if (it == std::end(states))
		{
			std::cerr << "Error: mke::StateMachine::popStatesUntil<T>: State \"" << typeid(T).name() 
				<< "\" not found in stack\n";
			exit(EXIT_FAILURE);
		}
		states.erase(it + 1, states.end());
	}

	template<typename Base>
	template<typename T, std::enable_if_t<std::is_base_of<Base, T>::value, bool>>
	inline T& StateMachine<Base>::peekFirst()
	{
		const auto it = std::find_if(states.begin(), states.end(), [](const auto& state)
		{
			return typeid(T) == typeid(*state.get());
		});
		if (it == std::end(states))
		{
			std::cerr << "Error: mke::StateMachine::peekFirst<T>: State \"" << typeid(T).name() 
				<< "\" not found in stack\n";
			exit(EXIT_FAILURE);
		}
		return *dynamic_cast<T*>(states[std::distance(states.begin(), it)].get());
	}

	template<typename Base>
	template<typename T, std::enable_if_t<std::is_base_of<Base, T>::value, bool>>
	inline std::optional<std::reference_wrapper<T>> StateMachine<Base>::tryPeekFirst()
	{
		const auto it = std::find_if(states.begin(), states.end(), [](const auto& state)
		{
			return typeid(T) == typeid(*state.get());
		});
		if (it == std::end(states))
			return {};
		return *dynamic_cast<T*>(states[std::distance(states.begin(), it)].get());
	}

	template<typename Base>
	inline void StateMachine<Base>::pop()
	{
		states.pop_back();
	}

	template<typename Base>
	inline Base& StateMachine<Base>::top()
	{
		if (states.empty())
		{
			std::cerr << "Error: mke::StateMachine::top(): stack is empty\n";
			exit(EXIT_FAILURE);
		}
		return *states.back().get();
	}

	template<typename Base>
	inline size_t StateMachine<Base>::size()
	{
		return states.size();
	}
}