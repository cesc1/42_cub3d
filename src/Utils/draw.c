#include "cub3d.h"
#include <math.h>

// void	draw_filled_circle(t_img_data *data, int xc, int yc, int r, int color)
// {
// 	int	x;
// 	int	y;

// 	y = -r;
// 	while (y <= r)
// 	{
// 		x = -r;
// 		while (x <= r)
// 		{
// 			if (x * x + y * y <= r * r)
// 				my_mlx_pixel_put(data, xc + x, yc + y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// void	draw_cros(t_img_data *data, int x_size, int y_size, int color)
// {
// 	int	x;
// 	int	y;

// 	x = x_size / 2;
// 	y = 0;
// 	while (y <= y_size)
// 	{
// 		my_mlx_pixel_put(data, x, y++, color);
// 	}
// 	y = y_size / 2;
// 	x = 0;
// 	while (x <= x_size)
// 	{
// 		my_mlx_pixel_put(data, x++, y, color);
// 	}
// }

// void	draw_vison(t_img_data *data, double *pos, double *v_vis, int color)
// {
// 	double	t;
// 	int		x;
// 	int		y;

// 	t = 0;
// 	while (t < 2000)
// 	{
// 		x = (int)(pos[0] + v_vis[0] * t);
// 		y = (int)(pos[1] + v_vis[1] * t);
// 		if (x < 0 || x >= 1000 || y < 0 || y >= 1000)
// 			break ;
// 		my_mlx_pixel_put(data, x, y, color);
// 		t += 0.1;
// 	}
// }
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

char	initialpos(char **map, double pos[2])
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'W'
				|| map[y][x] == 'E')
			{
				pos[0] = x + 0.5;
				pos[1] = y + 0.5;
				return (map[y][x]);
			}
			x++;
		}
		y++;
	}
	return (0);
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

void	init_vision(t_vision *v, char **map)
{
	char	direccion;

	direccion = initialpos(map, v->pos);
	// v->pos[0] = 22;
	// v->pos[1] = 12;
	initialdir(direccion, v->dir, v->plane);
	// v->dir[0] = -1.0;
	// v->dir[1] = 0.0;
	//	v->plane[0] = 0.66;
	//	v->plane[1] = 0;
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

void	draw_full_vision(t_img_data *data, t_vision *v, int *s, t_input imp)
{
	int	x;
	int	hit;

	clear_image(data, s[0], s[1], create_trgb(0, 0, 0, 255));
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
			drawVerLine(data, x, v->draw, create_trgb(0, 255, 0, 255));
		else
			drawVerLine(data, x, v->draw, create_trgb(0, 255, 0, 255));
		x++;
	}
}
// void	draw_full_vision(t_img_data *data, t_vision *v)
// {
// 	// Calcular puntos del plano de cámara
// 	clear_image(data, 1000, 1000, create_trgb(0, 0, 0, 0));
// 	v->plane1[0] = v->pos[0] + v->v_vis[0] * v->fov_scale + v->v_per[0]
// 		* v->fov_scale;
// 	v->plane1[1] = v->pos[1] + v->v_vis[1] * v->fov_scale + v->v_per[1]
// 		* v->fov_scale;
// 	v->plane2[0] = v->pos[0] + v->v_vis[0] * v->fov_scale - v->v_per[0]
// 		* v->fov_scale;
// 	v->plane2[1] = v->pos[1] + v->v_vis[1] * v->fov_scale - v->v_per[1]
// 		* v->fov_scale;
// 	// Dibujar cruz central
// 	draw_cros(data, 1000, 1000, create_trgb(0, 0, 0, 255));
// 	// Dibujar jugador (círculo verde)
// 	draw_filled_circle(data, (int)v->pos[0], (int)v->pos[1], 10, create_trgb(0,
// 			255, 0, 255));
// 	// Dibujar rayo central de visión (azul)
// 	draw_vison(data, v->pos, v->v_vis, create_trgb(0, 0, 255, 255));
// 	// Dibujar línea del plano de cámara (amarillo)
// 	draw_line(data, v->plane1, v->plane2, create_trgb(0, 255, 255, 0));
// 	// Calcular y dibujar rayos hacia los extremos
// 	v->v_dir[0] = v->plane1[0] - v->pos[0];
// 	v->v_dir[1] = v->plane1[1] - v->pos[1];
// 	draw_vison(data, v->pos, v->v_dir, create_trgb(0, 0, 255, 255));
// 	v->v_dir[0] = v->plane2[0] - v->pos[0];
// 	v->v_dir[1] = v->plane2[1] - v->pos[1];
// 	draw_vison(data, v->pos, v->v_dir, create_trgb(0, 0, 255, 255));
//}
