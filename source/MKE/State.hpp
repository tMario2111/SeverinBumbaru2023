#pragma once

#include <TGUI/TGUI.hpp>

#include <memory.h>

namespace mke
{
	class State
	{
	public:
		virtual ~State() = default;

		std::unique_ptr<tgui::Gui> gui;

		virtual void update() = 0;
		virtual void render() = 0;
	};
}