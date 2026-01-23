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

// Estructura para guardar lineas de un fichero
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
	double			ray_dir[2];
	double			side_dist[2];
	double			delta_dist[2];
	double			perp_wall_dist;
	double			camera;
	int				step[2];
	int				map[2];
	int				draw[2];
	int				side;
	int				line_height;
}					t_vision;

typedef struct s_texture_render
{
	double			wall[2];
	int				tex[2];
	double			step;
	double			tex_pos;
	int				color;
}					t_texture_render;

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
void				free_map(t_input *input);
void				free_input(t_input *input);
int					parser(int argc, char **argv, t_input *input);
int					save_memory_map(t_input *input);
int					save_texture(char *line, char **ptr_save, int line_num);
int					save_color(char *line, ssize_t *ptr_save, int line_num);
int					create_map(t_input *input, char *line, int fd);
int					flood_fill(t_input *input);
void				input_print(t_input *input);
int					file_data_init(t_file_data *file);
int					file_data_push(t_file_data *file, char *line);
void				file_data_free(t_file_data *file);
int					check_space(t_input *input_dup);
int					check_start_pos(t_input *input, int r, int c);
int					map_process_line(t_file_data *raw_map, char *line, \
	int *flag_eof);

// Functions error
void				print_error(t_return_status type);

// Functions TRGB // Graphics/trgb.c
int					create_trgb(int t, int r, int g, int b);
int					get_t(int trgb);
int					get_r(int trgb);
int					get_g(int trgb);
int					get_b(int trgb);

// Graphics/rendering.c
void				draw_back(t_img_data *img, int sx, int sy, t_input imp);
void				draw_ver_line(t_img_data *img, int x, int *draw, int color);
void				draw_textured_line(t_mlx_vars *data, int x, t_vision *v);
void				draw_single_ray(t_mlx_vars *data, t_vision *v, int x);
void				draw_full_vision(t_mlx_vars *data, t_vision *vision,
						int *screen, t_input imput);

// Graphics/raycasting.c
void				init_ray_direction(t_vision *v, int x, int *screen_width);
void				init_step_and_side_dist(t_vision *v);
void				init_ray_params(t_vision *v, int x, int *screen_width);
int					check_boundaries(t_vision *v, t_input *imp);
int					perform_dda(t_vision *v, t_input *imp);
void				calculate_wall_params(t_vision *v, int *screen);
int					get_wall_color(t_vision *v);

// Graphics/texture_utils.c
t_texture			*get_wall_texture(t_textures *textures, t_vision *v);
int					get_texture_pixel(t_texture *tex, int x, int y);
int					textures_are_loaded(t_textures *tex);

// Graphics/ray_utils.c
double				get_delta_dist(double ray);
void				clear_image(t_img_data *data, int width, int height,
						int color);

// Core/init.c
void				init_vision(t_vision *vision, t_input *input);
void				open_img(t_mlx_vars *data, t_texture *img, char *str);
void				init_texture_params(t_texture_render *tex_vars,
						t_texture *texture, t_vision *v, t_mlx_vars *data);

// MLX/my_mlx_func.c
void				my_mlx_pixel_put(t_img_data *data, int x, int y, int color);

// MLX/close_mlx.c
int					close_mlx(t_mlx_vars *vars);

// MLX/open_mlx.c
int					open_win(t_mlx_vars *data, int x, int y, char *name);

// Logic/input_events.c
int					key_press(int keysym, t_mlx_vars *data);
int					key_release(int keysym, t_mlx_vars *data);
int					game_loop(t_mlx_vars *data);
void				update_movement(t_mlx_vars *data);
void				redraw_scene(t_mlx_vars *data, int *screen, t_input input);

// Functions for movement // Logic/movement.c
void				move_forward(t_mlx_vars *data, t_input input, int *moved);
void				move_backward(t_mlx_vars *data, t_input input, int *moved);
void				move_left(t_mlx_vars *data, t_input input, int *moved);
void				move_right(t_mlx_vars *data, t_input input, int *moved);

// Functions for rotation // Logic/rotation.c
void				rotate_left(t_mlx_vars *data, int *moved);
void				rotate_right(t_mlx_vars *data, int *moved);

// Core/init.c
void				init_mlx(t_mlx_vars *mlx, t_input *input);

// Core/error.c
void				print_error(t_return_status type);

// Logic/direccion.c
void				initialdir(char direccion, double dir[2], double plane[2]);

#endif
