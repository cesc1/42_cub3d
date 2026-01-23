#include <stdlib.h>

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = -1;
	while (split[++i])
	{
		free(split[i]);
		split[i] = NULL;
	}
	free(split);
}
