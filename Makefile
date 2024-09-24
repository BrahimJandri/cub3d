NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT = Libft/libft.a

SRC = main.c ./parsing/map_parse.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C Libft
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C Libft clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C Libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re