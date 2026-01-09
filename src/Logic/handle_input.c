#include "cub3d.h"
#include "mlx.h"
#include <X11/keysym.h>
#include <math.h>

void	redraw_scene(t_mlx_vars *data, int *screen, t_input input)
{
	draw_full_vision(&data->img, &data->vision, screen, input);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

void	move_forward(t_mlx_vars *data, t_input input)
{
	double	moveSpeed;
	double	newX;
	double	newY;

	moveSpeed = 0.1;
	newX = data->vision.pos[0] + data->vision.dir[0] * moveSpeed;
	newY = data->vision.pos[1] + data->vision.dir[1] * moveSpeed;
	if (input.map[(int)newY][(int)data->vision.pos[0]] != '1')
		data->vision.pos[1] = newY;
	if (input.map[(int)data->vision.pos[1]][(int)newX] != '1')
		data->vision.pos[0] = newX;
}

void	move_left(t_mlx_vars *data, t_input input)
{
	double	moveSpeed;
	double	newX;
	double	newY;

	moveSpeed = 0.1;
	newX = data->vision.pos[0] - data->vision.plane[0] * moveSpeed;
	newY = data->vision.pos[1] - data->vision.plane[1] * moveSpeed;
	if (input.map[(int)newY][(int)data->vision.pos[0]] != '1')
		data->vision.pos[1] = newY;
	if (input.map[(int)data->vision.pos[1]][(int)newX] != '1')
		data->vision.pos[0] = newX;
}

void	move_right(t_mlx_vars *data, t_input input)
{
	double	moveSpeed;
	double	newX;
	double	newY;

	moveSpeed = 0.1;
	newX = data->vision.pos[0] + data->vision.plane[0] * moveSpeed;
	newY = data->vision.pos[1] + data->vision.plane[1] * moveSpeed;
	if (input.map[(int)newY][(int)data->vision.pos[0]] != '1')
		data->vision.pos[1] = newY;
	if (input.map[(int)data->vision.pos[1]][(int)newX] != '1')
		data->vision.pos[0] = newX;
}

void	move_backward(t_mlx_vars *data, t_input input)
{
	double	moveSpeed;
	double	newX;
	double	newY;

	moveSpeed = 0.1;
	newX = data->vision.pos[0] - data->vision.dir[0] * moveSpeed;
	newY = data->vision.pos[1] - data->vision.dir[1] * moveSpeed;
	if (input.map[(int)newY][(int)data->vision.pos[0]] != '1')
		data->vision.pos[1] = newY;
	if (input.map[(int)data->vision.pos[1]][(int)newX] != '1')
		data->vision.pos[0] = newX;
}

void	rotate_left(t_mlx_vars *data)
{
	double	rotSpeed;
	double	oldDirX;
	double	oldPlaneX;

	rotSpeed = 0.05;
	oldDirX = data->vision.dir[0];
	data->vision.dir[0] = data->vision.dir[0] * cos(-rotSpeed)
		- data->vision.dir[1] * sin(-rotSpeed);
	data->vision.dir[1] = oldDirX * sin(-rotSpeed) + data->vision.dir[1]
		* cos(-rotSpeed);
	oldPlaneX = data->vision.plane[0];
	data->vision.plane[0] = data->vision.plane[0] * cos(-rotSpeed)
		- data->vision.plane[1] * sin(-rotSpeed);
	data->vision.plane[1] = oldPlaneX * sin(-rotSpeed) + data->vision.plane[1]
		* cos(-rotSpeed);
}

void	rotate_rigth(t_mlx_vars *data)
{
	double	rotSpeed;
	double	oldDirX;
	double	oldPlaneX;

	rotSpeed = 0.05;
	oldDirX = data->vision.dir[0];
	data->vision.dir[0] = data->vision.dir[0] * cos(rotSpeed)
		- data->vision.dir[1] * sin(rotSpeed);
	data->vision.dir[1] = oldDirX * sin(rotSpeed) + data->vision.dir[1]
		* cos(rotSpeed);
	oldPlaneX = data->vision.plane[0];
	data->vision.plane[0] = data->vision.plane[0] * cos(rotSpeed)
		- data->vision.plane[1] * sin(rotSpeed);
	data->vision.plane[1] = oldPlaneX * sin(rotSpeed) + data->vision.plane[1]
		* cos(rotSpeed);
}

int	handle_input(int keysym, t_mlx_vars *data)
{
	if (keysym == XK_Escape)
		return (close_mlx(data));
	else if (keysym == XK_w)
		move_forward(data, data->input);
	else if (keysym == XK_d)
		move_right(data, data->input);
	else if (keysym == XK_s)
		move_backward(data, data->input);
	else if (keysym == XK_a)
		move_left(data, data->input);
	else if (keysym == XK_Left)
		rotate_left(data);
	else if (keysym == XK_Right)
		rotate_rigth(data);
	redraw_scene(data, data->screen, data->input);
	return (0);
}