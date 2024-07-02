#include "../cub3d.h"

int	create_trgb(unsigned char t, unsigned char r,
				unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

