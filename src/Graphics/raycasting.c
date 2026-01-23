#include "cub3d.h"
#include <math.h>

void	init_ray_params(t_vision *v, int x, int *screen_width)
{
	init_ray_direction(v, x, screen_width);
	init_step_and_side_dist(v);
}

int	check_boundaries(t_vision *v, t_input *imp)
{
	if (v->map[0] < 0 || v->map[1] < 0 || v->map[0] >= imp->w
		|| v->map[1] >= imp->h)
		return (1);
	if (imp->map[v->map[1]][v->map[0]] == '1')
		return (1);
	return (0);
}

int	perform_dda(t_vision *v, t_input *imp)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (v->side_dist[0] < v->side_dist[1])
		{
			v->side_dist[0] += v->delta_dist[0];
			v->map[0] += v->step[0];
			v->side = 0;
		}
		else
		{
			v->side_dist[1] += v->delta_dist[1];
			v->map[1] += v->step[1];
			v->side = 1;
		}
		hit = check_boundaries(v, imp);
	}
	return (hit);
}

void	calculate_wall_params(t_vision *v, int *screen)
{
	if (v->side == 0)
		v->perp_wall_dist = (v->side_dist[0] - v->delta_dist[0]);
	else
		v->perp_wall_dist = (v->side_dist[1] - v->delta_dist[1]);
	if (v->perp_wall_dist <= 0)
		v->perp_wall_dist = 0.1;
	v->line_height = (int)(screen[1] / v->perp_wall_dist);
	v->draw[0] = -v->line_height / 2 + screen[1] / 2;
	if (v->draw[0] < 0)
		v->draw[0] = 0;
	v->draw[1] = v->line_height / 2 + screen[1] / 2;
	if (v->draw[1] >= screen[1])
		v->draw[1] = screen[1] - 1;
}

int	get_wall_color(t_vision *v)
{
	if (v->side == 0)
	{
		if (v->ray_dir[0] > 0)
			return (create_trgb(0, 255, 0, 0));
		else
			return (create_trgb(0, 0, 255, 0));
	}
	else
	{
		if (v->ray_dir[1] > 0)
			return (create_trgb(0, 0, 0, 255));
		else
			return (create_trgb(0, 255, 255, 0));
	}
}
