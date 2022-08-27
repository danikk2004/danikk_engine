#pragma once

#include <danikk_engine/shader.h>
#include <danikk_engine/texture.h>
#include <danikk_engine/model.h>

namespace danikk_engine
{
	namespace internal
	{
		void initDataManager();

		/*
		 * В случае, если шейдер не может загрузиться,
		 * то загружает виртуальный аварийный шейдер
		 * Эта функция его инициализирует.
		 * */
		void initDefaultShaders();
	}

	Shader loadShader(const char* name);

	Shader createShader(const char* name, const char* vertex_shader, const char* fragment_shader);

	Texture loadTexture(const char* name);
}
