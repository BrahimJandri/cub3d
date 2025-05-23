NAME = cub3D
NAME_BONUS = cub3D_bonus 
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
MLXFLAGS = -lm -L./library/minilibx -lmlx -lX11 -lXext
LIBFT = ./library/Libft/libft.a
SRC = ./library/get_next_line/get_next_line.c ./library/get_next_line/get_next_line_utils.c \
	./mandatory/parsing/parsing.c ./mandatory/parsing/check_boundaries.c ./mandatory/parsing/check_columns.c ./mandatory/parsing/check_params.c \
	./mandatory/parsing/fill_map1.c ./mandatory/main.c ./mandatory/parsing/free_func.c ./mandatory/initialization.c ./mandatory/texture.c\
	./mandatory/parsing/parse_color.c ./mandatory/parsing/parse_texture.c ./mandatory/parsing/utils.c ./mandatory/getting_data.c\
	./mandatory/render.c ./mandatory/move.c ./mandatory/generate_walls.c ./mandatory/raycasting.c ./mandatory/raycasting_utils.c \
	./mandatory/utils.c ./mandatory/parsing/free_func2.c ./mandatory/parsing/utils2.c ./mandatory/free_kra.c

SRC_BNS = ./library/get_next_line/get_next_line.c ./library/get_next_line/get_next_line_utils.c \
	./bonus/parsing/parsing_bonus.c ./bonus/parsing/check_boundaries_bonus.c ./bonus/parsing/check_columns_bonus.c ./bonus/parsing/check_params_bonus.c \
	./bonus/parsing/fill_map1_bonus.c  ./bonus/main_bonus.c ./bonus/parsing/free_func_bonus.c \
	./bonus/parsing/parse_color_bonus.c ./bonus/parsing/parse_texture_bonus.c ./bonus/parsing/utils_bonus.c \
	./bonus/render_bonus.c ./bonus/move_bonus.c ./bonus/generate_walls_bonus.c ./bonus/raycasting_bonus.c ./bonus/raycasting_utils_bonus.c ./bonus/utils_bonus.c \
	./bonus/minimap_bonus.c ./bonus/minimap_util1_bonus.c ./bonus/minimap_util2_bonus.c ./bonus/parsing/free_func2_bonus.c ./bonus/free_kra_bonus.c\
	./bonus/sprites_bonus.c ./bonus/mouse_bonus.c ./bonus/initialization_bonus.c ./bonus/texture_bonus.c ./bonus/getting_data_bonus.c ./bonus/parsing/utils2_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_BNS = $(SRC_BNS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(MLXFLAGS) $(LIBFT) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BNS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ_BNS) $(MLXFLAGS) $(LIBFT) -o $(NAME_BONUS)

$(LIBFT):
	make -C ./library/Libft -s

clean:
	$(MAKE) -C ./library/Libft clean 
	rm -f $(OBJ)
	rm -f $(OBJ_BNS)


fclean: clean
	$(MAKE) -C ./library/Libft fclean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re: fclean all 

re_bonus: fclean bonus

.SECONDARY:
.PHONY: all clean fclean re bonus