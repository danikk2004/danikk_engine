#include <danikk_engine/dynamic_mesh.h>
#include <danikk_engine/built_in_meshes.h>
#include <danikk_engine/danikk_engine.h>
#include <danikk_framework/assert.h>
#include <danikk_framework/glm.h>

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

	void DynamicMesh::addSquare(const vec3& pos, const vec3& normal)
	{
		vec3 poses[4]
		{
			vec3(0.5f, 	0.0f, 0.5f),
			vec3(-0.5f, 0.0f, 0.5f),
			vec3(-0.5f, 0.0f, -0.5f),
			vec3(0.5f, 	0.0f, -0.5f),
		};
		for(vec3& square_pos : poses)
		{
			if(normal.y == 1)
			{
				square_pos = glm::rotateX(square_pos, (float)pi * 0.5f);
			}
			if(normal.y == -1)
			{

			}
			else
			{
				square_pos = glm::rotateX(square_pos, 0.5f * pi);
				float rotation = 0;
				if(normal.x == -1)
				{
					rotation = 0;
				}
				else if(normal.z == 1)
				{
					rotation = 0.5f;
				}
				else if(normal.x == 1)
				{
					rotation = 1.0f;
				}
				else if(normal.z == -1)
				{
					rotation = 1.5f;
				}
				rotation += 0.5f;
				rotation = rotation * pi;
				square_pos = glm::rotateY(square_pos, rotation);
			}
			square_pos += pos;
		}
		addSquare(poses, normal);
	}

	void DynamicMesh::addSquare(vec3* poses, const vec3& normal)
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
		DynamicMesh dynamic_sprite_mesh = DynamicMesh
		(
			{
				Vertex(0.5f,  0.5f, 0.0f,	0.0f,  0.0f, 1.0f,	1.0f, 0.0f),
				Vertex(0.5f, -0.5f, 0.0f,	0.0f,  0.0f, 1.0f,	1.0f, 1.0f),
				Vertex(-0.5f, -0.5f, 0.0f,	0.0f,  0.0f, 1.0f,	0.0f, 1.0f),
				Vertex(-0.5f,  0.5f, 0.0f,	0.0f,  0.0f, 1.0f,	0.0f, 0.0f),
			},
			{
				2, 3, 0,
				0, 1, 2,
			}
		);

		/*DynamicMesh dynamic_cube = DynamicMesh
		(
			{
				Vertex(1.0f, 1.0f, 1.0f,	0.0f, 0.0f, 0.0f, 	1.0f, 1.0f),
				Vertex(-1.0f, 1.0f, 1.0f, 	0.0f, 0.0f, 0.0f, 	0.0f, 1.0f),
				Vertex(-1.0f, 1.0f, -1.0f, 	0.0f, 0.0f, 0.0f, 	0.0f, 0.0f),
				Vertex(1.0f, 1.0f, -1.0f, 	0.0f, 0.0f, 0.0f, 	1.0f, 0.0f),

				Vertex(1.0f, -1.0f, 1.0f, 	0.0f, 0.0f, 0.0f, 	0.0f, 0.0f),
				Vertex(-1.0f, -1.0f, 1.0f, 	0.0f, 0.0f, 0.0f, 	0.0f, 0.0f),
				Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 	0.0f, 0.0f),
				Vertex(1.0f, -1.0f, -1.0f, 	0.0f, 0.0f, 0.0f, 	0.0f, 0.0f),
			},
			{
				0, 1, 3, //верх 1
				3, 1, 2, //верх 2
				2, 6, 7, //перед 1
				7, 3, 2, //перед 2
				7, 6, 5, //низ 1
				5, 4, 7, //низ 2
				5, 1, 4, //зад 1
				4, 1, 0, //зад 2
				4, 3, 7, //право 1
				3, 4, 0, //право 2
				5, 6, 2, //лево 1
				5, 1, 2  //лево 2
			}
		);*/
		DynamicMesh dynamic_cube;
		float start = -0.50f;
		float end = 1.0f;
		float step = 1.0f;
		for(float x = start; x <end; x += step)
		{
			dynamic_cube.addSquare(vec3(x, 0, 0), vec3(x * 2, 0, 0));
		}
		for(float y = start; y < end; y += step)
		{
			dynamic_cube.addSquare(vec3(0, y, 0), vec3(0, y * 2, 0));
		}
		for(float z = start; z < end; z += step)
		{
			dynamic_cube.addSquare(vec3(0, 0, z), vec3(0, 0, z * 2));
		}

		cube_mesh = dynamic_cube.toMesh();
		sprite_mesh = dynamic_sprite_mesh.toMesh();
	}
}
