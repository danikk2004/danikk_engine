#include <danikk_engine/internal/gl_memory_manager.h>
#include <danikk_engine/danikk_engine.h>
#include <danikk_framework/fixed_array.h>
#include <glad/glad.h>

using namespace danikk_framework;

namespace danikk_engine
{
    const size_t GL_MEMORY_BUFFER_SIZE = 64;

    static size_t glCurrentBufferIndex = 0;
    static uint32 glBuffers[GL_MEMORY_BUFFER_SIZE];
    static size_t glCurrentTextureIndex = 0;
    static uint32 glTextures[GL_MEMORY_BUFFER_SIZE];
    static size_t glCurrentVertexArrayIndex = 0;
    static uint32 glVertexArrays[GL_MEMORY_BUFFER_SIZE];

    uint32 glGenBuffer()
	{
		if (glCurrentBufferIndex == 0)
		{
			glCurrentBufferIndex = GL_MEMORY_BUFFER_SIZE - 1;
			glGenBuffers(GL_MEMORY_BUFFER_SIZE, glBuffers);
		}
		return glBuffers[glCurrentBufferIndex--];
	}

    void glDeleteBuffer(uint32 buffer)
    {
    	if(buffer == 0)
    	{
    		return;
    	}
        if (glCurrentBufferIndex == GL_MEMORY_BUFFER_SIZE)
        {
        	glCurrentBufferIndex = 0;
            glDeleteBuffers(GL_MEMORY_BUFFER_SIZE, glBuffers);
        }
        glBuffers[glCurrentBufferIndex++] = buffer;
    }

    uint32 glGenTexture()
	{
		if (glCurrentTextureIndex == 0)
		{
			glCurrentTextureIndex = GL_MEMORY_BUFFER_SIZE - 1;
			glGenTextures(GL_MEMORY_BUFFER_SIZE, glTextures);
		}
		return glTextures[glCurrentTextureIndex--];
	}

    void glDeletetexture(uint32 texture)
    {
    	if(texture == 0)
    	{
    		return;
    	}
        if (glCurrentTextureIndex == GL_MEMORY_BUFFER_SIZE)
        {
        	glCurrentTextureIndex = 0;
            glDeleteTextures(GL_MEMORY_BUFFER_SIZE, glTextures);
        }
        glTextures[glCurrentTextureIndex++] = texture;
    }

    uint32 glGenVertexArray()
	{
		if (glCurrentVertexArrayIndex == 0)
		{
			glCurrentVertexArrayIndex = GL_MEMORY_BUFFER_SIZE - 1;
			glGenVertexArrays(GL_MEMORY_BUFFER_SIZE, glVertexArrays);
		}
		return glVertexArrays[glCurrentVertexArrayIndex--];
	}

    void glDeleteVertexArray(uint32 vertexArray)
    {
    	if(vertexArray == 0)
    	{
    		return;
    	}
        if (glCurrentVertexArrayIndex == GL_MEMORY_BUFFER_SIZE)
        {
        	glCurrentVertexArrayIndex = 0;
            glDeleteVertexArrays(GL_MEMORY_BUFFER_SIZE, glVertexArrays);
        }
        glVertexArrays[glCurrentVertexArrayIndex++] = vertexArray;
    }
}
