#include "cub3d.h"

#include <stdlib.h>

#include <libft.h>

static int  check_start_pos(t_input *input, int r, int c)
{
    if (!ft_strchr("NSEW", input->map[r][c]))
        return (OK);
    if (input->start_dir)
        return (ft_printf("Error\n.cub: Map double start position\n"), ERR);
    input->start_dir = input->map[r][c];
    input->start_row = r;
    input->start_col = c;
    return (OK);
}

static int  copy_map(t_file_data *raw_map, t_input *input)
{
    int c;
    int r;
    int flag_endl;

    r = -1;
    while (++r < input->h)
    {
        c = -1;
        flag_endl = 0;
        while (++c < input->w)
        {
            if (!flag_endl && (!raw_map->data[r][c] || raw_map->data[r][c] == '\n'))
                flag_endl = 1;
            if (flag_endl)
                input->map[r][c] = ' ';
            else
            {
                input->map[r][c] = raw_map->data[r][c];
                if (check_start_pos(input, r, c) != OK)
                    return (ERR);
            }
        }
    }
    return (OK);
}

static int  save_memory_map(t_input *input)
{
    int i;

    input->map = ft_calloc(input->h, sizeof (char *));
    if (!input->map)
        return (ft_printf("Error\n.cub: Malloc error\n"), ERR_MALLOC);

    i = -1;
    while (++i < input->h)
    {
        input->map[i] = ft_calloc(input->w, sizeof (char));
        if (!input->map[i])
            return (ft_printf("Error\n.cub: Malloc error\n"), ERR_MALLOC);
    }
    return (OK);
}

static int  check_line(t_file_data *raw_map, char *line)
{
    int i;

    i = -1;
    while (line[++i] && line[i] != '\n')
    {
        if (!ft_strchr(" 01NSEW", line[i]))
            return (ERR);    
    }
    while (i > 0 && line[i - 1] == ' ')
        i--;
    if (i > (int)raw_map->max_width)
        raw_map->max_width = i;
    return (OK);
}

static int read_raw_map(t_file_data *raw_map, char *line, int fd)
{
    int flag_eof;

    if (file_data_init(raw_map) != OK)
        return (ERR_MALLOC);
    flag_eof = 0;
    line = ft_strdup(line);
    if (!line)
        return (ft_printf("Error\n.cub: Malloc error\n"), ERR_MALLOC);
    while (line)
    {
        if (line[0] == '\n')
            flag_eof = 1;
        else
        {
            if (flag_eof == 1 || \
                file_data_push(raw_map, line) != OK || \
                check_line(raw_map, line) != OK)
            {
                file_data_free(raw_map);
                return (ft_printf("Error\n.cub: Map error (map l%d)\n", raw_map->size), ERR);
            }
        }
        line = get_next_line(fd);
    }
    return (OK);
}

int create_map(t_input *input, char *line, int fd)
{
    t_file_data raw_map;

    if (read_raw_map(&raw_map, line, fd) != OK)
        return (ERR);
    input->h = raw_map.size;
    input->w = raw_map.max_width;
    if (save_memory_map(input) != OK || \
        copy_map(&raw_map, input) != OK)
    {
        free_input(input);
        file_data_free(&raw_map);
        return (ERR);
    }
    file_data_free(&raw_map);
    return (OK);
}