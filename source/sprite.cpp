#include <glm/gtc/matrix_transform.hpp>
#include <danikk_framework/memory.h>

#include <danikk_engine/sprite.h>
#include <danikk_engine/texture.h>
#include <danikk_engine/internal/texture_methods.h>
#include <danikk_engine/matrix/uv.h>
#include <danikk_engine/matrix/pos.h>

namespace danikk_engine
{
	using namespace internal;

	Sprite::Sprite(Sprite& other) : Asset(other.container)
	{
		this->uv=other.uv;
	}

	void Sprite::operator=(Sprite& other)
	{
    	this->~Asset();
		new (this) Sprite(other);
	}

	void Sprite::operator=(Sprite&& other)
	{
    	this->~Asset();
		new (this) Sprite(other);
	}

	void Sprite::draw(vec2 position, vec2 size, float rotation, vec4 color)
	{
		uint texture_handle = container ? container->texture_data.handle : 0;
		draw_texture(texture_handle , create_pos_matrix(position, size, rotation), uv, color);
	}

	void Sprite::draw(mat4 world, vec4 color)
	{
		uint texture_handle = container ? container->texture_data.handle : 0;
		draw_texture(texture_handle , world, uv, color);
	}
}
