NAME = cub3d

CC = clang
CFLAGS = -Wall -Wextra -Werror -O2
INC = -I inc -I libft -I mlx
MACROS = -I ./inc/mac


SRC_F = main.c
MINILIBX_F = hooks.c


SRC = $(addprefix src/, $(SRC_F)) 
SRC += $(addprefix src/minilibx/, $(MINILIBX_F))

OBJ = $(SRC:.c=.o)

LIBFT = ./libft/libft.a
MLX = ./mlx/libmlx.a
MLX_LINUX = ./mlx_linux/libmlx.a

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $^ -o $@


$(LIBFT):
	$(MAKE) -C ./libft

$(MLX):
	$(MAKE) -C ./mlx

$(MLX_LINUX):
	$(MAKE) -C ./mlx_linux

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(INC) $(MACROS) $(OBJ) $(LIBFT) $(MLX) -framework OpenGL -framework AppKit  -o $@

linux: INC = -I inc -I libft -I mlx_linux -I /usr/include
linux: $(OBJ) $(LIBFT) $(MLX_LINUX)
		$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
	rm -rf $(OBJ)
	$(MAKE) -C ./libft fclean
	$(MAKE) -C ./mlx clean
	$(MAKE) -C ./mlx_linux clean

fclean: clean
	rm -rf $(NAME)

re: fclean all

debug: CFLAGS = -Wall -Wextra -Werror -g3 
debug: $(OBJ)
	$(MAKE) -C ./libft debug
	$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIBFT) -o $(NAME)

norm:
	norminette src/ inc/

.PHONY: all clean fclean re debug norm
