#include "cub3d.h"

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft.h"

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
    i = -1;
    *ptr_save = 0;
    while (arr[++i] && i < 4)
    {
        if (str_isdigit_valid(arr[i]) != OK)
            return (ft_printf("Error\n.cub: Wrong color params (l%d)\n", line_num), \
                ft_free_split(arr), ERR);
        *ptr_save = (*ptr_save << 8) | ft_atoi(arr[i]);
    }
    if (i != 3)
        return (ft_printf("Error\n.cub: Wrong color params (l%d)\n", line_num), \
            ft_free_split(arr), ERR);
    ft_free_split(arr);
    return (OK);
}


static char    *line_cleaner(char *line, int line_num)
{
    int     n;
    char    *result;

    n = ft_strlen(line);
    if (line[n - 1] == '\n')
        line[n - 1] = '\0';
    result = ft_strtrim(line, " ");
    if (!result)
        return (ft_printf("Error\n.cub: Malloc (l%d)\n", line_num), NULL);
    if (ft_strlen(result) == 0)
        return (ft_printf("Error\n.cub: Texture/color empty (l%d)\n", line_num), NULL);
    return (result);
}

int  save_color(char *line, ssize_t *ptr_save, int line_num)
{
    int     r;
    char    *clean_line;

    if (*ptr_save != -1)
        return (ft_printf("Error\n.cub: Color dup (l%d)\n", line_num), ERR);
    clean_line = line_cleaner(line, line_num);
    if (!clean_line)
        return (ERR);
    r = col_str_to_ssize(clean_line, ptr_save, line_num);
    free(clean_line);
    return (r);
}

int  save_texture(char *line, char **ptr_save, int line_num)
{
    int fd;

    if (*ptr_save != NULL)
        return (ft_printf("Error\n.cub: Texture dup (l%d)\n", line_num), ERR);
    *ptr_save = line_cleaner(line, line_num);
    if (!(*ptr_save))
        return (ERR);
    fd = open(*ptr_save, O_RDONLY);
    if (fd == -1)
        return (print_error(ERR_OPEN), ERR);
    close(fd);
    return (OK);
}
