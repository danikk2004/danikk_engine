#pragma once

#include<danikk_engine/danikk_engine.h>

namespace danikk_engine
{
	namespace internal
	{
		uint32 glGenBuffer();

		void glDeleteBuffer(uint32 buffer);

		uint32 glGenTexture();

		void glDeletetexture(uint32 texture);

		uint32 glGenVertexArray();

		void  glDeleteVertexArray(uint32 vertex_array);

		void initGlObjectManager();
	}
}
