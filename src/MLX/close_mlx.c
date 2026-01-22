#include "cub3d.h"
#include "mlx.h"
#include <X11/X.h>
#include <stdlib.h>

void	close_img(t_mlx_vars *data, t_img_data *img)
{
	mlx_destroy_image(data->mlx, img->img);
}

void	close_textures(t_mlx_vars *data, t_textures *tex)
{
	if (tex->east.img && tex->east.addr)
	{
		mlx_destroy_image(data->mlx, tex->east.img);
		tex->east.img = NULL;
		tex->east.addr = NULL;
	}
	if (tex->north.img && tex->north.addr)
	{
		mlx_destroy_image(data->mlx, tex->north.img);
		tex->north.img = NULL;
		tex->north.addr = NULL;
	}
	if (tex->south.img && tex->south.addr)
	{
		mlx_destroy_image(data->mlx, tex->south.img);
		tex->south.img = NULL;
		tex->south.addr = NULL;
	}
	if (tex->west.img && tex->west.addr)
	{
		mlx_destroy_image(data->mlx, tex->west.img);
		tex->west.img = NULL;
		tex->west.addr = NULL;
	}
}

int	close_mlx(t_mlx_vars *vars)
{
	free_input(&vars->input);
	close_img(vars, &vars->img);
	close_textures(vars, &vars->textures);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(1);
}
