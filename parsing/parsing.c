/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:45:30 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/19 15:03:59 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int open_file(const char *file)
{
    int fd = open(file, O_RDONLY);
    if (fd == -1)
        return error_msg("Error: Open file failed\n"), -1;
    return fd;
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

size_t ft_arraylen(char **array)
{
    size_t length = 0;
    while (array[length])
        length++;
    return length;
}

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

char *parse_textures_and_colors(t_game *game, char *line, int fd)
{
    while (line)
    {
        if (ft_strncmp(line, "NO ", 3) == 0)
            game->no_texture = ft_strdup(line + 3);
        else if (ft_strncmp(line, "SO ", 3) == 0)
            game->so_texture = ft_strdup(line + 3);
        else if (ft_strncmp(line, "WE ", 3) == 0)
            game->we_texture = ft_strdup(line + 3);
        else if (ft_strncmp(line, "EA ", 3) == 0)
            game->ea_texture = ft_strdup(line + 3);
        else if (ft_strncmp(line, "F ", 2) == 0)
            game->floor_color = parse_color(line + 2);
        else if (ft_strncmp(line, "C ", 2) == 0)
            game->ceiling_color = parse_color(line + 2);
        else if (line[0] == '1' || line[0] == ' ')
            break;
        free(line);
        line = get_next_line(fd);
    }
    return line;
}

char *skip_empty_lines(int fd)
{
    char *line = get_next_line(fd);

    while (line)
    {
        char *trimmed_line = ft_strtrim(line, " \t");

        if (*trimmed_line == '\0')
        {
            free(line);
            free(trimmed_line);
            line = get_next_line(fd);
        }
        else
        {
            free(trimmed_line);
            break;
        }
    }
    return line;
}

void check_map_params(t_game *game)
{
    size_t i;
    size_t j;

    i = 0;
    while (i < game->map_height)
    {
        char *trimed_line = ft_strtrim(game->map[i], " \t");
        j = 0;
        while (trimed_line[j])
        {
            if (trimed_line[j] != '1' && trimed_line[j] != '0' &&
                trimed_line[j] != 'N' && trimed_line[j] != 'S' &&
                trimed_line[j] != 'E' && trimed_line[j] != 'W')
            {
                printf("\nhere ==> %s\n", trimed_line);
                error_msg("Bad Params on map.");
            }
            if (trimed_line[j] == 'N' || trimed_line[j] == 'S' ||
                trimed_line[j] == 'E' || trimed_line[j] == 'W')
            {
                game->player_x = i;
                game->player_y = j;
                game->player_found = 1;
            }
            j++;
        }
        free(trimed_line);
        i++;
    }
    if (!game->player_found)
        error_msg("Error: Player not found on the map.");
}

void error_msg(char *str)
{
    ft_putstr_fd(str, 2);
    exit(1);
}

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
}

void fill_map(t_game *game, const char *file)
{
    int fd = open_file(file);

    size_t i = 0;
    char *line = skip_empty_lines(fd);
    line = parse_textures_and_colors(game, line, fd);

    game->map = malloc(sizeof(char *) * (game->map_height + 1));
    if (!game->map)
        error_msg("Memory allocation error");

    while (line)
    {
        game->map[i] = ft_strdup(line);
        i++;
        free(line);
        line = get_next_line(fd);
    }
    game->map[i] = NULL;
    close(fd);
}

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

void draw_map(t_game *game)
{
    size_t i = 0;
    while (game->map[i])
    {
        printf("%s", game->map[i]);
        i++;
    }
}
void read_map(t_game *game, char *file)
{
    int fd = open_file(file);

    calculate_map_dimensions(game, file);
    fill_map(game, file);
    draw_map(game);
    check_map_params(game);
    close(fd);
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
    free(game);
    return (0);
}