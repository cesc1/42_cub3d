#include "cub3d.h"
#include "mlx.h"
#include <X11/keysym.h>
#include <math.h>

void	move_up(t_mlx_vars *data)
{
	data->vision.pos[1] -= 1.0;
	draw_full_vision(&data->img, &data->vision);
	printf("me muevo hacia ariba\n");
}
void	move_down(t_mlx_vars *data)
{
	data->vision.pos[1] += 1.0;
	draw_full_vision(&data->img, &data->vision);
	printf("me muevo hacia abajo\n");
}

void	move_right(t_mlx_vars *data)
{
	data->vision.pos[0] += 1.0;
	draw_full_vision(&data->img, &data->vision);
	printf("me muevo hacia la derecha\n");
}

void	move_left(t_mlx_vars *data)
{
	data->vision.pos[0] -= 1.0;
	draw_full_vision(&data->img, &data->vision);
	printf("me muevo hacia la hizquierda\n");
}

void	move_right_cam(t_mlx_vars *data)
{
	data->vision.ang += 0.01;
	data->vision.v_vis[0] = cos(data->vision.ang) - sin(data->vision.ang);
	data->vision.v_vis[1] = sin(data->vision.ang) + cos(data->vision.ang);
	data->vision.v_per[0] = -data->vision.v_vis[1];
	data->vision.v_per[1] = data->vision.v_vis[0];
	draw_full_vision(&data->img, &data->vision);
	printf("muevo la camara hacia la derecha %f\n", data->vision.ang);
}

void	move_letf_cam(t_mlx_vars *data)
{
	data->vision.ang -= 0.01;
	data->vision.v_vis[0] = cos(data->vision.ang) - sin(data->vision.ang);
	data->vision.v_vis[1] = sin(data->vision.ang) + cos(data->vision.ang);
	data->vision.v_per[0] = -data->vision.v_vis[1];
	data->vision.v_per[1] = data->vision.v_vis[0];
	draw_full_vision(&data->img, &data->vision);
	printf("muevo la camra hacia la hizquierda %f\n", data->vision.ang);
}

int	handle_input(int keysym, t_mlx_vars *data)
{
	if (keysym == XK_Escape)
		return (close_mlx(data));
	else if (keysym == XK_w)
		move_up(data);
	else if (keysym == XK_d)
		move_right(data);
	else if (keysym == XK_s)
		move_down(data);
	else if (keysym == XK_a)
		move_left(data);
	else if (keysym == XK_Left)
		move_letf_cam(data);
	else if (keysym == XK_Right)
		move_right_cam(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}