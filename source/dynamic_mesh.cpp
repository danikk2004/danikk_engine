#include <danikk_engine/dynamic_mesh.h>
#include <danikk_framework/assert.h>
#include <glm/glm.hpp>

namespace danikk_engine
{
	/*void DynamicMesh::addTriangle(cref<MeshTriangle> triangle)
	{
		uint32 point_indexes_at_array[3 + 1];//последний элемент - текущий индекс в массиве индексов
		#define current_arr_index point_indexes_at_array[3]
		for(MeshVertex vertex : triangle.vertexes)
		{
			int64 index = vertexes.indexOf(vertex);
			if(index == -1)
			{
				vertexes.push(vertex);
				point_indexes_at_array[current_arr_index] = vertexes.size() - 1;
			}
			else
			{
				point_indexes_at_array[current_arr_index] = index;
				current_arr_index++;
			}
		}
		indexes.push(point_indexes_at_array[0]);
		indexes.push(point_indexes_at_array[1]);
		indexes.push(point_indexes_at_array[2]);
	}*/

	DynamicMesh::DynamicMesh(const InitList<Vertex>& vertexes, const InitList<gl_point_index_t>& indexes)
	{
		new (&this->vertexes) DynamicArray<Vertex>(vertexes);
		new (&this->indexes) DynamicArray<gl_point_index_t>(indexes);
	}

	Mesh DynamicMesh::operator()()
	{
		return Mesh(vertexes, indexes);
	}

	DynamicMesh& DynamicMesh::operator=(const DynamicMesh& other)
	{
		indexes = other.indexes;
		vertexes = other.vertexes;
		return *this;
	}

	void initDynamicMeshes()
	{
		InitList<Vertex> vertexes
		{
					   //Позиции     		//Нормаль			//Текстурные координаты
			Vertex(1.0f, 0.0f, 1.0f,	0.0f,  0.0f, 1.0f,	1.0f, 0.0f),	//Верхний правый
			Vertex(1.0f, 0.0f, -1.0f,	0.0f,  0.0f, 1.0f,	1.0f, 1.0f),	//Нижний правый
			Vertex(-1.0f, 0.0f, -1.0f,	0.0f,  0.0f, 1.0f,	0.0f, 1.0f),	//Нижний левый
			Vertex(-1.0f, 0.0f, 1.0f,	0.0f,  0.0f, 1.0f,	0.0f, 0.0f) 	//Верхний левый
		};
		InitList<gl_point_index_t> indexes
		{
			2, 3, 0,
			0, 1, 2,
		};
		dynamic_square = DynamicMesh(vertexes, indexes);

		mat4 trans(1.0f);
		//trans = rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
		//trans = scale(trans, glm::vec3(0.5, 0.5, 0.5));

		square = dynamic_square();
		cube = dynamic_cube();
	}

	DynamicMesh dynamic_square;
	DynamicMesh dynamic_cube;

	Mesh square;
	Mesh cube;

}
