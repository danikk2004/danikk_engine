#include <glad/glad.h>

#include <danikk_engine/texture.h>
#include <danikk_engine/internal/gl_memory_manager.h>

namespace danikk_engine
{
	static uint SREBO;
	static uint SRVBO;
	static uint SRVAO;

	const float vertices[] = {
		 //Позиции     		//Нормаль			//Текстурные координаты
		 1.0f,  1.0f, 0.0f,	1.0f,   1.0f, 0.0f,	1.0f, 1.0f,	//Верхний правый
		 1.0f, -1.0f, 0.0f,	1.0f,  -1.0f, 0.0f,	1.0f, 0.0f,	//Нижний правый
		-1.0f, -1.0f, 0.0f,	-1.0f, -1.0f, 0.0f,	0.0f, 0.0f,	//Нижний левый
		-1.0f,  1.0f, 0.0f,	-1.0f,  1.0f, 0.0f,	0.0f, 1.0f 	//Верхний левый
	};

	const ushort indices[] =
	{
		2, 3, 0,
		0, 1, 2,
	};

	static constexpr size_t vertices_size = sizeof(float) * 4 * 8;
	static constexpr size_t indices_size = 6 * sizeof(uint);

	namespace internal
	{
		void initTextureRenderer()
		{
			SREBO = glGenBuffer();
			SRVBO = glGenBuffer();
			SRVAO = glGenVertexArray();
			glBindVertexArray(SRVAO);

			glBindBuffer(GL_ARRAY_BUFFER, SRVBO);
			glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SREBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);

			setVertexAttributes();
			glBindVertexArray(0);
		}
	}


	using namespace internal;

	size_t Texture::handle()
	{
		return container.texture_data.handle;
	}

    Texture::Texture(Texture& other)
    : Asset(other.container){}

    Texture::Texture(Texture&& other)
    : Asset(other.container){}

    Texture::Texture(AssetContainer& container)
    : Asset(container){}

    void Texture::operator=(Texture&& other)
    {
    	new (this) Texture(other);
    }

    void Texture::bind()
    {
    	glActiveTexture(GL_TEXTURE0);
    	glBindTexture(GL_TEXTURE_2D, handle());
    }

    void Texture::draw(mat4 model, mat4 uv, float rotation)
    {
		glad_glUniformMatrix4fv(0, 1, &model);
		glad_glUniformMatrix4fv(1, 1, &uv);
    }
}
