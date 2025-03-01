#pragma once

namespace stb
{
	//typedef unsigned char stbi_uc;
	unsigned char *load_from_memory(unsigned char const* buffer, int len, int *x, int *y, int *channels_in_file, int desired_channels);
}
