
#define STBI_ONLY_PNG
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include <stb_image.h>

namespace stb
{
	stbi_uc* load_from_memory(stbi_uc const* buffer, int len, int *x, int *y, int *channels_in_file, int desired_channels)
	{
		return stbi_load_from_memory(buffer, len, x, y, channels_in_file, desired_channels);
	}
}
