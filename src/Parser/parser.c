#include "cub3d.h"

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft.h"

static int  check_args(int argc)
{
    if (argc != 2)
    {
        ft_printf("Error\n");
        ft_printf("Number of arguments must be 1, you introduced %d\n", argc - 1);
        return (ERR);
    }
    return (OK);
}

static void init_input(t_input *input)
{
    input->map = NULL;
    input->texture_n = NULL;
    input->texture_s = NULL;
    input->texture_e = NULL;
    input->texture_o = NULL;
    input->col_c = -1;
    input->col_f = -1;
    input->w = 0;
    input->h = 0;
    input->start_x = 0;
    input->start_y = 0;
    input->start_dir = '\0';
}

void	free_split(char **split)
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

static int str_isdigit_valid(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (ERR);
        i++;
    }
    i = ft_atoi(str);
    if (i < 0 || i > 255)
        return (ERR);
    return (OK);
}

static int  col_str_to_ssize(char *str, ssize_t *ptr_save, int line_num)
{
    int i;
    char    **arr;
    
    arr = ft_split(str, ',');
    if (!arr)
        return (ft_printf("Error\n.cub: Malloc (l%d)\n", line_num), ERR_MALLOC);
    i = 0;
    *ptr_save = 0;
    while (arr[i] && i < 4)
    {
        if (str_isdigit_valid(arr[i]) != OK)
            return (ft_printf("Error\n.cub: Wrong color params (l%d)\n", line_num), \
                free_split(arr), ERR);
        *ptr_save = (*ptr_save << 8) | ft_atoi(arr[i]);
    }
    if (i != 3)
        return (ft_printf("Error\n.cub: Wrong color params (l%d)\n", line_num), \
            free_split(arr), ERR);
    return (OK);
}

static int  save_color(char *line, ssize_t *ptr_save, int line_num)
{
    int n;
    char    *clean_line;

    if (*ptr_save != -1)
        return (ft_printf("Error\n.cub: Color dup (l%d)\n", line_num), ERR);
    n = ft_strlen(line);
    if (line[n - 1] == '\n')
        line[n - 1] = '\0';
    clean_line = ft_strtrim(line, " ");
    if (!clean_line)
        return (ft_printf("Error\n.cub: Malloc (l%d)\n", line_num), ERR_MALLOC);
    if (ft_strlen(clean_line) == 0)
        return (ft_printf("Error\n.cub: Color empty (l%d)\n", line_num), ERR);
    return (col_str_to_ssize(clean_line, ptr_save, line_num));
}

static int  save_texture(char *line, char **ptr_save, int line_num)
{
    int n;
    int fd;

    if (*ptr_save != NULL)
        return (ft_printf("Error\n.cub: Texture dup (l%d)\n", line_num), ERR);
    n = ft_strlen(line);
    if (line[n - 1] == '\n')
        line[n - 1] = '\0';
    *ptr_save = ft_strtrim(line, " ");
    if (!(*ptr_save))
        return (ft_printf("Error\n.cub: Malloc (l%d)\n"), ERR_MALLOC);
    if (ft_strlen(*ptr_save) == 0)
        return (ft_printf("Error\n.cub: Texture empty (l%d)\n"), ERR);
    fd = open(*ptr_save, O_RDONLY);
    if (fd == -1)
        return (print_error(ERR_OPEN), ERR);
    close(fd);
    return (OK);
}

static int parse_line(t_input *input, char *line, int line_num)
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
        {/* Parse map */}
    return (ft_printf("Error\n.cub: Wrong line (l%d)\n", line_num), ERR);
}

static int parse_cub(t_input *input, int fd_cub)
{
    char    *line;
    int     line_count;
    int     res_parse_line;

    line_count = 0;
    line = get_next_line(fd_cub);
    while (line)
    {
        line_count++;
        res_parse_line = parse_line(input, line, line_count);
        free(line);
        if (res_parse_line != OK)
            return (res_parse_line);
        // How to detect that we processed the map? add flag 
        // to e_return _status?
        // Or process map giving line by line through here?
        line = get_next_line(fd_cub);
    }
    return (OK);
}

int parser(int argc, char **argv, t_input *input)
{
    int fd_cub;
    int res_parse_cub;

    if (check_args(argc) != OK)
        return (ERR);
    init_input(input);
    fd_cub = open(argv[1], O_RDONLY);
    if (fd_cub == -1)
        return (print_error(ERR_OPEN), ERR);
    res_parse_cub = parse_cub(input, fd_cub);
    close(fd_cub);
    return (res_parse_cub);
}
