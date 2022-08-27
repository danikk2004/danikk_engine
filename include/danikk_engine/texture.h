#pragma once

#include <danikk_engine/danikk_engine.h>
#include <danikk_engine/internal/asset.h>
#include <danikk_engine/sprite.h>

namespace danikk_engine
{
	namespace internal
	{
		void initTextureRenderer();
	}

	class Texture : private internal::Asset
	{
	private:
		size_t handle();
	public:
		Texture() = default;

		Texture(Texture& other);

		Texture(Texture&& other);

		Texture(internal::AssetContainer& containerRef);

		static Sprite create_sprite(uint x, uint y, uint width, uint height);

		void draw(mat4 model, mat4 uv, float rotation);

		void operator=(Texture&& other);

		void bind();
	};
}
