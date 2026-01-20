#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static int	parse_line(t_input *input, char *line, int line_num, int fd)
{
	if (line[0] == '\n')
		return (OK);
	if (ft_strncmp(line, "NO", 2) == 0)
		return (save_texture(line + 2, &(input->texture_n), line_num));
	if (ft_strncmp(line, "SO", 2) == 0)
		return (save_texture(line + 2, &(input->texture_s), line_num));
	if (ft_strncmp(line, "WE", 2) == 0)
		return (save_texture(line + 2, &(input->texture_o), line_num));
	if (ft_strncmp(line, "EA", 2) == 0)
		return (save_texture(line + 2, &(input->texture_e), line_num));
	if (ft_strncmp(line, "F", 1) == 0)
		return (save_color(line + 1, &(input->col_f), line_num));
	if (ft_strncmp(line, "C", 1) == 0)
		return (save_color(line + 1, &(input->col_c), line_num));
	if (ft_strchr(" 1", line[0]))
		return (create_map(input, line, fd));
	return (ft_printf("Error\n.cub: Wrong line (l%d)\n", line_num), ERR);
}

static int	parse_cub(t_input *input, int fd_cub)
{
	char	*line;
	int		line_count;
	int		res_parse_line;

	line_count = 0;
	line = get_next_line(fd_cub);
	while (line)
	{
		line_count++;
		res_parse_line = parse_line(input, line, line_count, fd_cub);
		free(line);
		if (res_parse_line != OK || input->map != NULL)
			return (res_parse_line);
		line = get_next_line(fd_cub);
	}
	return (OK);
}

int	parser(int argc, char **argv, t_input *input)
{
	int	fd_cub;
	int	res_parse_cub;

	init_input(input);
	if (check_args(argc) != OK)
		return (ERR);
	fd_cub = open(argv[1], O_RDONLY);
	if (fd_cub == -1)
		return (print_error(ERR_OPEN), ERR);
	res_parse_cub = parse_cub(input, fd_cub);
	close(fd_cub);
	return (res_parse_cub);
}
