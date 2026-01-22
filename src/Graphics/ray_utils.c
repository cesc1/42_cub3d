#include "cub3d.h"
#include <math.h>

double	get_delta_dist(double ray)
{
	if (ray == 0)
		return (1e30);
	return (fabs(1.0 / ray));
}

void	clear_image(t_img_data *data, int width, int height, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
}
