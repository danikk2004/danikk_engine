#include <danikk_engine/localization.h>

#define _(key, value) { key , value},

namespace danikk_engine
{
    danikk_framework::Localization localization
	{
    	_("error/create_window", 		"Failed to create window.")
    	_("error/glfwinit", 			"Failed to initialize GLFW.")
    	_("error/gladinit", 			"Failed to initialize GLAD.")
    	_("error/call_argv_init", 		"danikk_framework::argv::init is not called")
    	_("error/shader_compile", 		"shader compile error ")
    	_("error/cant_load_asset1", 	"Cant load ")
    	_("error/cant_load_asset2", 	" asset.")
		_("error/cant_open_data_file", 	"Cant open data file: ")
	};
}
