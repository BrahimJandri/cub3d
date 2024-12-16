NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLXFLGS = -lm -lmlx -lXext -lX11 
SRCS = main.c helpers.c solong.c get_next_line.c get_next_line_utils.c player.c
OBJS = $(SRCS:.c=.o)
LIBFT = ./libft/libft.a

all: $(NAME) clean

$(NAME): $(OBJS) $(LIBFT) 
	$(CC) $(CFLAGS) $^ $(MLXFLGS) -o $@

$(LIBFT):
	make -C libft

clean:
	make clean -C libft
	rm -rf $(OBJS)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all

.PHONY:	all clean fclean re
.SECONDARY: