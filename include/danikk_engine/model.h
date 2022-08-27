#pragma once

#include <danikk_framework/memory_stream.h>

#include <danikk_engine/danikk_engine.h>
#include <danikk_engine/texture.h>

namespace danikk_engine
{
	namespace internal
	{
		struct Material
		{
			Texture diffuse_texture;
		};

		struct Mesh
		{
			uint32 elementBufferObject;
			uint32 vertexBufferObject;
			uint32 vertexArrayObject;
			uint32 indicesCount;
			Material& material;
		};
	}

	class Model
	{
		using Mesh = internal::Mesh;
		using Material = internal::Material;

		DynamicArray<Mesh> meshes;
		DynamicArray<Material> materials;
		uint32* ref_count_ptr;
	public:
		Model();

		Model(DynamicArray<Mesh>& meshes, DynamicArray<Material>& materials, uint32* ref_count_ptr);

		~Model();

		void draw();
	};
}
