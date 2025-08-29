#pragma once

#include <danikk_engine/danikk_engine.h>
#include <danikk_engine/mesh.h>
#include <danikk_framework/dynamic_array.h>

namespace danikk_engine
{
	struct MeshTriangle
	{
		Vertex vertexes[3];

		MeshTriangle(const Vertex* vertexes)
		{
			this->vertexes[0] = vertexes[0];
			this->vertexes[1] = vertexes[1];
			this->vertexes[2] = vertexes[2];
		}
	};

	struct MeshSquare
	{
		Vertex vertexes[4];
	};

	class DynamicMesh
	{
	private:
		DynamicArray<Vertex> vertexes;
		DynamicArray<gl_point_index_t> indexes;
	public:
		DynamicMesh() = default;

		DynamicMesh& operator=(const DynamicMesh& other);

		DynamicMesh(const InitList<Vertex>& vertexes, const InitList<gl_point_index_t>& indexes);

		void addSquare(const vec3& pos, const vec3& normal, const vec2& uv_offset = vec2(0.0f), const vec2 uv_size = vec2(1.0f));

		void addSquare(Vertex* vertexes);

		void addSquare(vec3* poses, const vec3& normal);

		void clear();

		Mesh toMesh();
	};

	void initBuiltInMeshes();
}
