#ifndef CUB3D_H
# define CUB3D_H

# include "stddef.h"
# include <sys/types.h>

// Defines
# define FILE_DATA_CAP_INIT 16

// Enum types
typedef enum e_return_status
{
	OK,
	ERR,
	ERR_MALLOC,
	ERR_OPEN
}					t_return_status;

// Estructura para inputs
typedef struct s_input
{
	char			**map;
	char			*texture_n;
	char			*texture_s;
	char			*texture_e;
	char			*texture_o;
	ssize_t			col_c;
	ssize_t			col_f;
	int				w;
	int				h;
	int				start_row;
	int				start_col;
	char			start_dir;
}					t_input;

// Estructura para file_reader
typedef struct s_file_data
{
	char			**data;
	size_t			size;
	size_t			capacity;
	size_t			max_width;
}					t_file_data;

// Img_data // estructruara para acelerar la impresion de pixeles
typedef struct s_img_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img_data;

typedef struct s_texture
{
	void			*img;
	char			*addr;
	int				width;
	int				height;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_texture;

typedef struct s_textures
{
	t_texture		north;
	t_texture		south;
	t_texture		east;
	t_texture		west;
}					t_textures;

typedef struct s_vision
{
	double			pos[2];
	double			dir[2];
	double			plane[2];
	double			rayDir[2];
	double			sideDist[2];
	double			deltaDist[2];
	double			perpWallDist;
	double			camera;
	int				step[2];
	int				map[2];
	int				draw[2];
	int				side;
	int				lineHeight;
}					t_vision;

// Input_state // estructura para un moviminto mas fino
typedef struct s_input_state
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				left;
	int				right;
	int				escape;
}					t_input_state;

// Mlx_vars // estructrura necesaria para el correcto funcionamiento de hook
typedef struct s_mlx_vars
{
	void			*mlx;
	void			*win;
	int				screen[2];
	t_img_data		img;
	t_vision		vision;
	t_input			input;
	t_input_state	input_state;
	t_textures		textures;
}					t_mlx_vars;

// Functions import
int					check_args(int argc);
void				init_input(t_input *input);
void				free_input(t_input *input);
int					parser(int argc, char **argv, t_input *input);
int					save_texture(char *line, char **ptr_save, int line_num);
int					save_color(char *line, ssize_t *ptr_save, int line_num);
int					create_map(t_input *input, char *line, int fd);
void				input_print(t_input *input);
int					file_data_init(t_file_data *file);
int					file_data_push(t_file_data *file, char *line);
void				file_data_free(t_file_data *file);

// Functions error
void				print_error(t_return_status type);

// Funcions TRGB // Utils/trgb.c
int					create_trgb(int t, int r, int g, int b);
int					get_t(int trgb);
int					get_r(int trgb);
int					get_g(int trgb);
int					get_b(int trgb);

// temp Funcion to test // Utils/draw.c

void				clear_image(t_img_data *data, int width, int height,
						int color);
void				draw_full_vision(t_mlx_vars *data, t_vision *vision,
						int *screen, t_input imput);
void				init_vision(t_vision *vision, t_input *input);
void				open_img(t_mlx_vars *data, t_texture *img, char *str);

// Funcion i crete to render mlx // Utils/my_mlx_func.c
void				my_mlx_pixel_put(t_img_data *data, int x, int y, int color);

// Funcion close_win // Utils/close_mlx.c
int					close_mlx(t_mlx_vars *vars);

// Funcion open_win // Utils/open.mlx.c
int					open_win(t_mlx_vars *data, int x, int y, char *name);

// Funcions to handle continuous input // Logic/handle_input.c
int					key_press(int keysym, t_mlx_vars *data);
int					key_release(int keysym, t_mlx_vars *data);
int					game_loop(t_mlx_vars *data);
void				update_movement(t_mlx_vars *data);

#endif
