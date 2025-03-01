#include <danikk_engine/gui/subwindow.h>

namespace danikk_engine
{
	SubWindow::SubWindow()
	{
		border_draw_style = &default_draw_styles::window_border;
		flags[GUIElementFlags::draggable] = true;
	}
}
