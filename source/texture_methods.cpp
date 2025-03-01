#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <danikk_engine/danikk_engine.h>
#include <danikk_engine/internal/texture_methods.h>
#include <danikk_engine/internal/gl_object_manager.h>
#include <danikk_engine/internal/vertex_attrib.h>
#include <danikk_engine/shader.h>
#include <danikk_engine/mesh.h>
#include <danikk_engine/dynamic_mesh.h>

namespace danikk_engine
{
	Texture white_texture;

	namespace internal
	{
		static constexpr uint vertices_size = sizeof(float) * 4 * 8;
		static constexpr uint indices_size = 6 * sizeof(gl_point_index_t);

		Mesh sprite_mesh;

		void initTextureRenderer()
		{
			DynamicMesh dynamic_sprite_mesh = DynamicMesh
			(
				{
					//Vertex(1.0f,  1.0f, 0.0f,	0.0f,  0.0f, 1.0f,	1.0f, 0.0f),	//Верхний правый
					//Vertex(1.0f, -1.0f, 0.0f,	0.0f,  0.0f, 1.0f,	1.0f, 1.0f),	//Нижний правый
					//Vertex(-1.0f, -1.0f, 0.0f,	0.0f,  0.0f, 1.0f,	0.0f, 1.0f),	//Нижний левый
					//Vertex(-1.0f,  1.0f, 0.0f,	0.0f,  0.0f, 1.0f,	0.0f, 0.0f) 	//Верхний левый
						   //Позиции     		//Нормаль			//Текстурные координаты
					Vertex(0.5f,  0.5f, 0.0f,	0.0f,  0.0f, 1.0f,	1.0f, 0.0f),	//Верхний правый
					Vertex(0.5f, -0.5f, 0.0f,	0.0f,  0.0f, 1.0f,	1.0f, 1.0f),	//Нижний правый
					Vertex(-0.5f, -0.5f, 0.0f,	0.0f,  0.0f, 1.0f,	0.0f, 1.0f),	//Нижний левый
					Vertex(-0.5f,  0.5f, 0.0f,	0.0f,  0.0f, 1.0f,	0.0f, 0.0f) 	//Верхний левый
				},
				{
					2, 3, 0,
					0, 1, 2,
				}
			);
			sprite_mesh = dynamic_sprite_mesh();
		}

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

	    void set_world_matrix(const mat4& world)
	    {
			glUniformMatrix4fv(shader_layout_locations::world, 1, 0, (float*)&world);
	    }

	    void set_uv_matrix(const uv_matrix& uv)
	    {
			glUniformMatrix2fv(shader_layout_locations::uv, 1, 0, (float*)&uv);
	    }

	    void set_draw_color(const vec4& color)
	    {
			glUniform4fv(shader_layout_locations::color, 1, (float*)&color);
	    }

		void draw_texture(uint texture,const mat4& world, const uv_matrix& uv, const vec4& color)
		{
			set_world_matrix(world);
			set_uv_matrix(uv);
			set_draw_color(color);
			texture = texture ? texture : white_texture.container->texture_data.handle;
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
			sprite_mesh.draw();
		}
	}
}
