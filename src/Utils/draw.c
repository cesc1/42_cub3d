#include "cub3d.h"

void	draw_filled_circle(t_img_data *data, int xc, int yc, int r, int color)
{
	int	x;
	int	y;

	y = -r;
	while (y <= r)
	{
		x = -r;
		while (x <= r)
		{
			if (x * x + y * y <= r * r)
				my_mlx_pixel_put(data, xc + x, yc + y, color);
			x++;
		}
		y++;
	}
}

void	draw_cros(t_img_data *data, int x_size, int y_size, int color)
{
	int	x;
	int	y;

	x = x_size / 2;
	y = 0;
	while (y <= y_size)
	{
		my_mlx_pixel_put(data, x, y++, color);
	}
	y = y_size / 2;
	x = 0;
	while (x <= x_size)
	{
		my_mlx_pixel_put(data, x++, y, color);
	}
}

void	draw_vison(t_img_data *data, double *pos, double *v_vis, int color)
{
	double	t;
	int		x;
	int		y;

	t = 0;
	while (t < 2000)
	{
		x = (int)(pos[0] + v_vis[0] * t);
		y = (int)(pos[1] + v_vis[1] * t);
		if (x < 0 || x >= 1000 || y < 0 || y >= 1000)
			break ;
		my_mlx_pixel_put(data, x, y, color);
		t += 0.1;
	}
}
void	draw_line(t_img_data *img, double p0[2], double p1[2], int color)
{
	double	t;
	int		x;
	int		y;

	t = 0;
	while (t < 1)
	{
		x = (int)(p0[0] + (p1[0] - p0[0]) * t);
		y = (int)(p0[1] + (p1[1] - p0[1]) * t);
		my_mlx_pixel_put(img, x, y, color);
		t += 0.001;
	}
}

void	init_vision(t_vision *v, int x, int y)
{
	v->pos[0] = (double)(x / 2);
	v->pos[1] = (double)(y / 2);
	v->v_vis[0] = 0.0;
	v->v_vis[1] = -1.0;
	v->v_per[0] = -v->v_vis[1];
	v->v_per[1] = v->v_vis[0];
	v->fov_scale = 100.0;
	v->ang = -90.0;
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
void	draw_full_vision(t_img_data *data, t_vision *v)
{
	// Calcular puntos del plano de cámara
	clear_image(data, 1000, 1000, create_trgb(0, 0, 0, 0));
	v->plane1[0] = v->pos[0] + v->v_vis[0] * v->fov_scale + v->v_per[0]
		* v->fov_scale;
	v->plane1[1] = v->pos[1] + v->v_vis[1] * v->fov_scale + v->v_per[1]
		* v->fov_scale;
	v->plane2[0] = v->pos[0] + v->v_vis[0] * v->fov_scale - v->v_per[0]
		* v->fov_scale;
	v->plane2[1] = v->pos[1] + v->v_vis[1] * v->fov_scale - v->v_per[1]
		* v->fov_scale;
	// Dibujar cruz central
	draw_cros(data, 1000, 1000, create_trgb(0, 0, 0, 255));
	// Dibujar jugador (círculo verde)
	draw_filled_circle(data, (int)v->pos[0], (int)v->pos[1], 10, create_trgb(0,
			255, 0, 255));
	// Dibujar rayo central de visión (azul)
	draw_vison(data, v->pos, v->v_vis, create_trgb(0, 0, 255, 255));
	// Dibujar línea del plano de cámara (amarillo)
	draw_line(data, v->plane1, v->plane2, create_trgb(0, 255, 255, 0));
	// Calcular y dibujar rayos hacia los extremos
	v->v_dir[0] = v->plane1[0] - v->pos[0];
	v->v_dir[1] = v->plane1[1] - v->pos[1];
	draw_vison(data, v->pos, v->v_dir, create_trgb(0, 0, 255, 255));
	v->v_dir[0] = v->plane2[0] - v->pos[0];
	v->v_dir[1] = v->plane2[1] - v->pos[1];
	draw_vison(data, v->pos, v->v_dir, create_trgb(0, 0, 255, 255));
}
