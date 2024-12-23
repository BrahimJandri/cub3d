/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:45:30 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/23 13:26:20 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

// Open file function
int	open_file(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_msg("Error\nOpen file failed\n"), -1);
	return (fd);
}

void	free_texture(t_game *game)
{
	if (game->so_texture)
	{
		free(game->so_texture);
		game->so_texture = NULL;
	}
	if (game->no_texture)
	{
		free(game->no_texture);
		game->no_texture = NULL;
	}
	if (game->we_texture)
	{
		free(game->we_texture);
		game->we_texture = NULL;
	}
	if (game->ea_texture)
	{
		free(game->ea_texture);
		game->ea_texture = NULL;
	}
}

// Free memory allocated for game
void	free_all(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	i = 0;
	while (game->map_dup[i])
	{
		free(game->map_dup[i]);
		i++;
	}
	free(game->map);
	game->map = NULL;
	free(game->map_dup);
	game->map_dup = NULL;
	free_texture(game);
	free(game);
}

// Function to calculate the length of an array of strings
size_t	ft_arraylen(char **array)
{
	int	length;

	length = 0;
	while (array[length])
		length++;
	return (length);
}

// Free memory allocated for a split array of strings
void	ft_free_split(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int count_sep(char *str)
{
    int i;

    i = 0;
    while (*str)
    {
        if (*str == ',')
            i++;
        str++;
    }
    return (i);
}

// Parse a color from the string
int	parse_color(char *str, t_game *game)
{
	char	*trimmed_str;
	char	**parts;
	int		count;
	int		colors[3];
	int		i;
	int		color;

	// Trim leading/trailing whitespace or newline characters
	trimmed_str = ft_strtrim(str, " \t\n");
	if (!trimmed_str)
		error_msg("Error\nMemory allocation failed while trimming\n");
	// Split the trimmed string by commas
    if(count_sep(trimmed_str) != 2)
    {
        error_msg("Error\nInvalid color format\n");
    }
	parts = ft_split(trimmed_str, ',');
	if (!parts)
	{
		free(trimmed_str);
		error_msg("Error\nMemory allocation failed while splitting\n");
	}
	// Check if the split resulted in exactly 3 parts (RGB)
	count = 0;
	while (parts[count])
		count++;
	if (count != 3)
	{
		ft_free_split(parts);
		free(trimmed_str);
		error_msg("Error\nInvalid color format\n");
	}
	// Parse and validate the RGB components
	i = 0;
	while (i < 3)
	{
		colors[i] = ft_atoi(parts[i]); // Convert string to integer
		// Check if the color value is in the range 0-255
		if (colors[i] < 0 || colors[i] > 255)
		{
			ft_free_split(parts);
			free(trimmed_str);
			error_msg("Error\nColor values must be in the range 0-255\n");
		}
		i++;
	}
	// Combine the RGB values into a single 24-bit color (8 bits per channel)
	color = (colors[0] << 16) | (colors[1] << 8) | colors[2];
	// Update the game's configuration count
	game->config_count++;
	// Clean up memory
	ft_free_split(parts);
	free(trimmed_str);
	return (color);
}

char	*skip_texture_colors(int fd, char *line)
{
	char	*trimmed_line;

	while (line)
	{
		trimmed_line = ft_strtrim(line, " \t");
		if (*trimmed_line == '\n')
		{
			free(line);
			free(trimmed_line);
			line = get_next_line(fd);
			continue ;
		}
		free(trimmed_line);
		if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
			|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ",
				3) == 0)
		{
			free(line);
			line = get_next_line(fd);
		}
		else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ",
				2) == 0)
		{
			free(line);
			line = get_next_line(fd);
		}
		else
			break ;
	}
	return (line);
		// Return the line (could be NULL or valid line after processing)
}

// Function to skip empty lines and lines with only spaces/tabs/newlines
char	*skip_empty_lines(int fd)
{
	char *line = get_next_line(fd); // Get the first line from the file
    if(line == NULL)
    {
        error_msg("Error\nEmpty file.\n");
    }
	while (true)
	{
		if (line == NULL) // If there are no more lines (EOF)
			return (NULL);
		char *trimmed_line = ft_strtrim(line, " \t"); // Trim spaces and tabs
		if (*trimmed_line == '\0')
			// If the trimmed line is empty (just whitespace)
		{
			free(trimmed_line);       // Free the trimmed line
			free(line);               // Free the original line
			line = get_next_line(fd); // Get the next line
		}
		else
		{
			free(line);          // Free the trimmed line
			return (trimmed_line);
				// Return the original line (without trimming)
		}
	}
}
char	*parse_texture(char *line, char **texture, t_game *game)
{
	char	*trimmed_line;
	char	**split_line;

	// Trim any leading/trailing whitespaces and newline characters
	trimmed_line = ft_strtrim(line, " \t\n");
	// Split the trimmed line by spaces
	split_line = ft_split(trimmed_line, ' ');
	if (split_line && ft_arraylen(split_line) >= 2)
	{
		*texture = ft_strdup(split_line[1]); // Store the texture path
		game->config_count++;
	}
	else
	{
		// Handle error if split fails or the format is incorrect
		error_msg("Error\nInvalid texture line format.");
	}
	// Free the split line array and the trimmed line
	ft_free_split(split_line);
	free(trimmed_line);
	return (*texture);
}

// Parse textures and colors from the file
char	*parse_textures_and_colors(t_game *game, char *line, int fd)
{
	char	*trimmed_line;

	while (line)
	{
		trimmed_line = ft_strtrim(line, " \t");
		if (*trimmed_line == '\n')
		{
			free(line);
			free(trimmed_line);
			line = get_next_line(fd);
			continue ;
		}
		free(trimmed_line);
		if (ft_strncmp(line, "NO ", 3) == 0)
			game->no_texture = parse_texture(line, &game->no_texture, game);
		else if (ft_strncmp(line, "SO ", 3) == 0)
			game->so_texture = parse_texture(line, &game->so_texture, game);
		else if (ft_strncmp(line, "WE ", 3) == 0)
			game->we_texture = parse_texture(line, &game->we_texture, game);
		else if (ft_strncmp(line, "EA ", 3) == 0)
			game->ea_texture = parse_texture(line, &game->ea_texture, game);
		else if (ft_strncmp(line, "F ", 2) == 0)
			game->floor_color = parse_color(line + 2, game);
		else if (ft_strncmp(line, "C ", 2) == 0)
			game->ceiling_color = parse_color(line + 2, game);
		else
			break ;
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

void	count_params(t_game *game)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (i < game->map_height && game->map[i])
	{
		j = 0;
		while (j < game->map_width && game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->player_x = i;
				game->player_y = j;
				count++;
			}
			j++;
		}
		i++;
	}
	if (count != 1)
		error_msg("Error\nInvalid params of the map");
}

// Check if the map contains valid parameters and find the player position
void	check_map_params(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (game->map[i][j])
		{
			if ((game->map[i][j] != '1' && game->map[i][j] != '0')
				&& (game->map[i][j] != 'N' && game->map[i][j] != 'S'
					&& game->map[i][j] != 'E' && game->map[i][j] != 'W')
				&& game->map[i][j] != 32 && game->map[i][j] != '\n')
				error_msg("Error\nBad Params on map.");
			j++;
		}
		i++;
	}
}

// Error handling function
void	error_msg(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

// Initialize the game structure
void	init_game(t_game *game)
{
	game->map = NULL;
	game->map_dup = NULL;
	game->no_texture = NULL;
	game->we_texture = NULL;
	game->so_texture = NULL;
	game->ea_texture = NULL;
	game->floor_color = -1;
	game->ceiling_color = -1;
	game->map_width = 0;
	game->map_height = 0;
	game->player_found = 0;
	game->config_count = 0;
}

void	check_map_boundaries(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j] && (game->map[i][j] == ' '
				|| game->map[i][j] == '\t'))
			j++;
		if (game->map[i][j] == '\0' || game->map[i][j] == '\n')
		{
			i++;
			continue ; // Skip empty or whitespace-only lines
		}
		if (i == 0)
		{
			while (game->map[i][j] && game->map[i][j] != '\n')
			{
				if (game->map[i][j] != '1')
					error_msg("Error\nMap Not Surrounded by Walls");
				j++;
			}
		}
		else if (game->map[i + 1] == NULL) // Check the last line
		{
			while (game->map[i][j] && game->map[i][j] != '\n')
			{
				if (game->map[i][j] != '1' && game->map[i][j] != ' ')
				{
					printf("game->map[i][j] == %c\n", game->map[i][j]);
					error_msg("Error\nMap Not Surrounded by Walls");
				}
				j++;
			}
		}
		else // Check middle lines
		{
			if (game->map[i][j] != '1')
				error_msg("Error\nMap Not Surrounded by Walls in Middle Line");
			while (game->map[i][j] && game->map[i][j] != '\n')
				j++;
			if (game->map[i][j - 1] != '1')
				error_msg("Error\nMap Not Surrounded by Walls in Middle Line");
		}
		i++;
	}
}

void	check_map_columns(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	while (j < game->map_width)
	{
		i = 0;
		// Skip rows with only spaces or tabs
		while (game->map[i] && (j >= (int)ft_strlen(game->map[i])
				|| game->map[i][j] == ' ' || game->map[i][j] == '\t'
				|| game->map[i][j] == '\n' || game->map[i][j] == '\0'))
			i++;
		// Check the first valid cell in the column
		if (game->map[i] && j < (int)ft_strlen(game->map[i])
			&& game->map[i][j] != '1')
			error_msg("Error\nMap Not Surrounded by Walls at Left Boundary");
		// Move down the column to check the last cell
		while (game->map[i] && j < (int)ft_strlen(game->map[i])
			&& game->map[i][j] != '\n')
			i++;
		// Check the last valid cell in the column
		while (i > 0 && (j >= (int)ft_strlen(game->map[i - 1]) || game->map[i
				- 1][j] == ' ' || game->map[i - 1][j] == '\t' || game->map[i
				- 1][j] == '\n' || game->map[i - 1][j] == '\0'))
			i--;
		if (i > 0 && j < (int)ft_strlen(game->map[i - 1]) && game->map[i
			- 1][j] != '1')
			error_msg("Error\nMap Not Surrounded by Walls at Right Boundary");
		j++;
	}
}

// Calculate the map's dimensions
void	calculate_map_dimensions(t_game *game, const char *file)
{
	int		fd;
	char	*line;
	char	*trimed_line;
	int		line_length;

	fd = open_file(file);
	line = skip_empty_lines(fd);
	line = parse_textures_and_colors(game, line, fd);
	while (line)
	{
		trimed_line = ft_strtrim(line, " \t\n");
		game->map_height++;
		line_length = ft_strlen(trimed_line);
		if (line_length > game->map_width)
			game->map_width = line_length;
		free(line);
		free(trimed_line);
		line = get_next_line(fd);
	}
	close(fd);
}

// Fill the game map with the content of the file
void	fill_map(t_game *game, const char *file)
{
	int	fd;
	int	i;

	fd = open_file(file);
	i = 0;
	char *line = skip_empty_lines(fd); // Skip empty lines at the start
	line = skip_texture_colors(fd, line);
	game->map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!game->map)
		error_msg("Error\nMemory allocation error");
	while (line)
	{
		if (*line != '\0')
		{
			game->map[i] = ft_strdup(line);
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	game->map[i] = NULL;
	close(fd);
}
//TODO

// Function to draw the map
void	draw_map(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		printf("%s", game->map[i]);
		i++;
	}
}

bool	ft_flood_fill(int x, int y, t_game *game)
{
	bool up, down, left, right;
	// Check if we are out of bounds
	if (x < 0 || y < 0 || x >= game->map_height || y >= game->map_width)
		return (false); // Found an edge without walls.
	// Check if the current cell is already visited or is a wall
	if (game->map_dup[x][y] == 'V' || game->map_dup[x][y] == '1')
		return (true);
	// Check if there is a '0' followed by a space in any direction
	if ((game->map[x][y] == '0' && (x > 0 && game->map[x - 1][y] == ' '))
		||                    // Up
		(game->map[x][y] == '0' && (x < game->map_height - 1 && game->map[x
				+ 1][y] == ' ')) || // Down
		(game->map[x][y] == '0' && (y > 0 && game->map[x][y - 1] == ' '))
			||                    // Left
		(game->map[x][y] == '0' && (y < game->map_width - 1 && game->map[x][y
				+ 1] == ' ')))    // Right
		return (false);
	// Mark the current cell as visited
	game->map_dup[x][y] = 'V';
	// Recursively check all directions
	up = ft_flood_fill(x - 1, y, game);
	down = ft_flood_fill(x + 1, y, game);
	left = ft_flood_fill(x, y - 1, game);
	right = ft_flood_fill(x, y + 1, game);
	// Return the result of all directions
	return (up && down && left && right);
}

void	map_dup(t_game *game)
{
	int	i;

	i = 0;
	game->map_dup = malloc(sizeof(char *) * (game->map_height + 1));
	while (i < game->map_height)
	{
		game->map_dup[i] = ft_strdup(game->map[i]);
		i++;
	}
	game->map_dup[i] = NULL;
}

void	print_config(t_game *game)
{
	printf("\n\nGame->height ==> %d\n", game->map_height);
	printf("Game->width ==> %d\n", game->map_width);
	printf("Game->floor_color ==> %d\n", game->floor_color);
	printf("Game->ceiling_color ==> %d\n", game->ceiling_color);
	printf("Game->no_texture ==> %s\n", game->no_texture);
	printf("Game->so_texture ==> %s\n", game->so_texture);
	printf("Game->we_texture ==> %s\n", game->we_texture);
	printf("Game->ea_texture ==> %s\n", game->ea_texture);
}

void	check_config(t_game *game)
{
	printf("config count ==> %d\n", game->config_count);
	if (game->config_count != 6)
		error_msg("Error\nTextures or Colors are not correct.");
}

void	read_map(t_game *game, char *file)
{
	calculate_map_dimensions(game, file);
	fill_map(game, file);
	draw_map(game);
	check_map_boundaries(game);
	print_config(game);
	check_config(game);
	check_map_params(game);
	check_map_columns(game);
	map_dup(game);
	count_params(game);
	printf("player_x == %d\nplayer_y == %d\n", game->player_x, game->player_x);
	if (!ft_flood_fill(game->player_x, game->player_y, game))
		error_msg("Error\nInvalid Map");
}

void	check_extension(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_msg("Error\nFile deosn't exist or no permession\n");
	if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4) != 0)
		error_msg("Error\nInvalid file extension\n");
}

void	parse_config(t_game *game, char **av)
{
	check_extension(av[1]);
	init_game(game);
	read_map(game, av[1]);
}

int	main(int ac, char **av)
{
	t_game *game;

	game = (t_game *)malloc(sizeof(t_game));
	if (ac != 2)
		return (ft_putstr_fd("Error\nUsage : Cub3d map.cub\n", 2), 1);
	parse_config(game, av);
	free_all(game);
	return (0);
}
