NAME = cub3d

CC = clang
CFLAGS = -Wall -Wextra -Werror -O2
INC = -I inc -I libft -I mlx 

SRC_F = main.c

SRC = $(addprefix src/, $(SRC_F)) 
OBJ = $(SRC:.c=.o)

LIBFT = ./libft/libft.a
MLX = ./mlx/libmlx.a

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $^ -o $@


$(LIBFT):
	$(MAKE) -C ./libft

$(MLX):
	$(MAKE) -C ./mlx

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIBFT) $(MLX) -framework OpenGL -framework AppKit  -o $@

clean:
	rm -rf $(OBJ)
	$(MAKE) -C ./libft fclean
	$(MAKE) -C ./mlx clean

fclean: clean
	rm -rf $(NAME)

re: fclean all

debug: CFLAGS = -Wall -Wextra -Werror -g3 
debug: $(OBJ)
	$(MAKE) -C ./libft debug
	$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIBFT) -o $(NAME)

.PHONY: all clean fclean re debug
