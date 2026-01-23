#include "cub3d.h"
#include <math.h>

t_texture	*get_wall_texture(t_textures *textures, t_vision *v)
{
	if (v->side == 0)
	{
		if (v->ray_dir[0] > 0)
			return (&textures->west);
		else
			return (&textures->east);
	}
	else
	{
		if (v->ray_dir[1] > 0)
			return (&textures->north);
		else
			return (&textures->south);
	}
}

int	get_texture_pixel(t_texture *tex, int x, int y)
{
	char	*dst;

	dst = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

int	textures_are_loaded(t_textures *tex)
{
	return (tex->north.img != NULL && tex->north.addr != NULL
		&& tex->south.img != NULL && tex->south.addr != NULL
		&& tex->east.img != NULL && tex->east.addr != NULL
		&& tex->west.img != NULL && tex->west.addr != NULL);
}
