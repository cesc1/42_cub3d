#include "cub3d.h"

#include "libft.h"

int  check_args(int argc)
{
    if (argc != 2)
    {
        ft_printf("Error\n");
        ft_printf("Number of arguments must be 1, you introduced %d\n", argc - 1);
        return (ERR);
    }
    return (OK);
}

void init_input(t_input *input)
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