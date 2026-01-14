// Header
#include "cub3d.h"

#include "libft.h"

int	is_char_map(const char c)
{
	if (c == '0' || \
		c == '1' || \
		c == 'N' || \
		c == 'S' || \
		c == 'E' || \
		c == 'W')
	{
		return (1);
	}
	return (0);
}

int	is_line_map(const char *line)
{
	while (*line)
	{
		if (is_char_map(*line))
			return (1);
		line++;
	}
	return (0);
}

void	print_map(const t_input *input)
{
	char	**map;
	int		i;

	map = input->map;
	if (!map)
		return ;
	i = -1;
	while (map[++i])
		ft_printf("%s\n", map[i]);
}
