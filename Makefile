NAME = cub3D

CC = clang
CFLAGS = -Wall -Wextra -Werror -O2
INC = -I inc -I libft
LIBFT = ./libft/libft.a

ifeq ($(shell uname), Linux)
	INC += -I inc/linux -I mlx_linux
	MLX = ./mlx_linux/libmlx.a
	MLX_D = mlx_linux
	MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
else
	INC += -I inc/mac -I mlx
	MLX = ./mlx/libmlx.a
	MLX_D = mlx
	MLX_FLAGS = -framework OpenGL -framework AppKit
endif

SRC_F = 		main.c \
				read_utils.c \
				read_utils_2.c \
				read_scene.c \
				parse_scene.c \
				read_checks_1.c \
				read_colors.c \
				read_load_file.c \
				freezers.c \
				freezers_2.c \
				check_map.c

UTILS_F = 		utils.c \
				vector.c

MINILIBX_F =	main_loop.c \
				hooks.c \
				render.c \
				ray.c \
				texture.c

SRC = $(addprefix src/, $(SRC_F))
SRC += $(addprefix src/utils/, $(UTILS_F))
SRC += $(addprefix src/minilibx/, $(MINILIBX_F))
OBJ = $(SRC:.c=.o)


all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $^ -o $@

$(LIBFT):
	$(MAKE) -C ./libft

$(MLX):
	@$(MAKE) -C $(MLX_D)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $@

clean:
	rm -rf $(OBJ)
	$(MAKE) -C ./libft fclean
	$(MAKE) -C $(MLX_D) clean

fclean: clean
	rm -rf $(NAME)

re: fclean all

debug: CFLAGS = -Wall -Wextra -Werror -g0 -fsanitize=address
debug: $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)

norm:
	norminette src/ inc/

.PHONY: all clean fclean re debug norm
