NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
MLXFLAGS = -lm -lX11 -lmlx -lXext
LIBFT = ./library/Libft/libft.a
SRC = ./parsing/main.c ./parsing/parse_config/parse_config.c ./parsing/utils/utils1.c
OBJ = $(SRC:.c=.o)

# ANSI escape codes for bold text
BOLD = \033[1m
RESET = \033[0m

# Default target
all: $(NAME)
	@echo "$(BOLD)compiling success ✅$(RESET)"

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(MLXFLAGS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C ./library/Libft > /dev/null 2>&1

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null 2>&1

clean:
	@$(MAKE) -C ./library/Libft clean > /dev/null 2>&1
	@rm -f $(OBJ)
	@echo "$(BOLD)obj file removed 🗑$(RESET)"

fclean: clean
	@$(MAKE) -C ./library/Libft fclean > /dev/null 2>&1
	@rm -f $(NAME)
	@echo "$(BOLD)all obj and exec file are removed 💔$(RESET)"

re: fclean all

.PHONY: all clean fclean re