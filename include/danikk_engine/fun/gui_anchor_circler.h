#pragma once
#include <danikk_engine/danikk_engine.h>
#include <danikk_engine/gui.h>

namespace danikk_engine
{
	class GuiAnchorCircler
	{
		int counter = 0;
		int index = 0;
		int frame_delay;

		int8 anchor_arr[8];
	public:
		GuiAnchorCircler(int frame_delay)
		{
			this->frame_delay = frame_delay;
			anchor_arr[GUIAnchor::top] = GUIAnchor::top;
			anchor_arr[GUIAnchor::top_right] = GUIAnchor::top_right;
			anchor_arr[GUIAnchor::right] = GUIAnchor::right;
			anchor_arr[GUIAnchor::down_right] = GUIAnchor::down_right;
			anchor_arr[GUIAnchor::down] = GUIAnchor::down;
			anchor_arr[GUIAnchor::down_left] = GUIAnchor::down_left;
			anchor_arr[GUIAnchor::left] = GUIAnchor::left;
			anchor_arr[GUIAnchor::top_left] = GUIAnchor::top_left;
		}

		int get()
		{
	    	counter++;
	    	if(counter >= frame_delay)
	    	{
	    		counter = 0;
	    		index++;
	    		if(index >= 8)
	    		{
	    			index = 0;
	    		}
	    	}
	    	return anchor_arr[index];
		}
	};
}
