SRCS	= src/main.c src/read_utils.c src/read_scene.c src/freezers.c
 
INC		= -Ilibft/ -Iinc/

CC		= gcc

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -Wall -Wextra -Werror 

NAME	= cub3d

RM		= rm -f

%.o:%.c
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) $(INC) 

$(NAME):	$(OBJS)
			@make -C libft/ --silent
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INC) -Llibft/ -lft 

all:		$(NAME)

clean:
			$(RM) $(OBJS)
			@make -C libft/ clean --silent

fclean:		clean
			@make -C libft/ fclean --silent
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
