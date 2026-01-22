#include "cub3d.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

// comprobacion de que mlx abre la ventana

int	open_win(t_mlx_vars *data, int x, int y, char *name)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (1);
	data->win = mlx_new_window(data->mlx, x, y, name);
	if (data->win == NULL)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		return (1);
	}
	return (0);
}

void	open_img(t_mlx_vars *data, t_texture *img, char *str)
{
	img->img = mlx_xpm_file_to_image(data->mlx, str, &img->width, &img->height);
	if (img->img == NULL)
	{
		printf("Advertencia: No se pudo cargar la imagen %s\n", str);
		printf("Se usará color por defecto\n");
		img->addr = NULL;
		img->width = 0;
		img->height = 0;
		return ;
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}
