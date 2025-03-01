#include <danikk_engine/matrix/uv.h>
#include <danikk_engine/matrix/pos.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace danikk_engine
{
	using namespace glm;

	mat4 create_world_matrix(vec2 position, vec2 size)
	{
		mat4 pos = mat4(1.0f);

		pos = translate(pos, glm::vec3(position, 0.0f));
		pos = scale(pos, glm::vec3(size, 1.0f));

		return pos;
	}

	mat4 create_world_matrix(vec2 position, float size)
	{
		mat4 pos = mat4(1.0f);

		pos = translate(pos, glm::vec3(position, 0.0f));
		pos = scale(pos, glm::vec3(size, size, 1.0f));

		return pos;
	}


	mat4 create_world_matrix(vec2 position, vec2 size, float rotation)
	{
		mat4 pos = mat4(1.0f);

		pos = translate(pos, glm::vec3(position, 0.0f));
		pos = rotate(pos, rotation, glm::vec3(0, 0, 1.0f));
		pos = scale(pos, glm::vec3(size, 1.0f));

		return pos;
	}

	mat4 create_pos_matrix(vec2 position, vec2 size, float rotation)
	{
		mat4 pos = mat4(0.0f);
		pos[0].x = size.x;
		pos[0].y = size.y;
		pos[1].x = position.x;
		pos[1].y = position.y;
		return pos;
	}

	uv_matrix create_uv_matrix(
			uint x, uint y,
			uint width, uint height,
			uint texture_width, uint texture_height)
	{
		float uv_x_scale = (float)width / (float)texture_width;
		float uv_y_scale = (float)height / (float)texture_height;
		float uv_x_offset = (float)x / (float)texture_width;
		float uv_y_offset = (float)y / (float)texture_height;

		return create_uv_matrix(uv_x_offset, uv_y_offset, uv_x_scale, uv_y_scale);
	}

	uv_matrix create_uv_matrix(float x, float y, float scale)
	{
		return create_uv_matrix(x, y, scale, scale);
	}

	uv_matrix create_uv_matrix(float x, float y, float scale_x, float scale_y)
	{
		uv_matrix result(1.0f);

		//result = glm::scale(result, vec3(scale_x, scale_y, 0));
		//result = glm::translate(result, vec3(x, y, 0));

		result[0][0] = scale_x;
		result[0][1] = scale_y;
		result[1][0] = x;
		result[1][1] = y;

		return result;
	}

	uv_matrix fill_uv_matrix;

	namespace internal
	{

		void initUV()
		{
			fill_uv_matrix = create_uv_matrix(0.0f, 0.0f, 1.0f, 1.0f);
		}
	}

}
