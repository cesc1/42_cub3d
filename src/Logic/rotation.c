#include "cub3d.h"
#include <math.h>

void	rotate_left(t_mlx_vars *data, int *moved)
{
	double	rot_speed;
	double	old_dir;
	double	old_plane;

	rot_speed = 0.020;
	old_dir = data->vision.dir[0];
	data->vision.dir[0] = data->vision.dir[0] * cos(-rot_speed)
		- data->vision.dir[1] * sin(-rot_speed);
	data->vision.dir[1] = old_dir * sin(-rot_speed) + data->vision.dir[1]
		* cos(-rot_speed);
	old_plane = data->vision.plane[0];
	data->vision.plane[0] = data->vision.plane[0] * cos(-rot_speed)
		- data->vision.plane[1] * sin(-rot_speed);
	data->vision.plane[1] = old_plane * sin(-rot_speed) + data->vision.plane[1]
		* cos(-rot_speed);
	*moved = 1;
}

void	rotate_right(t_mlx_vars *data, int *moved)
{
	double	rot_speed;
	double	old_dir;
	double	old_plane;

	rot_speed = 0.020;
	old_dir = data->vision.dir[0];
	data->vision.dir[0] = data->vision.dir[0] * cos(rot_speed)
		- data->vision.dir[1] * sin(rot_speed);
	data->vision.dir[1] = old_dir * sin(rot_speed) + data->vision.dir[1]
		* cos(rot_speed);
	old_plane = data->vision.plane[0];
	data->vision.plane[0] = data->vision.plane[0] * cos(rot_speed)
		- data->vision.plane[1] * sin(rot_speed);
	data->vision.plane[1] = old_plane * sin(rot_speed) + data->vision.plane[1]
		* cos(rot_speed);
	*moved = 1;
}
