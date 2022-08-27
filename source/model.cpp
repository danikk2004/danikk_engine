#include <glad/glad.h>

#include <danikk_framework/danikk_framework.h>
#include <danikk_framework/dynamic_array.h>
#include <danikk_engine/model.h>

#include <danikk_engine/internal/gl_memory_manager.h>
#include <danikk_engine/internal/vertex_attrib.h>

using danikk_framework::DynamicArray;

namespace danikk_engine
{
	using namespace internal;

    Model::Model(DynamicArray<Mesh>& meshes, DynamicArray<Material>& materials, uint32* ref_count_ptr)
    {
    	this->meshes = move(meshes);
    	this->materials = move(materials);
    	this->ref_count_ptr = ref_count_ptr;
    }

    Model::~Model()
    {
    	(*ref_count_ptr)--;

    	if(*ref_count_ptr == 0)
    	{
    		/*
    	glDeleteBuffer(elementBufferObject);
        glDeleteBuffer(vertexBufferObject);*/



/*
        indicesCount = indices.size();

        glexec
		(
			elementBufferObject = glGenBuffer();
			vertexBufferObject = glGenBuffer();
			vertexArrayObject = glGenVertexArray();
			glBindVertexArray(vertexArrayObject);

			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(uint), indices.data(), GL_STATIC_DRAW);

			vertexAttribFloatPointer(0, 3, 0);					//Позиция вершины.
			vertexAttribFloatPointer(1, 3, sizeof(float) * 3);	//Нормаль вершины.
			vertexAttribFloatPointer(2, 2, sizeof(float) * 6);	//UV координаты.
			glBindVertexArray(0);
        );
*/
    	}
    }

    void Model::draw()
    {
/*
        glBindVertexArray(vertexArrayObject);
        glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_SHORT, (void*)(0));
*/
    }
}
