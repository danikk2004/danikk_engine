#include <danikk_engine/danikk_engine.h>
#include <danikk_engine/mesh.h>
#include <danikk_engine/internal/data_manager.h>
#include <danikk_engine/internal/vertex_attrib.h>
#include <danikk_engine/internal/glexec.h>
#include <danikk_engine/internal/gl_object_manager.h>

#include <danikk_framework/misc/line_getter.h>
#include <danikk_framework/cstring_functions.h>
#include <danikk_framework/glm.h>

namespace danikk_engine
{
	using namespace internal;
	using namespace danikk_framework;

	Mesh::Mesh()
	{
		element_buffer_object =
		vertex_buffer_object =
		vertex_array_object =
		indexes_count = 0;
	}

	Mesh::Mesh(const char* model_name, const char* name)
	{
		bool can_load;
		if(model_name == NULL)
		{
			can_load = loadDataToBuffer("meshes", name, "obj", true);
		}
		else
		{
			can_load = loadDataToBuffer("models", model_name, name, "obj", true);
		}

		DynamicArray<vec3> vertex_pos;
		DynamicArray<vec2> vertex_uv;
		DynamicArray<vec3> vertex_normal;
		DynamicArray<Vertex> vertexes;
		DynamicArray<gl_point_index_t> indexes;

		uint32 index_counter = 0;

		if(can_load)
		{
			char* current_obj_ptr = asset_load_buffer.c_string();
			Array<char*, 16> splitted;
			Array<char, 8> splitters
			{
				' ',
				'/'
			};
			while (*current_obj_ptr != '\0')
			{
				char* line = getLine(current_obj_ptr);
				splitted.clear();
				strsplit(line, splitted, splitters);
				//SplitToFirstSelectedChar(OBJReader.ReadLine(), ' ', out string DataType, out string Value);
				char* obj_key = splitted[0];
				if(strequal(obj_key, "v"))
				{
					vertex_pos.push(parseVec3(splitted.data() + 1));

				}
				else if(strequal(obj_key, "vt"))
				{
					vertex_uv.push(parseVec2(splitted.data() + 1));

				}
				else if(strequal(obj_key, "vn"))
				{
					vertex_normal.push(parseVec3(splitted.data() + 1));

				}
				else if(strequal(obj_key, "vf"))
				{
					char** current_data = splitted.data() + 1;
					for(index_t i = 0; i < 3; i++)
					{
						uvec3 index_vec = parseUvec3(current_data + i * 3);
						vertexes.pushCtor(
								vertex_pos[index_vec[0]],
								vertex_normal[index_vec[1]],
								vertex_normal[index_vec[2]]);
						indexes.push(index_counter++);

					}
				}
			}
			glexec
			(
				generateBuffers();
				setData((float*)vertexes.data(),  vertexes.size() * 8, indexes.data(), indexes.size());
			);
		}
	}

	void Mesh::generateBuffers()
	{
    	vertex_buffer_object = glGenBuffer();
    	vertex_array_object = glGenVertexArray();
		element_buffer_object = glGenBuffer();
	}

	void Mesh::setData(const float* vertexes, size_t vertexes_count, const gl_point_index_t* indexes,  size_t indexes_count)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
		glBufferData(GL_ARRAY_BUFFER, vertexes_count * sizeof(float), vertexes, GL_STATIC_DRAW);

		glBindVertexArray(vertex_array_object);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes_count * sizeof(uint), indexes, GL_STATIC_DRAW);

		setVertexAttributes();
	}

	Mesh::Mesh(const float* vertexes, size_t vertexes_count, const gl_point_index_t* indexes,  size_t indexes_count)
	{
		this->indexes_count = indexes_count;

        glexec
		(
			generateBuffers();
			setData(vertexes, vertexes_count, indexes, indexes_count);
        )
	}

	Mesh::Mesh(const DynamicArray<float>& vertexes, const DynamicArray<gl_point_index_t>& indexes) :
		Mesh(vertexes.data() ,vertexes.size(),
			 indexes.data(), indexes.size()){}

	Mesh::Mesh(const DynamicArray<Vertex>& vertexes, const DynamicArray<gl_point_index_t>& indexes) :
		Mesh((float*)vertexes.data() , vertexes.size() * 8,
			  indexes.data(), indexes.size()){}

	void Mesh::clear()
	{
		if(element_buffer_object != 0)
		{
			glDeleteBuffer(element_buffer_object);
		}
		if(vertex_buffer_object != 0)
		{
			glDeleteBuffer(vertex_buffer_object);
		}
	}

	bool Mesh::isNull()
	{
		return !(vertex_buffer_object && element_buffer_object);
	}

	/*void Mesh::bind()
	{
		glBindVertexArray(vertex_array_object);
	}

	void Mesh::unbind()
	{
		glBindVertexArray(0);
	}*/

	void Mesh::draw()
	{
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
		glBindVertexArray(vertex_array_object);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
		glDrawElements(GL_TRIANGLES, indexes_count, GL_UNSIGNED_SHORT, (void*)(0));
	}
}
