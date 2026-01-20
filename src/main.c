#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include <X11/X.h>

int	main(void)
{
	t_input		input;
	t_mlx_vars	mlx;
	int			i;

	i = 0;
	input.map = import_tmp_map("data/fakemapgp.cub");
	input.texture_n = "data/textures/Walltest1.xpm";
	input.texture_s = "data/textures/Walltest2.xpm";
	input.texture_e = "data/textures/Walltest3.xpm";
	input.texture_o = "data/textures/Walltest4.xpm";
	input.col_c = 0x0000FFFF;
	input.col_f = 0x00FFFFFF;
	input.w = 60;
	input.h = 60;
	print_map(&input);
	mlx.input = input;
	mlx.screen[0] = 1920;
	mlx.screen[1] = 1080;
	if (open_win(&mlx, mlx.screen[0], mlx.screen[1], "cub3d") != 0)
		return (1);
	mlx.img.img = mlx_new_image(mlx.mlx, mlx.screen[0], mlx.screen[1]);
	mlx.img.addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bits_per_pixel,
			&mlx.img.line_length, &mlx.img.endian);
	open_img(&mlx, &mlx.textures.north, input.texture_n);
	open_img(&mlx, &mlx.textures.south, input.texture_s);
	open_img(&mlx, &mlx.textures.east, input.texture_e);
	open_img(&mlx, &mlx.textures.west, input.texture_o);
	mlx.input_state.w = 0;
	mlx.input_state.a = 0;
	mlx.input_state.s = 0;
	mlx.input_state.d = 0;
	mlx.input_state.left = 0;
	mlx.input_state.right = 0;
	mlx.input_state.escape = 0;
	init_vision(&mlx.vision, input.map);
	draw_full_vision(&mlx, &mlx.vision, mlx.screen, input);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
	mlx_hook(mlx.win, KeyPress, KeyPressMask, key_press, &mlx);
	mlx_hook(mlx.win, KeyRelease, KeyReleaseMask, key_release, &mlx);
	mlx_hook(mlx.win, 17, 0L, close_mlx, &mlx);
	mlx_loop_hook(mlx.mlx, game_loop, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
