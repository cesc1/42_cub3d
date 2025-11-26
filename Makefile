# 42 header

NAME := cub3D

# Directory names
SRC_DIR := src
OBJ_DIR := obj
INCLUDE_DIR := include
LIB := lib
LIBFT_DIR := $(LIB)/libft
MLX_DIR := $(LIB)/minilibx

LIBFT := $(LIBFT_DIR)/libft.a
LIBMLX := $(MLX_DIR)/libmlx.a
MLX_CONFIG := $(MLX_DIR)/configure
MLX_STAMP := $(MLX_DIR)/.downloaded

# Files (don't add "src/")
SRC := main.c

OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEP := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.d))

# Files from libraries
SRC_LIBFT := $(addprefix $(LIBFT_DIR)/, $(shell $(MAKE) -s -C $(LIBFT_DIR) export_src))
SRC_MLX = mlx_init.c mlx_new_window.c mlx_pixel_put.c mlx_loop.c \
	mlx_mouse_hook.c mlx_key_hook.c mlx_expose_hook.c mlx_loop_hook.c \
	mlx_int_anti_resize_win.c mlx_int_do_nothing.c \
	mlx_int_wait_first_expose.c mlx_int_get_visual.c \
	mlx_flush_event.c mlx_string_put.c mlx_set_font.c \
	mlx_new_image.c mlx_get_data_addr.c \
	mlx_put_image_to_window.c mlx_get_color_value.c mlx_clear_window.c \
	mlx_xpm.c mlx_int_str_to_wordtab.c mlx_destroy_window.c \
	mlx_int_param_event.c mlx_int_set_win_event_mask.c mlx_hook.c \
	mlx_rgb.c mlx_destroy_image.c mlx_mouse.c mlx_screen_size.c \
	mlx_destroy_display.c
SRC_MLX := $(addprefix $(MLX_DIR)/, $(SRC_MLX))


# Flags
CC := cc
IFLAGS := -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
CFLAGS := -Wall -Werror -Wextra -g -MMD -MP $(IFLAGS)
LDFLAGS := -L/usr/lib -lXext -lX11 -lm


# =========================================================================

all: $(NAME)

# Cub3d rule
$(NAME):  $(LIBFT) $(LIBMLX) $(OBJ)
	$(CC) $(OBJ) $(LIBFT) $(LIBMLX) $(CFLAGS) $(LDFLAGS) -o $@

# Library rules
$(LIBFT): $(SRC_LIBFT)
	$(MAKE) -C $(LIBFT_DIR)

$(LIBMLX): $(MLX_STAMP) $(SRC_MLX)
	cd $(MLX_DIR) && ./configure

$(MLX_STAMP):
	rm -rf $(MLX_DIR)
	wget https://github.com/42paris/minilibx-linux/archive/refs/heads/master.zip -O minilibx.zip
	unzip minilibx.zip
	rm minilibx.zip
	mv minilibx-linux-master $(MLX_DIR)
	touch $(MLX_STAMP)

# Objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Standard rules
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	if [ -d $(MLX_DIR) ]; then $(MAKE) -C $(MLX_DIR) clean; fi

fclean:
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(MLX_DIR)

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re
