#include "cub3d.h"
#include "mlx.h"
#include <math.h>
#include <stdlib.h>

void	open_img(t_mlx_vars *data, t_texture *img, char *str)
{
	img->img = mlx_xpm_file_to_image(data->mlx, str, &img->width, &img->height);
	if (img->img == NULL)
	{
		printf("Advertencia: No se pudo cargar la imagen %s\n", str);
		printf("Se usará color por defecto\n");
		img->addr = NULL;
		img->width = 0;
		img->height = 0;
		return ;
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

void	draw_back(t_img_data *img, int sx, int sy, t_input imp)
{
	int	y;
	int	x;

	y = 0;
	while (y < (sy / 2))
	{
		x = 0;
		while (x != sx)
		{
			my_mlx_pixel_put(img, x, y, imp.col_c);
			x++;
		}
		y++;
	}
	while (y != sy)
	{
		x = 0;
		while (x != sx)
		{
			my_mlx_pixel_put(img, x, y, imp.col_f);
			x++;
		}
		y++;
	}
}

void	drawVerLine(t_img_data *img, int x, int *draw, int color)
{
	int	y;

	y = draw[0];
	while (y <= draw[1])
	{
		my_mlx_pixel_put(img, x, y, color);
		y++;
	}
}

void	initialdir(char direccion, double dir[2], double plane[2])
{
	if (direccion == 'N')
	{
		dir[0] = 0.0;
		dir[1] = -1.0;
		plane[0] = 0.66;
		plane[1] = 0.0;
	}
	else if (direccion == 'S')
	{
		dir[0] = 0.0;
		dir[1] = 1.0;
		plane[0] = -0.66;
		plane[1] = 0.0;
	}
	else if (direccion == 'W')
	{
		dir[0] = -1.0;
		dir[1] = 0.0;
		plane[0] = 0.0;
		plane[1] = -0.66;
	}
	else if (direccion == 'E')
	{
		dir[0] = 1.0;
		dir[1] = 0.0;
		plane[0] = 0.0;
		plane[1] = 0.66;
	}
}

void	init_vision(t_vision *v, t_input *input)
{
	v->pos[0] = input->start_col + 0.5;
	v->pos[1] = input->start_row + 0.5;
	initialdir(input->start_dir, v->dir, v->plane);
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

double	get_delta_dist(double ray)
{
	if (ray == 0)
		return (1e30);
	return (fabs(1.0 / ray));
}
t_texture	*get_wall_texture(t_textures *textures, t_vision *v)
{
	if (v->side == 0)
	{
		if (v->rayDir[0] > 0)
			return (&textures->west); // pared oeste
		else
			return (&textures->east); // pared este
	}
	else
	{
		if (v->rayDir[1] > 0)
			return (&textures->north); // pared norte
		else
			return (&textures->south); // pared sur
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

void	draw_textured_line(t_mlx_vars *data, int x, t_vision *v)
{
	t_texture	*texture;
	double		wallX;
	int			texX;
	double		step;
	double		texPos;
	int			texY;
	int			color;

	texture = get_wall_texture(&data->textures, v);
	if (v->side == 0) // Pared vertical
		wallX = v->pos[1] + v->perpWallDist * v->rayDir[1];
	else // Pared horizontal
		wallX = v->pos[0] + v->perpWallDist * v->rayDir[0];
	wallX -= floor(wallX);
	texX = (int)(wallX * (double)texture->width);
	if ((v->side == 0 && v->rayDir[0] > 0) || (v->side == 1
			&& v->rayDir[1] < 0))
		texX = texture->width - texX - 1;
	step = (double)texture->height / v->lineHeight;
	texPos = (v->draw[0] - data->screen[1] / 2 + v->lineHeight / 2) * step;
	for (int y = v->draw[0]; y <= v->draw[1]; y++)
	{
		texY = (int)texPos % texture->height;
		texPos += step;
		color = get_texture_pixel(texture, texX, texY);
		my_mlx_pixel_put(&data->img, x, y, color);
	}
}

void	draw_full_vision(t_mlx_vars *data, t_vision *v, int *s, t_input imp)
{
	int	x;
	int	hit;
	int	wall_color;

	draw_back(&data->img, s[0], s[1], imp);
	x = 0;
	while (x < s[0])
	{
		v->camera = 2.0 * x / (double)s[0] - 1.0;
		v->rayDir[0] = v->dir[0] + v->plane[0] * v->camera;
		v->rayDir[1] = v->dir[1] + v->plane[1] * v->camera;
		v->map[0] = (int)v->pos[0];
		v->map[1] = (int)v->pos[1];
		v->deltaDist[0] = get_delta_dist(v->rayDir[0]);
		v->deltaDist[1] = get_delta_dist(v->rayDir[1]);
		hit = 0;
		if (v->rayDir[0] < 0)
		{
			v->step[0] = -1;
			v->sideDist[0] = (v->pos[0] - v->map[0]) * v->deltaDist[0];
		}
		else
		{
			v->step[0] = 1;
			v->sideDist[0] = (v->map[0] + 1.0 - v->pos[0]) * v->deltaDist[0];
		}
		if (v->rayDir[1] < 0)
		{
			v->step[1] = -1;
			v->sideDist[1] = (v->pos[1] - v->map[1]) * v->deltaDist[1];
		}
		else
		{
			v->step[1] = 1;
			v->sideDist[1] = (v->map[1] + 1.0 - v->pos[1]) * v->deltaDist[1];
		}
		hit = 0;
		while (!hit)
		{
			if (v->sideDist[0] < v->sideDist[1])
			{
				v->sideDist[0] += v->deltaDist[0];
				v->map[0] += v->step[0];
				v->side = 0;
			}
			else
			{
				v->sideDist[1] += v->deltaDist[1];
				v->map[1] += v->step[1];
				v->side = 1;
			}
			if (v->map[0] < 0 || v->map[1] < 0 || v->map[0] >= imp.w
				|| v->map[1] >= imp.h)
			{
				hit = 1;
				break ;
			}
			if (imp.map[v->map[1]][v->map[0]] == '1')
				hit = 1;
		}
		if (v->side == 0)
			v->perpWallDist = (v->sideDist[0] - v->deltaDist[0]);
		else
			v->perpWallDist = (v->sideDist[1] - v->deltaDist[1]);
		if (v->perpWallDist <= 0)
			v->perpWallDist = 0.1;
		v->lineHeight = (int)(s[1] / v->perpWallDist);
		v->draw[0] = -v->lineHeight / 2 + s[1] / 2;
		if (v->draw[0] < 0)
			v->draw[0] = 0;
		v->draw[1] = v->lineHeight / 2 + s[1] / 2;
		if (v->draw[1] >= s[1])
			v->draw[1] = s[1] - 1;
		if (v->side == 0)
		{
			if (v->rayDir[0] > 0)
				wall_color = create_trgb(0, 255, 0, 0); // Pared OESTE
			else
				wall_color = create_trgb(0, 0, 255, 0); // Pared ESTE
		}
		else
		{
			if (v->rayDir[1] > 0)
				wall_color = create_trgb(0, 0, 0, 255); // Pared NORTE
			else
				wall_color = create_trgb(0, 255, 255, 0); // Pared SUR
		}
		if (textures_are_loaded(&data->textures))
			draw_textured_line(data, x, v);
		else
			drawVerLine(&data->img, x, v->draw, wall_color);
		x++;
	}
}
