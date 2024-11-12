NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
LIBFT = Libft/libft.a
SRC = main.c ./parsing/map_parse.c ./parsing/read_map.c ./parsing/get_next_line.c ./parsing/get_next_line_utils.c
OBJ = $(SRC:.c=.o)

# ANSI escape codes for bold text
BOLD = \033[1m
RESET = \033[0m

# Default target
all: $(NAME)
	@echo "$(BOLD)compiling success ✅$(RESET)"

$(NAME): $(OBJ)
	@$(MAKE) -C Libft > /dev/null 2>&1  # Suppress output from Libft make
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) > /dev/null 2>&1  # Suppress gcc output

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null 2>&1  # Suppress gcc output

clean:
	@$(MAKE) -C Libft clean > /dev/null 2>&1  # Suppress Libft clean output
	@rm -f $(OBJ)
	@echo "$(BOLD)obj file removed 🗑$(RESET)"

fclean: clean
	@$(MAKE) -C Libft fclean > /dev/null 2>&1  # Suppress Libft fclean output
	@rm -f $(NAME)
	@echo "$(BOLD)all obj and exec file are removed 💔$(RESET)"

re: fclean all

.PHONY: all clean fclean re
