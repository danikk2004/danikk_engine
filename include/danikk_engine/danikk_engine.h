#pragma once

#include <functional>

#include <danikk_framework/danikk_framework.h>
#include <danikk_framework/dynamic_array.h>
#include <danikk_framework/string.h>
#include <glm/glm.hpp>

using namespace glm;
using danikk_framework::String;
using danikk_framework::DynamicArray;

namespace danikk_engine
{
	//Эти функции нужно будет определить в проекте игры.
	//А main определён уже в движке, его переопределять не надо.
	void begin();

	void update();

	void draw();
	//

    void exit();

    void fatalError(const char* message);

    void fatalError(const String& message);

    //glexec используется только для запуска gl кода для загрузки графических ассетов.
    //Если использовать его не по назначению будет ошибка opengl или gigsegvъ.
	#define glexec(code) danikk_engine::_glexec([&]{code});

    void _glexec(std::function<void()> func);

	#define GLOBAL_DF_USE(NAME) using danikk_framework::NAME;
	GLOBAL_DF_USE(int8)
	GLOBAL_DF_USE(uint8)
	GLOBAL_DF_USE(int16)
	GLOBAL_DF_USE(uint16)
	GLOBAL_DF_USE(int32)
	GLOBAL_DF_USE(uint32)
	GLOBAL_DF_USE(int64)
	GLOBAL_DF_USE(uint64)
	GLOBAL_DF_USE(DynamicArray);
	GLOBAL_DF_USE(MemoryStream)
	#undef GLOBAL_DF_USE

	using std::move;

	class Texture;
}
