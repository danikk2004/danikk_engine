#include <danikk_engine/danikk_engine.h>

namespace danikk_engine
{
	bool for_n_frames(int n)
	{
		return frameCount() % n == 0;
	}
}
