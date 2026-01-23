#include "cub3d.h"
#include "libft.h"
#include <stdlib.h>

void	input_print(t_input *input)
{
	int	r;
	int	c;

	ft_printf("TEXTURES:\n");
	ft_printf("  - N: %s\n", input->texture_n);
	ft_printf("  - S: %s\n", input->texture_s);
	ft_printf("  - E: %s\n", input->texture_e);
	ft_printf("  - O: %s\n", input->texture_o);
	ft_printf("  - Floor: %d %d %d\n", (input->col_f >> 16) & 0xFF,
		(input->col_f >> 8) & 0xFF, (input->col_f) & 0xFF);
	ft_printf("  - Ceiling: %d %d %d\n\n", (input->col_c >> 16) & 0xFF,
		(input->col_c >> 8) & 0xFF, (input->col_c) & 0xFF);
	ft_printf("MAP:\n");
	ft_printf("  - Start: %c, (%d, %d)\n", input->start_dir, input->start_row,
		input->start_col);
	ft_printf("  - Dim: (%d, %d)\n", input->h, input->w);
	r = -1;
	while (++r < input->h)
	{
		c = -1;
		while (++c < input->w)
			ft_printf("%c ", input->map[r][c]);
		ft_printf("\n");
	}
}

int	check_args(int argc)
{
	if (argc != 2)
	{
		ft_printf("Error\n");
		ft_printf("Number of arguments must be 1, you introduced %d\n", argc
			- 1);
		return (ERR);
	}
	return (OK);
}

void	init_input(t_input *input)
{
	input->map = NULL;
	input->texture_n = NULL;
	input->texture_s = NULL;
	input->texture_e = NULL;
	input->texture_o = NULL;
	input->col_c = -1;
	input->col_f = -1;
	input->w = 0;
	input->h = 0;
	input->start_row = 0;
	input->start_col = 0;
	input->start_dir = '\0';
}

void	free_map(t_input *input)
{
	int	i;

	i = -1;
	if (!input->map)
		return ;
	while (++i < input->h)
	{
		if (input->map[i])
		{
			free(input->map[i]);
			input->map[i] = NULL;
		}
	}
	free(input->map);
	input->map = NULL;
}

void	free_input(t_input *input)
{
	free_map(input);
	if (input->texture_n)
		free(input->texture_n);
	if (input->texture_s)
		free(input->texture_s);
	if (input->texture_e)
		free(input->texture_e);
	if (input->texture_o)
		free(input->texture_o);
}
