#include "cub3d.h"
#include "mlx.h"
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
// comprobacion de abrir las imagenes // falta configurar

/*int	open_img(t_mlx_vars *data, t_img *img, char *str)
{
	img->img_ptr = mlx_xpm_file_to_image(data->mlx, str,
			&img->img_x, &img->img_y);
	if (img->img_ptr == NULL)
	{
		ft_printf("Error: No se pudo cargar la imagen %s\n", str);
		mlx_destroy_window (data->mlx, data->win);
		mlx_destroy_display (data->mlx);
		free (data->mlx);
		exit (1);
	}
}*/