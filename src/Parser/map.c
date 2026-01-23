#include "cub3d.h"
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>

static int	copy_map(t_file_data *raw_map, t_input *input)
{
	int	c;
	int	r;
	int	flag_endl;

	r = -1;
	while (++r < input->h)
	{
		c = -1;
		flag_endl = 0;
		while (++c < input->w)
		{
			if (!flag_endl && \
				(!raw_map->data[r][c] || raw_map->data[r][c] == '\n'))
				flag_endl = 1;
			if (flag_endl)
				input->map[r][c] = ' ';
			else
			{
				input->map[r][c] = raw_map->data[r][c];
				if (check_start_pos(input, r, c) != OK)
					return (ERR);
			}
		}
	}
	return (OK);
}

int	save_memory_map(t_input *input)
{
	int	i;

	input->map = ft_calloc(input->h, sizeof(char *));
	if (!input->map)
		return (printf("Error\n.cub: Malloc error\n"), ERR_MALLOC);
	i = -1;
	while (++i < input->h)
	{
		input->map[i] = ft_calloc(input->w, sizeof(char));
		if (!input->map[i])
		{
			free_map(input);
			return (printf("Error\n.cub: Malloc error\n"), ERR_MALLOC);
		}
	}
	return (OK);
}

static int	read_raw_map(t_file_data *raw_map, char *line, int fd)
{
	int	flag_eof;

	if (file_data_init(raw_map) != OK)
		return (ERR_MALLOC);
	flag_eof = 0;
	line = ft_strdup(line);
	if (!line)
		return (printf("Error\n.cub: Malloc error\n"), ERR_MALLOC);
	while (line)
	{
		if (map_process_line(raw_map, line, &flag_eof) != OK)
			return (ERR);
		line = get_next_line(fd);
	}
	return (OK);
}

int	create_map(t_input *input, char *line, int fd)
{
	t_file_data	raw_map;

	if (read_raw_map(&raw_map, line, fd) != OK)
		return (file_data_free(&raw_map), ERR);
	input->h = raw_map.size;
	input->w = raw_map.max_width;
	if (save_memory_map(input) != OK || copy_map(&raw_map, input) != OK)
	{
		free_input(input);
		file_data_free(&raw_map);
		return (ERR);
	}
	file_data_free(&raw_map);
	return (OK);
}
