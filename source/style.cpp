#include <danikk_engine/style.h>
#include <danikk_engine/internal/texture_methods.h>
#include <danikk_engine/matrix/pos.h>
#include <danikk_engine/matrix/uv.h>

namespace danikk_engine
{
	using namespace internal;

	namespace default_draw_styles
	{
		TextStyle label_text;
		TextStyle button_text;
		DrawStyle panel_draw;
		DrawStyle button_draw;
		BorderDrawStyle panel_border;
		BorderDrawStyle window_border;

		DrawStyle* all[]
		{
			&label_text,
			&button_text,
			&panel_draw,
			&button_draw,
			&panel_border,
			&window_border
		};
	}

	BorderDrawStyle::BorderDrawStyle()
	{
		this->color = vec4(0.0f,0.0f,0.0f,1.0f);
	}

	void BorderDrawStyle::draw(vec2 pos, vec2 size)
	{
		mat4 poses[]
		{
			create_pos_matrix(pos, 								vec2(size.x, width.y), 0),
			create_pos_matrix(pos + vec2(0, size.y - width.y), 	vec2(size.x, width.y), 0),
			create_pos_matrix(pos, 								vec2(width.x, size.y), 0),
			create_pos_matrix(pos + vec2(size.x - width.x, 0),	vec2(width.x, size.y), 0)
		};
		for(const mat4& pos : poses)
		{
			draw_texture(0, pos, fill_uv_matrix, color);
		}
	}

	void TextStyle::draw(const String& text, vec2 pos, vec2 size)
	{
		shader.use();
		font.draw(text, pos, size, *this);
	}

	void setDefaultGUIShader(Shader& shader)
	{
		for(DrawStyle* ptr : default_draw_styles::all)
		{
			ptr->shader = shader;
		}
	}

	void setDefaultFont(Font& font)
	{
		default_draw_styles::label_text.font = font;
		default_draw_styles::button_text.font = font;
	}

	void setDefaultCharSize(float height, float width)
	{
		default_draw_styles::label_text.absolute_char_height = height;
		default_draw_styles::label_text.absolute_char_width = width;
		default_draw_styles::button_text.absolute_char_height = height;
		default_draw_styles::button_text.absolute_char_width = width;
	}

	void setDefaultCharInterval(float value)
	{
		default_draw_styles::label_text.char_interval = default_draw_styles::label_text.absolute_char_width * value;
		default_draw_styles::button_text.char_interval = default_draw_styles::button_text.absolute_char_width * value;
	}
}
