#pragma once

#include <danikk_engine/danikk_engine.h>
#include <danikk_engine/internal/asset.h>
#include <danikk_engine/internal/texture_methods.h>
#include <danikk_engine/sprite.h>

namespace danikk_engine
{
	namespace internal
	{
		void initTextureRenderer();
	}

	class Texture : public internal::Asset
	{
	private:
		friend class Sprite;

		size_t handle();
	public:

		Texture() = default;

		Texture(Texture& other);

		Texture(Texture&& other);

		Texture(internal::AssetContainer* container);

		Texture(const String& name, int filter = texture_filters::nearest);

		void operator=(Texture& other);

		void operator=(Texture&& other);

		Sprite createSprite();

		Sprite createSprite(float x, float y, float width, float height);

		Sprite createSprite(uint x, uint y, uint width, uint height);

		void draw(const mat4& model, const mat4& uv, const vec4& color = vec4(1));
	};

	extern Texture white_texture;
}
