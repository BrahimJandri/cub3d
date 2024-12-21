/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:45:30 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/21 11:03:27 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

// Open file function
int open_file(const char *file)
{
    int fd = open(file, O_RDONLY);
    if (fd == -1)
        return error_msg("Error: Open file failed\n"), -1;
    return fd;
}

// Free memory allocated for game
void free_all(t_game *game)
{
    int i = 0;
    while (game->map[i])
    {
        free(game->map[i]);
        i++;
    }
    free(game->map);
    free(game);
}

// Function to calculate the length of an array of strings
size_t ft_arraylen(char **array)
{
    size_t length = 0;
    while (array[length])
        length++;
    return length;
}

// Free memory allocated for a split array of strings
void ft_free_split(char **array)
{
    size_t i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

// Parse a color from the string
int parse_color(char *str)
{
    int colors[3];
    char **parts = ft_split(str, ',');
    if (!parts || ft_arraylen(parts) != 3)
        error_msg("Error: Invalid color format\n");

    int i = 0;
    while (i < 3)
    {
        colors[i] = ft_atoi(parts[i]);
        i++;
    }

    int color = (colors[0] << 16) | (colors[1] << 8) | colors[2];
    ft_free_split(parts);
    return color;
}

// Function to skip empty lines and lines with only spaces/tabs/newlines
char *skip_empty_lines(int fd)
{
    char *line = get_next_line(fd); // Get the first line from the file

    while (true)
    {
        if (line == NULL) // If there are no more lines (EOF)
            return NULL;

        char *trimmed_line = ft_strtrim(line, " \t"); // Trim spaces and tabs

        if (*trimmed_line == '\0') // If the trimmed line is empty (just whitespace)
        {
            free(trimmed_line);       // Free the trimmed line
            free(line);               // Free the original line
            line = get_next_line(fd); // Get the next line
        }
        else
        {
            free(line);          // Free the trimmed line
            return trimmed_line; // Return the original line (without trimming)
        }
    }
}

// Parse textures and colors from the file
char *parse_textures_and_colors(t_game *game, char *line, int fd)
{
    while (line)
    {
        char *trimmed_line = ft_strtrim(line, " \t");
        if (*trimmed_line == '\n')
        {
            free(line);
            free(trimmed_line);
            line = get_next_line(fd);
            continue;
        }

        // Now we can check the texture or color definitions, as the line is valid
        if (ft_strncmp(line, "NO ", 3) == 0)
        {
            game->no_texture = ft_strdup(line + 3);
            game->config_count++;
        }
        else if (ft_strncmp(line, "SO ", 3) == 0)
        {
            game->so_texture = ft_strdup(line + 3);
            game->config_count++;
        }
        else if (ft_strncmp(line, "WE ", 3) == 0)
        {
            game->we_texture = ft_strdup(line + 3);
            game->config_count++;
        }
        else if (ft_strncmp(line, "EA ", 3) == 0)
        {
            game->ea_texture = ft_strdup(line + 3);
            game->config_count++;
        }
        else if (ft_strncmp(line, "F ", 2) == 0)
        {
            game->floor_color = parse_color(line + 2);
            game->config_count++;
        }
        else if (ft_strncmp(line, "C ", 2) == 0)
        {
            game->ceiling_color = parse_color(line + 2);
            game->config_count++;
        }
        else
            break;
        free(line);
        line = get_next_line(fd);
    }
    return line; // Return the line (could be NULL or valid line after processing)
}

// Check if the map contains valid parameters and find the player position
void check_map_params(t_game *game)
{
	size_t i;
	size_t j;
	int player_found = 0;

	i = 0;
	while (i < game->map_height)
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

// Error handling function
void error_msg(char *str)
{
    ft_putstr_fd(str, 2);
    exit(1);
}

// Initialize the game structure
void init_game(t_game *game)
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

// Fill the game map with the content of the file
void fill_map(t_game *game, const char *file)
{
    int fd = open_file(file);
    size_t i = 0;
    char *line = skip_empty_lines(fd);                // Skip empty lines at the start
    line = parse_textures_and_colors(game, line, fd); // Parse textures and colors

    game->map = malloc(sizeof(char *) * (game->map_height + 1));
    if (!game->map)
        error_msg("Memory allocation error");

    // Now fill the map with 1s and 0s
    while (line)
    {
        if (*line != '\0') // Ignore empty lines
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

// Calculate the map's dimensions
void calculate_map_dimensions(t_game *game, const char *file)
{
    int fd = open_file(file);
    char *line = skip_empty_lines(fd);
    line = parse_textures_and_colors(game, line, fd);

    while (line)
    {
        char *trimed_line = ft_strtrim(line, " \t");
        game->map_height++;
        size_t line_length = ft_strlen(trimed_line);
        if (line_length > game->map_width)
            game->map_width = line_length;
        free(line);
        free(trimed_line);
        line = get_next_line(fd);
    }
    close(fd);
}

// Function to draw the map
void draw_map(t_game *game)
{
    size_t i = 0;
    while (game->map[i])
    {
        printf("%s", game->map[i]);
        i++;
    }
}

void print_config(t_game *game)
{
    printf("\n\nGame->height ==> %ld\n", game->map_height);
    printf("Game->width ==> %ld\n", game->map_width);
    printf("Game->floor_color ==> %d\n", game->floor_color);
    printf("Game->ceiling_color ==> %d\n", game->ceiling_color);
    printf("Game->no_texture ==> %s", game->no_texture);
    printf("Game->so_texture ==> %s", game->so_texture);
    printf("Game->we_texture ==> %s", game->we_texture);
    printf("Game->ea_texture ==> %s", game->ea_texture);
}

// Read the entire map, including textures, colors, and map content
void read_map(t_game *game, char *file)
{
    calculate_map_dimensions(game, file); // First calculate map dimensions
    fill_map(game, file);                 // Then fill the map
    draw_map(game);                       // Draw the map on the screen
    check_map_params(game);               // Check map for valid parameters and player position
    // print_config(game);
}

void check_extension(const char *file)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (fd == -1)
        error_msg("Error: File deosn't exicte or no permession\n");
    if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4) != 0)
        error_msg("Error: Invalid file extension File must have a .cub extension.\n");
}

void parse_config(t_game *game, char **av)
{
    check_extension(av[1]);
    init_game(game);
    read_map(game, av[1]);
}

int main(int ac, char **av)
{
    t_game *game;

    game = (t_game *)malloc(sizeof(t_game));
    if (ac != 2)
        return (ft_putstr_fd("Error\nUsage : Cub3d map.cub", 2), 1);
    parse_config(game, av);
    free_all(game);
    return (0);
}