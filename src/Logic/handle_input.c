#include "cub3d.h"
#include "mlx.h"
#include <X11/keysym.h>
#include <math.h>

int	key_press(int keysym, t_mlx_vars *data)
{
	if (keysym == XK_Escape)
		return (close_mlx(data));
	else if (keysym == XK_w)
		data->input_state.w = 1;
	else if (keysym == XK_a)
		data->input_state.a = 1;
	else if (keysym == XK_s)
		data->input_state.s = 1;
	else if (keysym == XK_d)
		data->input_state.d = 1;
	else if (keysym == XK_Left)
		data->input_state.left = 1;
	else if (keysym == XK_Right)
		data->input_state.right = 1;
	return (0);
}

int	key_release(int keysym, t_mlx_vars *data)
{
	if (keysym == XK_w)
		data->input_state.w = 0;
	else if (keysym == XK_a)
		data->input_state.a = 0;
	else if (keysym == XK_s)
		data->input_state.s = 0;
	else if (keysym == XK_d)
		data->input_state.d = 0;
	else if (keysym == XK_Left)
		data->input_state.left = 0;
	else if (keysym == XK_Right)
		data->input_state.right = 0;
	return (0);
}

void	redraw_scene(t_mlx_vars *data, int *screen, t_input input)
{
	draw_full_vision(data, &data->vision, screen, input);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

void	move_forward(t_mlx_vars *data, t_input input, int *moved)
{
	double	moveSpeed;
	double	newX;
	double	newY;

	moveSpeed = 0.05;
	newX = data->vision.pos[0] + data->vision.dir[0] * moveSpeed;
	newY = data->vision.pos[1] + data->vision.dir[1] * moveSpeed;
	if (input.map[(int)newY][(int)data->vision.pos[0]] != '1')
		data->vision.pos[1] = newY;
	if (input.map[(int)data->vision.pos[1]][(int)newX] != '1')
		data->vision.pos[0] = newX;
	*moved = 1;
}

void	move_left(t_mlx_vars *data, t_input input, int *moved)
{
	double	moveSpeed;
	double	newX;
	double	newY;

	moveSpeed = 0.05;
	newX = data->vision.pos[0] - data->vision.plane[0] * moveSpeed;
	newY = data->vision.pos[1] - data->vision.plane[1] * moveSpeed;
	if (input.map[(int)newY][(int)data->vision.pos[0]] != '1')
		data->vision.pos[1] = newY;
	if (input.map[(int)data->vision.pos[1]][(int)newX] != '1')
		data->vision.pos[0] = newX;
	*moved = 1;
}

void	move_right(t_mlx_vars *data, t_input input, int *moved)
{
	double	moveSpeed;
	double	newX;
	double	newY;

	moveSpeed = 0.05;
	newX = data->vision.pos[0] + data->vision.plane[0] * moveSpeed;
	newY = data->vision.pos[1] + data->vision.plane[1] * moveSpeed;
	if (input.map[(int)newY][(int)data->vision.pos[0]] != '1')
		data->vision.pos[1] = newY;
	if (input.map[(int)data->vision.pos[1]][(int)newX] != '1')
		data->vision.pos[0] = newX;
	*moved = 1;
}

void	move_backward(t_mlx_vars *data, t_input input, int *moved)
{
	double	moveSpeed;
	double	newX;
	double	newY;

	moveSpeed = 0.05;
	newX = data->vision.pos[0] - data->vision.dir[0] * moveSpeed;
	newY = data->vision.pos[1] - data->vision.dir[1] * moveSpeed;
	if (input.map[(int)newY][(int)data->vision.pos[0]] != '1')
		data->vision.pos[1] = newY;
	if (input.map[(int)data->vision.pos[1]][(int)newX] != '1')
		data->vision.pos[0] = newX;
	*moved = 1;
}

void	rotate_left(t_mlx_vars *data, int *moved)
{
	double	rotSpeed;
	double	oldDirX;
	double	oldPlaneX;

	rotSpeed = 0.020;
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
	*moved = 1;
}

void	rotate_rigth(t_mlx_vars *data, int *moved)
{
	double	rotSpeed;
	double	oldDirX;
	double	oldPlaneX;

	rotSpeed = 0.020;
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
	*moved = 1;
}

void	update_movement(t_mlx_vars *data)
{
	int	moved;

	moved = 0;
	if (data->input_state.w)
		move_forward(data, data->input, &moved);
	if (data->input_state.s)
		move_backward(data, data->input, &moved);
	if (data->input_state.a)
		move_left(data, data->input, &moved);
	if (data->input_state.d)
		move_right(data, data->input, &moved);
	if (data->input_state.left)
		rotate_left(data, &moved);
	if (data->input_state.right)
		rotate_rigth(data, &moved);
	if (moved)
		redraw_scene(data, data->screen, data->input);
}

int	game_loop(t_mlx_vars *data)
{
	update_movement(data);
	return (0);
}
