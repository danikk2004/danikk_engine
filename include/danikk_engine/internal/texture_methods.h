#pragma once

#include <danikk_engine/danikk_engine.h>
#include <danikk_engine/internal/asset.h>

namespace danikk_engine
{
	enum texture_filters
	{
		nearest,
		linear
	};

	typedef mat2 uv_matrix;

	extern Texture white_texture;

	namespace internal
	{
		void initTextureRenderer();

	    void setupDefaultTextureParameters(int filter = texture_filters::nearest);

	    void set_world_matrix(const mat4& world);

	    void set_uv_matrix(const uv_matrix& uv);

	    void set_draw_color(const vec4& color);

		void draw_texture(uint texture, const mat4& pos, const uv_matrix& uv, const vec4& color);


		//mat4 create_world_matrix(vec2 position, vec2 size);

		//mat4 create_world_matrix(vec2 position, float size);

		//mat4 create_world_matrix(vec2 position, vec2 size, float rotation);
	}
}
