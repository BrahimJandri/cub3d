/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:02:55 by bjandri           #+#    #+#             */
/*   Updated: 2024/11/24 15:45:39 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int check_path(char *str)
{
	int len;
	int i;

	len = ft_strlen(str);
	i = len - 4;
	if (str[i] == '.' && str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b')
		return (1);
	return (0);
}

void free_all(t_game *game)
{
	int i;

	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	i = 0;
	while (game->map2[i])
	{
		free(game->map2[i]);
		i++;
	}
	free(game->map);
	free(game->map2);
}

void check_lines(char *line)
{
	char *line_trimmed;

	int start, end;
	line_trimmed = ft_strtrim(line, " \t\n");
	if (line_trimmed[0] == '\0')
	{
		free(line_trimmed);
		return;
	}
	start = 0;
	end = ft_strlen(line_trimmed) - 1;
	if (line_trimmed[start] != '1' || line_trimmed[end] != '1')
	{
		printf("NOT CLOSE: %s\n", line_trimmed);
		free(line_trimmed);
		exit(1);
	}
	free(line_trimmed);
}

void error_open(int fd)
{
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
}

int ft_countlines(int fd)
{
	int i;
	char *line;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		i++;
		line = get_next_line(fd);
	}
	return (i);
}

static int error_msg(char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void check_map_params(t_game *game)
{
	int i;
	int j;
	int player_found = 0;

	i = 0;
	while (i < game->map_x)
	{
		j = 0;
		while (game->map[i][j])
		{
			if ((game->map[i][j] != '1' && game->map[i][j] != '0') &&
				(game->map[i][j] != 'N' && game->map[i][j] != 'S' &&
				 game->map[i][j] != 'E' && game->map[i][j] != 'W') &&
				game->map[i][j] != 32 && game->map[i][j] != '\n')
				error_msg("Bad Params on map.");
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' ||
				game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->player_x = i;
				game->player_y = j;
				player_found = 1;
			}
			j++;
		}
		i++;
	}
	if (!player_found)
		error_msg("Error: Player not found on the map.");
}

static void fill_map(t_game *game, int fd, char *file)
{
	int i = 0;
	char *line;
	int longest_row = 0;

	// First pass: Find the width of the longest line
	while ((line = get_next_line(fd)))
	{
		int len = ft_strlen(line);
		if (len > longest_row)
			longest_row = len;
		free(line);
	}
	close(fd);

	// Second pass: Allocate and fill the map
	fd = open(file, O_RDONLY);
	error_open(fd);
	game->map = malloc(sizeof(char *) * (game->map_x + 1));
	if (!game->map)
		error_msg("Memory allocation error");

	while (i < game->map_x)
	{
		line = get_next_line(fd);
		if (line)
		{
			game->map[i] = malloc(sizeof(char) * (longest_row + 1));
			if (!game->map[i])
				error_msg("Memory allocation error");
			ft_strlcpy(game->map[i], line, longest_row + 1); // Copy and pad line
			free(line);
			i++;
		}
	}
	game->map[i] = NULL;
	close(fd);
	game->map_y = longest_row; // Set the map width
}

bool all_walls(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '0')
			return false;
		i++;
	}
	return true;
}
void parse_lines(t_game *game)
{
	int i;
	int index;
	char *line_trimmed;
	int j;

	i = 0;
	while (i < game->map_x && game->map[i][0] == '\n')
		i++;
	index = i;
	while (index < game->map_x)
	{
		if (game->map[index][0] == '\n')
		{
			if (!all_walls(game->map[index - 1]) || !all_walls(game->map[index + 1]))
			{
				printf("ERROR 404 NEWLINE FOUND\n");
				exit(1);
			}
		}
		index++;
	}
	index = i;
	while (index < game->map_x)
	{
		j = 0;
		line_trimmed = ft_strtrim(game->map[index], " \t\n");
		while (line_trimmed[j])
		{
			if (line_trimmed[j] == ' ' &&
				(line_trimmed[j - 1] != '1' || line_trimmed[j + 1] != '1'))
			{
				printf("MISSING WALL: Line %d, Column %d\n", index + 1, j + 1);
				free(line_trimmed);
				exit(1);
			}
			j++;
		}
		free(line_trimmed);
		index++;
	}
}

void ft_flood_fill(int x, int y, t_game *game)
{
	if (x < 0 || x >= game->map_x || y < 0 || y >= game->map_y ||
		game->map2[x][y] == '1' || game->map2[x][y] == 'V')
		return;

	if (game->map2[x][y] == ' ')
		return; // Treat spaces as invalid tiles

	game->map2[x][y] = 'V'; // Mark visited

	ft_flood_fill(x - 1, y, game); // Up
	ft_flood_fill(x + 1, y, game); // Down
	ft_flood_fill(x, y - 1, game); // Left
	ft_flood_fill(x, y + 1, game); // Right
}

void map_dup(t_game *game)
{
	int i;

	i = 0;
	game->map2 = malloc(sizeof(char *) * (game->map_x + 1));
	while (i < game->map_x)
	{
		game->map2[i] = ft_strdup(game->map[i]);
		i++;
	}
	game->map2[i] = NULL;
}

void draw_map(t_game *game)
{
	int i;

	i = 0;
	while (game->map_x > i)
	{
		printf("%s", game->map2[i]);
		i++;
	}
}
void check_borders(t_game *game)
{
	int x;
	int y;

	y = 0;
	// Check the top and bottom borders
	while (y < game->map_y)
	{
		if (game->map2[0][y] == 'V') // Top border
			error_msg("Error\nInvalid character 'V' found on the top border");
		if (game->map2[game->map_x - 1][y] == 'V') // Bottom border
			error_msg("Error\nInvalid character 'V' found on the bottom border");
		y++;
	}
	x = 0;
	// Check the left and right borders
	while (x < game->map_x)
	{
		if (game->map2[x][0] == 'V') // Left border
			error_msg("Error\nInvalid character 'V' found on the left border");
		if (game->map2[x][game->map_y - 1] == 'V') // Right border
			error_msg("Error\nInvalid character 'V' found on the right border");
		x++;
	}
}

void read_map(t_game *game, char *file)
{
	char *line;
	int fd;
	int linecount;

	fd = open(file, O_RDONLY);
	error_open(fd);
	linecount = ft_countlines(fd);
	if (!linecount)
	{
		perror("Error\nEmpty Map");
		exit(EXIT_FAILURE);
	}
	close(fd);
	game->map_x = linecount;
	fd = open(file, O_RDONLY);
	error_open(fd);
	fill_map(game, fd, file);
	fd = open(file, O_RDONLY);
	error_open(fd);
	line = get_next_line(fd);
	while (line)
	{
		check_lines(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	check_map_params(game);
	parse_lines(game);
	map_dup(game);
	ft_flood_fill(game->player_x, game->player_y, game);
	draw_map(game);
	check_borders(game);
	close(fd);
}
