#include <functional>
#include <danikk_engine/danikk_engine.h>

namespace danikk_engine
{
	namespace internal
	{
		 void _glexec(std::function<void()> func);
	}

	//glexec используется только для исполнения opengl кода для загрузки графических ассетов.
	//Если использовать его не по назначению будет фриз игры, ошибка opengl или sigsegv.
	#define glexec(code) danikk_engine::internal::_glexec([&](){code});
}
