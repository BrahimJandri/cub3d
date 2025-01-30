NAME = cub3d
NAME_BONUS = cub3d_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
MLXFLAGS = -lm -L./library/minilibx -lmlx -lX11 -lXext
LIBFT = ./library/Libft/libft.a
SRC = ./library/get_next_line/get_next_line.c ./library/get_next_line/get_next_line_utils.c \
	./mandatory/parsing/parsing.c ./mandatory/parsing/check_boundaries.c ./mandatory/parsing/check_columns.c ./mandatory/parsing/check_params.c \
	./mandatory/parsing/fill_map1.c ./mandatory/parsing/flood_fill.c ./mandatory/main.c ./mandatory/parsing/free_func.c \
	./mandatory/parsing/parse_color.c ./mandatory/parsing/parse_texture.c ./mandatory/parsing/utils.c \
	./mandatory/render.c ./mandatory/move.c ./mandatory/generate_walls.c ./mandatory/raycasting.c ./mandatory/raycasting_utils.c ./mandatory/utils.c ./mandatory/draw.c

SRC_BNS = ./library/get_next_line/get_next_line.c ./library/get_next_line/get_next_line_utils.c \
	./bonus/parsing/parsing.c ./bonus/parsing/check_boundaries.c ./bonus/parsing/check_columns.c ./bonus/parsing/check_params.c \
	./bonus/parsing/fill_map1.c ./bonus/parsing/flood_fill.c ./bonus/main.c ./bonus/parsing/free_func.c \
	./bonus/parsing/parse_color.c ./bonus/parsing/parse_texture.c ./bonus/parsing/utils.c \
	./bonus/render.c ./bonus/move.c ./bonus/generate_walls.c ./bonus/raycasting.c ./bonus/raycasting_utils.c ./bonus/utils.c ./bonus/draw.c
OBJ = $(SRC:.c=.o)
OBJ_BNS = $(SRC_BNS:.c=.o)

# ANSI escape codes for bold text
BOLD = \033[1m
RESET = \033[0m

# Default target
all: $(NAME) clean 
	@echo "$(BOLD)compiling success ✅$(RESET)"

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(MLXFLAGS) $(LIBFT) -o $(NAME)

bonus: $(OBJ_BNS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ_BNS) $(MLXFLAGS) $(LIBFT) -o $(NAME_BONUS)
	@echo "$(BOLD)Bonus features compiled successfully 💥$(RESET)"

$(LIBFT):
	@make -C ./library/Libft > /dev/null 2>&1

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	@$(MAKE) -C ./library/Libft clean > /dev/null 2>&1
	@rm -f $(OBJ)
	@rm -f $(OBJ_BNS)
	@echo "$(BOLD)obj file removed 🗑$(RESET)"

fclean: clean
	@$(MAKE) -C ./library/Libft fclean > /dev/null 2>&1
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@echo "$(BOLD)all obj and exec file are removed 💔$(RESET)"

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re bonus
