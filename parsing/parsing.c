/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:45:30 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/19 10:40:57 by bjandri          ###   ########.fr       */
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
    while (line && *line == '\n')
    {
        free(line);
        line = get_next_line(fd);
    }
    return line;
}

void validate_map(t_game *game)
{
    size_t i = 0;
    while (i < game->map_height)
    {
        size_t j = 0;
        while (j < game->map_width)
        {
            if (game->map[i][j] != '1' && game->map[i][j] != '0' &&
                game->map[i][j] != 'N' && game->map[i][j] != 'S' &&
                game->map[i][j] != 'E' && game->map[i][j] != 'W')
                error_msg("Error: Invalid character in map\n");

            if ((i == 0 || i == game->map_height - 1 ||
                 j == 0 || j == game->map_width - 1) &&
                game->map[i][j] != '1')
                error_msg("Error: Map not enclosed by walls\n");

            j++;
        }
        i++;
    }
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
    game->line_number = 1;
    game->map_width = 0;
    game->map_height = 0;
}

void fill_map(t_game *game, int fd)
{
    char *line = skip_empty_lines(fd);
    line = parse_textures_and_colors(game, line, fd);
    // if (!line || *line != '1')
    //     error_msg("Error: Invalid map format\n");
    game->map = ft_calloc(game->map_height + 1, sizeof(char *));
    int i = 0;
    while (line)
    {
        game->map[i++] = ft_strdup(line);
        free(line);
        line = get_next_line(fd);
    }
}

void calculate_map_dimensions(t_game *game, const char *file)
{
    int fd = open_file(file);
    char *line = get_next_line(fd);

    while (line)
    {
        char *trimed_line = ft_strtrim(line, " \t");
        if (*trimed_line == '1' || *trimed_line == '0')
        {
            game->map_height++;
            size_t line_length = ft_strlen(trimed_line);
            if (line_length > game->map_width)
                game->map_width = line_length;
        }
        free(line);
        free(trimed_line);
        line = get_next_line(fd);
    }
    close(fd);
}

void draw_map(t_game *game)
{
    size_t i = 0;
    while(i <= game->map_height)
    {
        printf("%s", game->map[i]);
        i++;
    }
}
void read_map(t_game *game, char *file)
{
    int fd = open_file(file);

    calculate_map_dimensions(game, file);
    fill_map(game, fd);
    draw_map(game);
    validate_map(game);
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
    free(game);
    return (0);
}