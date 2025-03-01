#pragma once

#include <danikk_engine/danikk_engine.h>
#include <danikk_engine/texture.h>
#include <danikk_engine/font.h>
#include <danikk_engine/style.h>

#include <danikk_framework/bit_array.h>
#include <functional>

namespace danikk_engine
{

	enum GUIElementFlags
	{
		visible,
		draggable,
		absolute_recalc
	};

	class GUIElement
	{
	public:
		DynamicArray<GUIElement*> childs;
		GUIElement* parent = NULL;

		danikk_framework::BitArray<4> flags = danikk_framework::BitArray<4>(0b101);
		int32 anchor;

		vec2 pos = vec2(0.0f, 0.0f);
		vec2 absolute_pos;

		vec2 relative_size = vec2(0);
		vec2 pixel_size = vec2(0);
		vec2 absolute_size;

		GUIElement();

		GUIElement& operator=(const GUIElement&) = delete;

		GUIElement& operator=(const GUIElement&&) = delete;

		void recursiveDraw();

		void handleClick(int32 is_pushed);

		void addChild(GUIElement& child);

		virtual void draw(vec2 offset, vec2 scale) = 0;

		virtual ~GUIElement() = default;
	};

	class Panel : public GUIElement
	{
	public:
		Sprite sprite;
		DrawStyle* draw_style = &default_draw_styles::panel_draw;
		BorderDrawStyle* border_draw_style = &default_draw_styles::panel_border;

		Panel() = default;

		GUIElement& operator=(const GUIElement&) = delete;

		GUIElement& operator=(const GUIElement&&) = delete;

		~Panel() = default;

		void draw(vec2 offset, vec2 scale);
	};

	class Label : public GUIElement
	{
	public:
		String text;
		TextStyle* text_style = NULL;

		Label() = default;

		GUIElement& operator=(const GUIElement&) = delete;

		GUIElement& operator=(const GUIElement&&) = delete;

		~Label() = default;

		void draw(vec2 offset, vec2 scale);
	};

	class Button : public Panel
	{
	public:
		String text;
		TextStyle* text_style = &default_draw_styles::button_text;
		std::function<void()> on_click;
		int draw_panel = true;

		Button();

		void draw(vec2 offset, vec2 scale);

		Button& operator=(const Button&) = delete;

		Button& operator=(const Button&&) = delete;
	};

	class ButtonArray//Не реализовано.
	{
	public:
		bool is_horizontal = false;
	};

	/*enum gui_compose_type
	{
		vertical,
		horizontal
	};

	enum direction
	{
		down,
		up
	};*/

	//void composeGUI(int compose_type, GUIElement& target, vec2 offset, float default_height);

	extern Panel gui_root;
}
