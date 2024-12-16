NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -lm -lX11 -lmlx -lXext
LIBFT = Libft/libft.a
SRC = main.c ./parsing/read_map.c ./parsing/get_next_line.c ./parsing/get_next_line_utils.c
OBJ = $(SRC:.c=.o)

# ANSI escape codes for bold text
BOLD = \033[1m
RESET = \033[0m

# Default target
all: $(NAME)
	@echo "$(BOLD)compiling success ✅$(RESET)"

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(MLXFLAGS) $(LIBFT) -o $(NAME) > /dev/null 2>&1

$(LIBFT):
	@make -C Libft > /dev/null 2>&1

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null 2>&1

clean:
	@$(MAKE) -C Libft clean > /dev/null 2>&1
	@rm -f $(OBJ)
	@echo "$(BOLD)obj file removed 🗑$(RESET)"

fclean: clean
	@$(MAKE) -C Libft fclean > /dev/null 2>&1
	@rm -f $(NAME)
	@echo "$(BOLD)all obj and exec file are removed 💔$(RESET)"

re: fclean all

.PHONY: all clean fclean re