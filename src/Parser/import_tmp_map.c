#include "cub3d.h"

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = -1;
	while (map[++i])
	{
		free(map[i]);
		map[i] = NULL;
	}
	free(map);
}

static int	count_map_lines(const char *path)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_error(ERR_OPEN), -1);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (is_line_map(line))
			count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

static void	load_map(char **map, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (is_line_map(line))
		{
			*map = line;
			line = ft_strrchr(line, '\n');
			if (line)
				*line = '\0';
			map++;
		}
		else
			free(line);
		line = get_next_line(fd);
	}
}

char	**import_tmp_map(const char *path)
{
	int		n;
	int		fd;
	char	**map;

	n = count_map_lines(path);
	if (n == -1)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_error(ERR_OPEN), NULL);
	map = (char **)ft_calloc(n + 1, sizeof (char *));
	if (!map)
		return (print_error(ERR_MALLOC), NULL);
	load_map(map, fd);
	return (map);
}
