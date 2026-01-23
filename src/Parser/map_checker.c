#include "cub3d.h"
#include "libft.h"

static int	process_position(char pos, int *status)
{
	if (pos == ' ')
		return (1);
	if (pos == '1' || pos == 'X')
		return (0);
	ft_printf("Error\n.cub: The map is incorrect (flood fill)\n");
	*status = ERR;
	return (0);
}

static void	recursive_fill(t_input *input, int h, int w, int *status)
{
	if (*status == ERR)
		return ;
	input->map[h][w] = 'X';
	if (h > 0)
		if (process_position(input->map[h - 1][w], status) == 1)
			recursive_fill(input, h - 1, w, status);
	if (h < input->h - 1)
		if (process_position(input->map[h + 1][w], status) == 1)
			recursive_fill(input, h + 1, w, status);
	if (w > 0)
		if (process_position(input->map[h][w - 1], status) == 1)
			recursive_fill(input, h, w - 1, status);
	if (w < input->w - 1)
		if (process_position(input->map[h][w + 1], status) == 1)
			recursive_fill(input, h, w + 1, status);
	return ;
}

static void	fill_borders(t_input *input)
{
	int	hor;
	int	ver;

	hor = -1;
	while (++hor < input->w)
	{
		input->map[0][hor] = ' ';
		input->map[input->h - 1][hor] = ' ';
	}
	ver = -1;
	while (++ver < input->h)
	{
		input->map[ver][0] = ' ';
		input->map[ver][input->w - 1] = ' ';
	}
}

static int	dup_pad_map(t_input *input, t_input *input_dup)
{
	int	i;
	int	j;

	input_dup->h = input->h + 2;
	input_dup->w = input->w + 2;
	if (save_memory_map(input_dup) != OK)
		return (ft_printf("Error\n.cub: Malloc error\n"), ERR_MALLOC);
	i = -1;
	while (++i < input->h)
	{
		j = -1;
		while (++j < input->w)
			input_dup->map[i + 1][j + 1] = input->map[i][j];
	}
	fill_borders(input_dup);
	return (OK);
}

int	flood_fill(t_input *input)
{
	t_input	input_dup;
	int		status;

	init_input(&input_dup);
	if (dup_pad_map(input, &input_dup) != OK)
		return (ERR_MALLOC);
	status = OK;
	recursive_fill(&input_dup, 0, 0, &status);
	if (status != OK || check_space(&input_dup) != OK)
		return (free_input(&input_dup), ERR);
	free_input(&input_dup);
	return (OK);
}
