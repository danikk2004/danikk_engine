#include <danikk_engine/dynamic_mesh.h>
#include <danikk_framework/assert.h>
#include <glm/glm.hpp>

namespace danikk_engine
{
	Mesh cube_mesh;

	uvec2 square_tex_coords[4]
	{
		uvec2(1, 0),
		uvec2(1, 1),
		uvec2(0, 1),
		uvec2(0, 0),
	};

	//в массиве из 4 элементов должны быть следующие индексы:
	//2, 3, 0
	//0, 1, 2
	gl_point_index_t square_end_indices[6]
	{
		2, 3, 0,
		0, 1, 2
	};



	DynamicMesh::DynamicMesh(const InitList<Vertex>& vertexes, const InitList<gl_point_index_t>& indexes)
	{
		new (&this->vertexes) DynamicArray<Vertex>(vertexes);
		new (&this->indexes) DynamicArray<gl_point_index_t>(indexes);
	}

	Mesh DynamicMesh::toMesh()
	{
		return Mesh(vertexes, indexes);
	}

	DynamicMesh& DynamicMesh::operator=(const DynamicMesh& other)
	{
		indexes = other.indexes;
		vertexes = other.vertexes;
		return *this;
	}

	void DynamicMesh::addSquare(vec3* poses, vec3 normal)
	{
		gl_point_index_t first_index = vertexes.size();
		for(index_t i = 0; i < 4; i++)
		{
			Vertex vertex;
			vertex.pos = poses[i];
			vertex.normal = normal;
			vertex.uv = square_tex_coords[i];
			vertexes.push(vertex);
		}

		for(gl_point_index_t i : square_end_indices)
		{
			indexes.push(first_index + i);
		}
	}

	void initBuiltInMeshes()
	{
		DynamicMesh dynamic_cube = DynamicMesh();
		vec3 cube_yp[4]
		{
			vec3(0, 1, 0),
			vec3(1, 1, 0),
			vec3(1, 1, 1),
			vec3(0, 1, 1),
		};
		vec3 cube_ym[4]
		{
			vec3(0, 0, 0),
			vec3(1, 0, 0),
			vec3(1, 0, 1),
			vec3(0, 0, 1),
		};
		vec3 cube_zm[4]
		{
			vec3(0, 0, 0),
			vec3(1, 0, 0),
			vec3(1, 1, 0),
			vec3(0, 1, 0),
		};
		vec3 cube_zp[4]
		{
			vec3(0, 0, 1),
			vec3(1, 0, 1),
			vec3(1, 1, 1),
			vec3(0, 1, 1),
		};
		dynamic_cube.addSquare(cube_yp, vec3(0, 1, 0));
		dynamic_cube.addSquare(cube_ym, vec3(0, -1, 0));
		dynamic_cube.addSquare(cube_zm, vec3(0, 0, 1));
		dynamic_cube.addSquare(cube_zp, vec3(0, 0, -1));


		cube_mesh = dynamic_cube.toMesh();
	}
}
