#ifndef CUB3D_H
# define CUB3D_H

# include "stddef.h"

// Enum types

typedef enum e_return_status
{
	OK,
	ERR_MALLOC,
	ERR_OPEN,
	ERR_PARSER
}	t_return_status;

// Struct types

typedef struct s_input
{
	char			**map;
	char			*texture_n;
	char			*texture_s;
	char			*texture_e;
	char			*texture_o;
	unsigned int	col_c;
	unsigned int	col_f;
}	t_input;

// Functions import
char	**import_tmp_map(const char *path);
void	print_map(const t_input *input);
void	free_map(char **map);
int		is_char_map(const char c);
int		is_line_map(const char *line);

// Functions error
void	print_error(t_return_status type);

#endif
