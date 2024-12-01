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
	free(game->map);
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

void draw_map(t_game *game)
{
	int i;

	i = 0;
	while (i < game->map_x)
	{
		printf("%s\n", game->map[i]);
		i++;
	}
}

static void fill_map(t_game *game, int fd)
{
	int i;
	char *line;

	i = 0;
	game->map = malloc(sizeof(char *) * (game->map_x + 1));
	if (!game->map)
		error_msg("Memory allocation error");
	while (i < game->map_x)
	{
		line = get_next_line(fd);
		if (line)
		{
			game->map[i] = ft_strdup(line);
			free(line);
			i++;
		}
	}
	game->map[i] = NULL;
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
			printf("ERROR 404 NEWLINE FOUND\n");
			exit(1);
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
	fill_map(game, fd);
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
	parse_lines(game);
	draw_map(game);
	close(fd);
}
