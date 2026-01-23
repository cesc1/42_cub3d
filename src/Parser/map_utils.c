#include "cub3d.h"
#include "libft.h"
#include <stdlib.h>

int	check_start_pos(t_input *input, int r, int c)
{
	if (!ft_strchr("NSEW", input->map[r][c]))
		return (OK);
	if (input->start_dir)
		return (ft_printf("Error\n.cub: Map double start position\n"), ERR);
	input->start_dir = input->map[r][c];
	input->start_row = r;
	input->start_col = c;
	return (OK);
}

static int	check_line(t_file_data *raw_map, char *line)
{
	int	i;

	i = -1;
	while (line[++i] && line[i] != '\n')
	{
		if (!ft_strchr(" 01NSEW", line[i]))
			return (ERR);
	}
	while (i > 0 && line[i - 1] == ' ')
		i--;
	if (i > (int)raw_map->max_width)
		raw_map->max_width = i;
	return (OK);
}

int	map_process_line(t_file_data *raw_map, char *line, int *flag_eof)
{
	if (line[0] == '\n')
	{
		*flag_eof = 1;
		return (free(line), OK);
	}
	else
	{
		if (*flag_eof == 1)
			return (free(line), ft_printf("Error\n.cub: Map\n"), ERR);
		if (file_data_push(raw_map, line) != OK || check_line(raw_map,
				line) != OK)
		{
			file_data_free(raw_map);
			ft_printf("Error\n.cub: Map");
			return (ERR);
		}
	}
	return (OK);
}
