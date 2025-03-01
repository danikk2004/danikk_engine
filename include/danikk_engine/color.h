#pragma once

#include <danikk_engine/danikk_engine.h>
#include <danikk_framework/log.h>

namespace danikk_engine
{
	struct font_color
	{
		uint8 r, g, b, a;

		font_color() = default;

		inline font_color(uint8 value)
		{
			r = g = b = 255;
			a = 255 - value;
		}

		void operator=(uint8 value)
		{
			*this = font_color(value);
		}
	};

	struct rgba
	{
		uint8 r, g, b, a;

		inline rgba(uint8 value)
		{
			r = g = b = 255;
			a = value;
		}

		void operator=(uint8 value)
		{
			*this = rgba(value);
		}
	};

	inline vec4 rgbToVec4(int r, int g, int b)
	{
		return vec4((float)r/255.0f,(float)g/255.0f,(float)b/255.0f, 1.0f);
	}
}
