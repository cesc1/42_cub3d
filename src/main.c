#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include <X11/X.h>

int	main(int argc, char **argv)
{
	t_input		input;
    /*
	t_mlx_vars	mlx;

	input.map = import_tmp_map("data/fakemapgp.cub");
	input.texture_n = "...";
	input.texture_s = "...";
	input.texture_e = "...";
	input.texture_o = "...";
	input.col_c = 0x00000000;
	input.col_f = 0x00000000;
	input.w = 24;
	input.h = 24;
	print_map(&input);
	mlx.input = input;
	mlx.screen[0] = 1080;
	mlx.screen[1] = 720;
	if (open_win(&mlx, mlx.screen[0], mlx.screen[1], "cub3d") != 0)
		return (1);
	mlx.img.img = mlx_new_image(mlx.mlx, mlx.screen[0], mlx.screen[1]);
	mlx.img.addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bits_per_pixel,
			&mlx.img.line_length, &mlx.img.endian);
	init_vision(&mlx.vision, input.map);
	draw_full_vision(&mlx.img, &mlx.vision, mlx.screen, input);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
	mlx_hook(mlx.win, KeyPress, KeyPressMask, handle_input, &mlx);
	mlx_hook(mlx.win, 17, 0L, close_mlx, &mlx);
	mlx_loop(mlx.mlx);
    */
    parser(argc, argv, &input);
	return (0);
}
