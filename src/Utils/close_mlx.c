
#include "cub3d.h"
#include "mlx.h"
#include <X11/X.h>
#include <stdlib.h>

// a lo mjor lo necesitamos para el mapa

/*static char	**free_dobe_char(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (0);
}*/
void	close_img(t_mlx_vars *data, t_img_data *img)
{
	mlx_destroy_image(data->mlx, img->img);
}

int	close_mlx(t_mlx_vars *vars)
{
	close_img(vars, &vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(1);
}
