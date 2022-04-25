NAME = cub3d

CC = clang
CFLAGS = -Wall -Wextra -Werror -O2
INC = -I inc -I libft

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

MACROS = -I ./inc/mac



SRC_F = 	main.c \
		temporary_utils.c \
		read_utils.c \
		read_scene.c \
		freezers.c

UTILS_F = 	utils.c
MINILIBX_F =	main_loop.c \
		hooks.c \
		render.c



SRC = $(addprefix src/, $(SRC_F)) 
SRC += $(addprefix src/utils/, $(UTILS_F))
SRC += $(addprefix src/minilibx/, $(MINILIBX_F))

OBJ = $(SRC:.c=.o)

LIBFT = ./libft/libft.a

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) $(MACROS) -c $^ -o $@


$(LIBFT):
	$(MAKE) -C ./libft

$(MLX):
	@$(MAKE) -C $(MLX_D)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $@

linux: MACROS = -I ./inc/linux
linux: INC = -I inc -I libft -I mlx_linux -I /usr/include
linux: $(OBJ) $(LIBFT) $(MLX_LINUX)
		$(CC) $(OBJ) $(LIBFT) $(MLX_LINUX) -o $(NAME)

clean:
	rm -rf $(OBJ)
	$(MAKE) -C ./libft fclean
	$(MAKE) -C $(MLX_D) clean

fclean: clean
	rm -rf $(NAME)

re: fclean all

debug: CFLAGS = -Wall -Wextra -Werror -g3
debug: $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(INC) $(MACROS) $(OBJ) $(LIBFT) $(MLX) -framework OpenGL -framework AppKit  -o $(NAME)

norm:
	norminette src/ inc/

.PHONY: all clean fclean re debug norm
