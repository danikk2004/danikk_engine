#pragma once

#include<danikk_engine/danikk_engine.h>

namespace danikk_engine
{
	class Sprite
	{
	private:
		friend class Texture;

		Texture* texture;
		mat4 uv;
	public:
		void draw(vec2 position, vec2 size, float rotation);
	};
}
