#include "cub3d.h"
#include <math.h>

void	move_forward(t_mlx_vars *data, t_input input, int *moved)
{
	double	move_speed;
	double	new[2];

	move_speed = 0.05;
	new[0] = data->vision.pos[0] + data->vision.dir[0] * move_speed;
	new[1] = data->vision.pos[1] + data->vision.dir[1] * move_speed;
	if (input.map[(int)new[1]][(int)data->vision.pos[0]] != '1')
		data->vision.pos[1] = new[1];
	if (input.map[(int)data->vision.pos[1]][(int)new[0]] != '1')
		data->vision.pos[0] = new[0];
	*moved = 1;
}

void	move_backward(t_mlx_vars *data, t_input input, int *moved)
{
	double	move_speed;
	double	new[2];

	move_speed = 0.05;
	new[0] = data->vision.pos[0] - data->vision.dir[0] * move_speed;
	new[1] = data->vision.pos[1] - data->vision.dir[1] * move_speed;
	if (input.map[(int)new[1]][(int)data->vision.pos[0]] != '1')
		data->vision.pos[1] = new[1];
	if (input.map[(int)data->vision.pos[1]][(int)new[0]] != '1')
		data->vision.pos[0] = new[0];
	*moved = 1;
}

void	move_left(t_mlx_vars *data, t_input input, int *moved)
{
	double	move_speed;
	double	new[2];

	move_speed = 0.05;
	new[0] = data->vision.pos[0] - data->vision.plane[0] * move_speed;
	new[1] = data->vision.pos[1] - data->vision.plane[1] * move_speed;
	if (input.map[(int)new[1]][(int)data->vision.pos[0]] != '1')
		data->vision.pos[1] = new[1];
	if (input.map[(int)data->vision.pos[1]][(int)new[0]] != '1')
		data->vision.pos[0] = new[0];
	*moved = 1;
}

void	move_right(t_mlx_vars *data, t_input input, int *moved)
{
	double	move_speed;
	double	new[2];

	move_speed = 0.05;
	new[0] = data->vision.pos[0] + data->vision.plane[0] * move_speed;
	new[1] = data->vision.pos[1] + data->vision.plane[1] * move_speed;
	if (input.map[(int)new[1]][(int)data->vision.pos[0]] != '1')
		data->vision.pos[1] = new[1];
	if (input.map[(int)data->vision.pos[1]][(int)new[0]] != '1')
		data->vision.pos[0] = new[0];
	*moved = 1;
}
