#include "cub3d.h"

#include <X11/X.h>

#include "libft.h"
#include "mlx.h"

int	main(void)
{
	t_input	input;
 	t_mlx_vars	mlx;
  int			x;
	int			y;

	input.map = import_tmp_map("data/fakemap.cub");
	input.texture_n = "...";
	input.texture_s = "...";
	input.texture_e = "...";
	input.texture_o = "...";
	input.col_c = 0x00000000;
	input.col_f = 0x00000000;
	print_map(&input);
	free_map(input.map);
//========================	
	x = 1000;
	y = 1000;
	if (open_win(&mlx, x, y, "cub3d") != 0)
		return (1);
	mlx.img.img = mlx_new_image(mlx.mlx, x, y);
	mlx.img.addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bits_per_pixel,
			&mlx.img.line_length, &mlx.img.endian);
	// Inicializar valores de visión
	init_vision(&mlx.vision, x, y);
	// Dibujar toda la visión
	draw_full_vision(&mlx.img, &mlx.vision);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
	mlx_hook(mlx.win, KeyPress, KeyPressMask, handle_input, &mlx);
	mlx_hook(mlx.win, 17, 0L, close_mlx, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
