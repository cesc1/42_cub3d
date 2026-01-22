#include "cub3d.h"
#include "mlx.h"
#include <X11/X.h>
#include <math.h>

void	init_mlx(t_mlx_vars *mlx, t_input *input)
{
	mlx->input = *input;
	mlx->img.img = mlx_new_image(mlx->mlx, mlx->screen[0], mlx->screen[1]);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel,
			&mlx->img.line_length, &mlx->img.endian);
	open_img(mlx, &mlx->textures.north, input->texture_n);
	open_img(mlx, &mlx->textures.south, input->texture_s);
	open_img(mlx, &mlx->textures.east, input->texture_e);
	open_img(mlx, &mlx->textures.west, input->texture_o);
	mlx->input_state.w = 0;
	mlx->input_state.a = 0;
	mlx->input_state.s = 0;
	mlx->input_state.d = 0;
	mlx->input_state.left = 0;
	mlx->input_state.right = 0;
	mlx->input_state.escape = 0;
	init_vision(&mlx->vision, input);
}

void	init_texture_params(t_texture_render *tex_vars, t_texture *texture,
		t_vision *v, t_mlx_vars *data)
{
	if (v->side == 0)
		tex_vars->wall[0] = v->pos[1] + v->perp_wall_dist * v->ray_dir[1];
	else
		tex_vars->wall[0] = v->pos[0] + v->perp_wall_dist * v->ray_dir[0];
	tex_vars->wall[0] -= floor(tex_vars->wall[0]);
	tex_vars->tex[0] = (int)(tex_vars->wall[0] * (double)texture->width);
	if ((v->side == 0 && v->ray_dir[0] > 0) || (v->side == 1
			&& v->ray_dir[1] < 0))
		tex_vars->tex[0] = texture->width - tex_vars->tex[0] - 1;
	tex_vars->step = (double)texture->height / v->line_height;
	tex_vars->tex_pos = (v->draw[0] - data->screen[1] / 2 + v->line_height / 2)
		* tex_vars->step;
}

void	init_step_and_side_dist(t_vision *v)
{
	if (v->ray_dir[0] < 0)
	{
		v->step[0] = -1;
		v->side_dist[0] = (v->pos[0] - v->map[0]) * v->delta_dist[0];
	}
	else
	{
		v->step[0] = 1;
		v->side_dist[0] = (v->map[0] + 1.0 - v->pos[0]) * v->delta_dist[0];
	}
	if (v->ray_dir[1] < 0)
	{
		v->step[1] = -1;
		v->side_dist[1] = (v->pos[1] - v->map[1]) * v->delta_dist[1];
	}
	else
	{
		v->step[1] = 1;
		v->side_dist[1] = (v->map[1] + 1.0 - v->pos[1]) * v->delta_dist[1];
	}
}

void	init_vision(t_vision *v, t_input *input)
{
	v->pos[0] = input->start_col + 0.5;
	v->pos[1] = input->start_row + 0.5;
	initialdir(input->start_dir, v->dir, v->plane);
}

void	init_ray_direction(t_vision *v, int x, int *screen_width)
{
	v->camera = 2.0 * x / (double)*screen_width - 1.0;
	v->ray_dir[0] = v->dir[0] + v->plane[0] * v->camera;
	v->ray_dir[1] = v->dir[1] + v->plane[1] * v->camera;
	v->map[0] = (int)v->pos[0];
	v->map[1] = (int)v->pos[1];
	v->delta_dist[0] = get_delta_dist(v->ray_dir[0]);
	v->delta_dist[1] = get_delta_dist(v->ray_dir[1]);
}
