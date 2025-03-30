#include <danikk_engine/danikk_engine.h>
#include <danikk_engine/mesh.h>
#include <danikk_engine/internal/vertex_attrib.h>
#include <danikk_engine/internal/glexec.h>
#include <danikk_engine/internal/gl_object_manager.h>

namespace danikk_engine
{
	using namespace internal;

	Mesh::Mesh()
	{
		element_buffer_object =
		vertex_buffer_object =
		vertex_array_object =
		indexes_count = 0;
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
