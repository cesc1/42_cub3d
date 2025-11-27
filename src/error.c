#include "cub3d.h"

#include <stdio.h>

#include "libft.h"

void	print_error(t_return_status r)
{
	if (r == ERR_MALLOC || \
		r == ERR_OPEN)
	{
		perror("Error\n");
	}
}
