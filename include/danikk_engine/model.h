#pragma once

#include <danikk_engine/danikk_engine.h>
#include <danikk_engine/mesh.h>
#include <danikk_engine/internal/asset.h>

namespace danikk_engine
{
	class Model : internal::Asset
	{
		DynamicArray<Mesh> meshes;
	public:
		Model();

		Model(const char* name, bool is_sinle_meshed_obj = false);

		~Model();

		void draw();
	};
}
