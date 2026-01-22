#include "cub3d.h"
#include "mlx.h"
#include <math.h>
#include <stdlib.h>

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

void	draw_ver_line(t_img_data *img, int x, int *draw, int color)
{
	int	y;

	y = draw[0];
	while (y <= draw[1])
	{
		my_mlx_pixel_put(img, x, y, color);
		y++;
	}
}

// void	init_texture_params(t_texture_render *tex_vars, t_texture *texture,
// 		t_vision *v, t_mlx_vars *data)
// {
// 	if (v->side == 0)
// 		tex_vars->wall[0] = v->pos[1] + v->perp_wall_dist * v->ray_dir[1];
// 	else
// 		tex_vars->wall[0] = v->pos[0] + v->perp_wall_dist * v->ray_dir[0];
// 	tex_vars->wall[0] -= floor(tex_vars->wall[0]);
// 	tex_vars->tex[0] = (int)(tex_vars->wall[0] * (double)texture->width);
// 	if ((v->side == 0 && v->ray_dir[0] > 0) || (v->side == 1
// 			&& v->ray_dir[1] < 0))
// 		tex_vars->tex[0] = texture->width - tex_vars->tex[0] - 1;
// 	tex_vars->step = (double)texture->height / v->line_height;
// 	tex_vars->tex_pos = (v->draw[0] - data->screen[1] / 2 + v->line_height / 2)
// 		* tex_vars->step;
// }

void	draw_textured_line(t_mlx_vars *data, int x, t_vision *v)
{
	t_texture			*texture;
	t_texture_render	tex_vars;
	int					y;

	texture = get_wall_texture(&data->textures, v);
	init_texture_params(&tex_vars, texture, v, data);
	y = v->draw[0];
	while (y <= v->draw[1])
	{
		tex_vars.tex[1] = (int)tex_vars.tex_pos % texture->height;
		tex_vars.tex_pos += tex_vars.step;
		tex_vars.color = get_texture_pixel(texture, tex_vars.tex[0],
				tex_vars.tex[1]);
		my_mlx_pixel_put(&data->img, x, y, tex_vars.color);
		y++;
	}
}

void	draw_single_ray(t_mlx_vars *data, t_vision *v, int x)
{
	int	wall_color;

	calculate_wall_params(v, data->screen);
	wall_color = get_wall_color(v);
	if (textures_are_loaded(&data->textures))
		draw_textured_line(data, x, v);
	else
		draw_ver_line(&data->img, x, v->draw, wall_color);
}

void	draw_full_vision(t_mlx_vars *data, t_vision *v, int *s, t_input imp)
{
	int	x;

	draw_back(&data->img, s[0], s[1], imp);
	x = 0;
	while (x < s[0])
	{
		init_ray_params(v, x, &s[0]);
		perform_dda(v, &imp);
		draw_single_ray(data, v, x);
		x++;
	}
}
