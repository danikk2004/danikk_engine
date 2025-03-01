#pragma once

#include <danikk_engine/danikk_engine.h>
#include <danikk_engine/mesh.h>
#include <danikk_engine/internal/asset.h>

namespace danikk_engine
{
	class Model : internal::Asset
	{
		DynamicArray<Mesh> meshes;
		DynamicArray<Material> materials;
	public:
		Model();

		Model(const char* name);

		~Model();

		void draw();
	};
}
