#include "cub3d.h"

#include "libft.h"

int	check_space(t_input *input_dup)
{
	int	w;
	int	h;

	h = -1;
	while (++h < input_dup->h)
	{
		w = -1;
		while (++w < input_dup->w)
		{
			if (input_dup->map[h][w] == ' ')
			{
				ft_printf("Error\n.cub: The map is incorrect (flood fill)\n");
				return (ERR);
			}
		}
	}
	return (OK);
}
