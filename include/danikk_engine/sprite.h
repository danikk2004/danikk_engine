#pragma once

#include<danikk_engine/danikk_engine.h>
#include<danikk_engine/internal/asset.h>

namespace danikk_engine
{
	class Sprite : private internal::Asset
	{
	private:
		friend class Texture;

		mat2 uv;
	public:
		Sprite() = default;

		Sprite(Sprite& other);

		Sprite(Sprite&& other);

		void operator=(Sprite& other);

		void operator=(Sprite&& other);

		~Sprite() = default;

		void draw(vec2 position, vec2 size, float rotation, vec4 color);

		void draw(mat4 world, vec4 color);
	};
}
