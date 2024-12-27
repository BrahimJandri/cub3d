NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
MLXFLAGS = -lm -L./library/minilibx -lmlx -lX11 -lXext
LIBFT = ./library/Libft/libft.a
SRC = ./library/get_next_line/get_next_line.c ./library/get_next_line/get_next_line_utils.c \
	./parsing/parsing.c ./parsing/check_boundaries.c ./parsing/check_columns.c ./parsing/check_params.c \
	./parsing/fill_map1.c ./parsing/flood_fill.c ./parsing/main.c ./parsing/draw.c ./parsing/free_func.c \
	./parsing/parse_color.c ./parsing/parse_texture.c ./parsing/utils.c
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
	@$(CC) $(CFLAGS) -c $< -o $@ 

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