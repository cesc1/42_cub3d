#include "cub3d.h"
#include "libft.h"
#include <stdlib.h>

void	file_data_free(t_file_data *file)
{
	int	i;

	i = -1;
	if (!file->data)
		return ;
	while (++i < (int)file->capacity)
	{
		if (file->data[i])
		{
			free(file->data[i]);
			file->data[i] = NULL;
		}
	}
	free(file->data);
	file->data = NULL;
}

int	file_data_init(t_file_data *file)
{
	file->size = 0;
	file->max_width = 0;
	file->capacity = FILE_DATA_CAP_INIT;
	file->data = ft_calloc(file->capacity, sizeof(char *));
	if (!file->data)
		return (ft_printf("Error\n.cub: Malloc fail parsing map\n"),
			ERR_MALLOC);
	return (OK);
}

int	file_data_push(t_file_data *file, char *line)
{
	char	**new_data;
	int		i;

	if (file->size == file->capacity)
	{
		file->capacity *= 2;
		new_data = ft_calloc(file->capacity, sizeof(char *));
		if (!new_data)
			return (ft_printf("Error\n.cub: Malloc fail parsing map\n"),
				ERR_MALLOC);
		i = -1;
		while (++i < (int)file->size)
			new_data[i] = file->data[i];
		free(file->data);
		file->data = new_data;
	}
	file->data[file->size++] = line;
	return (OK);
}
