#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <danikk_engine/danikk_engine.h>
#include <danikk_engine/texture_methods.h>
#include <danikk_engine/internal/gl_object_manager.h>
#include <danikk_engine/internal/vertex_attrib.h>
#include <danikk_engine/shader.h>
#include <danikk_engine/mesh.h>
#include <danikk_engine/dynamic_mesh.h>

namespace danikk_engine
{
	Texture white_texture;
	Sprite white_sprite;

	static constexpr uint vertices_size = sizeof(float) * 4 * 8;
	static constexpr uint indices_size = 6 * sizeof(gl_point_index_t);

	Mesh sprite_mesh;

    void setupDefaultTextureParameters(int filter)
    {
    	if(filter == texture_filters::linear)
    	{
	    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    	}
    	else
    	{
	    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    	}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_REPEAT);
		//glGenerateMipmap(GL_TEXTURE_2D);
    }

    void setWorldMatrix(const mat4& world)
    {
		glUniformMatrix4fv(shader_layout_locations::world, 1, 0, (float*)&world);
    }

    void setUVMatrix(const uv_matrix& uv)
    {
		glUniformMatrix2fv(shader_layout_locations::uv, 1, 0, (float*)&uv);
    }

    void setProjectionMatrix(const mat4& projection)
    {
		glUniformMatrix4fv(shader_layout_locations::projection, 1, 0, (float*)&projection);
    }

    void setViewMatrix(const mat4& view)
    {
		glUniformMatrix4fv(shader_layout_locations::view, 1, 0, (float*)&view);
    }

    void setDrawColor(const vec4& color)
    {
		glUniform4fv(shader_layout_locations::color, 1, (float*)&color);
    }

    void bindTexture(uint handle, uint index)
    {
    	if(handle == 0)
    	{
    		handle = white_texture.container->texture_data.handle;
    	}
    	glActiveTexture(GL_TEXTURE0 + index);
    	glBindTexture(GL_TEXTURE_2D, handle);
    }

	void drawSpriteMesh()
	{
		sprite_mesh.draw();
	}
}
