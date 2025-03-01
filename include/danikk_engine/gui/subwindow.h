#pragma once

#include <danikk_engine/gui.h>

namespace danikk_engine
{
	class SubWindow : public Panel
	{
	public:
		Panel header;
		Label title;
		Button close_button;

		Panel body;

		SubWindow();

		GUIElement& operator=(const GUIElement&) = delete;

		GUIElement& operator=(const GUIElement&&) = delete;

		~SubWindow() = default;
	};
}
