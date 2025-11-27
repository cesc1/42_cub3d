#include "cub3d.h"

int	main(void)
{
	t_input	input;

	input.map = import_tmp_map("data/fakemap.cub");
	input.texture_n = "...";
	input.texture_s = "...";
	input.texture_e = "...";
	input.texture_o = "...";
	input.col_c = 0x00000000;
	input.col_f = 0x00000000;
	print_map(&input);
	free_map(input.map);
	return (0);
}
