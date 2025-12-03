#ifndef CUB3D_H
# define CUB3D_H

# include "stddef.h"
# include <stdio.h> //Libreria necesaria para .h?

// Enum types
typedef enum e_return_status
{
	OK,
	ERR_MALLOC,
	ERR_OPEN,
	ERR_PARSER
}	t_return_status;

// Estructura para inputs
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

// Img_data // estructruara para acelerar la impresion de pixeles
typedef struct s_img_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img_data;

// Vision // estructura para los valores de visión
typedef struct s_vision
{
	double pos[2];    // Posición del jugador
	double v_vis[2];  // Vector de visión principal
	double v_per[2];  // Vector perpendicular (plano cámara)
	double plane1[2]; // Punto izquierdo del plano
	double plane2[2]; // Punto derecho del plano
	double v_dir[2];  // Vector direccional temporal
	double fov_scale; // Escala del campo de visión
	double ang;
}				t_vision;

// Mlx_vars // estructrura necesaria para el correcto funcionamiento de hook
typedef struct s_mlx_vars
{
	void		*mlx;
	void		*win;
	t_img_data	img;
	t_vision	vision;
}				t_mlx_vars;

// Functions import
char	**import_tmp_map(const char *path);
void	print_map(const t_input *input);
void	free_map(char **map);
int		is_char_map(const char c);
int		is_line_map(const char *line);

// Functions error
void	print_error(t_return_status type);

// Funcions TRGB // Utils/trgb.c
int				create_trgb(int t, int r, int g, int b);
int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);

// temp Funcion to test // Utils/draw.c
void			draw_filled_circle(t_img_data *data, int xc, int yc, int r,
					int color);
void			draw_cros(t_img_data *data, int x_size, int y_size, int color);
void			draw_vison(t_img_data *data, double *pos, double *v_vis, int color);
void			clear_image(t_img_data *data, int width, int height, int color);
void			draw_full_vision(t_img_data *data, t_vision *vision);
void			init_vision(t_vision *vision, int x, int y);

// Funcion i crete to render mlx // Utils/my_mlx_func.c
void			my_mlx_pixel_put(t_img_data *data, int x, int y, int color);

// Funcion close_win // Utils/close_mlx.c
int				close_mlx(t_mlx_vars *vars);

// Funcion open_win // Utils/open.mlx.c
int				open_win(t_mlx_vars *data, int x, int y, char *name);

// Funcions to handel the input // Logic/handle_input.c
int				handle_input(int keysym, t_mlx_vars *data);

#endif
