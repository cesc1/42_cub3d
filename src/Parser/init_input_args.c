#include "cub3d.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	input_print(t_input *input)
{
	int	r;
	int	c;

	printf("TEXTURES:\n");
	printf("  - N: %s\n", input->texture_n);
	printf("  - S: %s\n", input->texture_s);
	printf("  - E: %s\n", input->texture_e);
	printf("  - O: %s\n", input->texture_o);
	printf("  - Floor: %ld %ld %ld\n", (input->col_f >> 16) & 0xFF,
		(input->col_f >> 8) & 0xFF, (input->col_f) & 0xFF);
	printf("  - Ceiling: %ld %ld %ld\n\n", (input->col_c >> 16) & 0xFF,
		(input->col_c >> 8) & 0xFF, (input->col_c) & 0xFF);
	printf("MAP:\n");
	printf("  - Start: %c, (%d, %d)\n", input->start_dir, input->start_row,
		input->start_col);
	printf("  - Dim: (%d, %d)\n", input->h, input->w);
	r = -1;
	while (++r < input->h)
	{
		c = -1;
		while (++c < input->w)
			printf("%c ", input->map[r][c]);
		printf("\n");
	}
}

int	check_args(int argc)
{
	if (argc != 2)
	{
		printf("Error\n");
		printf("Number of arguments must be 1, you introduced %d\n", argc
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
