
#include <glad/glad.h>

namespace danikk_engine
{
	namespace internal
	{
		constexpr size_t VERTEX_SIZE = 8 * sizeof(float);

		static inline void vertexAttribFloatPointer(uint index, int size, size_t offset)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (void*)offset);
		}

		static inline void setVertexAttributes()
		{
			vertexAttribFloatPointer(0, 3, 0);					//Позиция вершины.
			vertexAttribFloatPointer(1, 3, sizeof(float) * 3);	//Нормаль вершины.
			vertexAttribFloatPointer(2, 2, sizeof(float) * 6);	//UV координаты.
		}
	}
}
