#pragma once
#include <danikk_engine/danikk_engine.h>
#include <danikk_engine/texture.h>

namespace danikk_engine
{
	struct Material
	{
		Texture diffuse_texture;
	};

	typedef uint16 gl_point_index_t;

	struct Vertex
	{
		vec3 pos;
		vec3 normal;
		vec2 uv;

		bool operator==(Vertex other)
		{
			return other.pos != pos && other.normal != normal && other.uv != uv;
		}

		Vertex() = default;

		Vertex(float posx, float posy, float posz,
				   float normalx, float normaly, float normalz,
				   float uvx, float uvz)
		{
			pos = vec3(posx, posy, posz);
			normal = vec3(normalx, normaly, normalz);
			uv = vec2(uvx, uvz);
		}

		Vertex(const Vertex& other) = default;
	};

	struct Mesh
	{
		uint32 element_buffer_object;
		uint32 vertex_buffer_object;
		uint32 vertex_array_object;
		uint32 indexes_count;

		Mesh();

		Mesh(Mesh&) = delete;

		Mesh(Mesh&&) = delete;

		~Mesh();

		Mesh& operator=(Mesh&) = delete;

		Mesh& operator=(Mesh&&) = default;

		void gl_init(const float* vertexes, size_t vertexes_count, const gl_point_index_t* indexes,  size_t indexes_count);

		Mesh(const float* vertexes, size_t vertexes_count, const gl_point_index_t* indexes,  size_t indexes_count);

		Mesh(const DynamicArray<float>& vertexes, const DynamicArray<gl_point_index_t>& indexes);

		Mesh(const DynamicArray<Vertex>& vertexes, const DynamicArray<gl_point_index_t>& indexes);

		/*void bind();

		void unbind();*/

		void draw();
	};

	extern Mesh sprite_mesh;
}
