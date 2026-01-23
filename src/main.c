#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include <X11/X.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_input		input;
	t_mlx_vars	mlx;

	if (parser(argc, argv, &input) != OK)
		return (free_input(&input), 1);
	mlx.screen[0] = 1920;
	mlx.screen[1] = 1080;
	if (open_win(&mlx, mlx.screen[0], mlx.screen[1], "cub3d") != 0)
		return (free_input(&input), 1);
	init_mlx(&mlx, &input);
	draw_full_vision(&mlx, &mlx.vision, mlx.screen, input);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
	mlx_hook(mlx.win, KeyPress, KeyPressMask, key_press, &mlx);
	mlx_hook(mlx.win, KeyRelease, KeyReleaseMask, key_release, &mlx);
	mlx_hook(mlx.win, 17, 0L, close_mlx, &mlx);
	mlx_loop_hook(mlx.mlx, game_loop, &mlx);
	mlx_loop(mlx.mlx);
	free_input(&input);
	return (0);
}
