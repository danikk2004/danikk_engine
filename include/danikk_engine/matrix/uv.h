#pragma once
#include <danikk_engine/danikk_engine.h>
#include <danikk_engine/texture_methods.h>

namespace danikk_engine
{
	uv_matrix create_uv_matrix(
		uint x, uint y,
		uint width, uint height,
		uint texture_width, uint texture_height);

	uv_matrix create_uv_matrix(float x, float y, float scale);

	uv_matrix create_uv_matrix(float x, float y, float scale_x, float scale_y);

	extern uv_matrix fill_uv_matrix;

	namespace internal
	{
		void initUV();
	}

}
