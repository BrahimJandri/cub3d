/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:02:55 by bjandri           #+#    #+#             */
/*   Updated: 2024/10/10 16:24:41 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	error_open(int fd)
{
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
}

int	ft_countlines(int fd)
{
	int		i;
	char	*line;

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

static void	ft_fill_map(t_game *game, int fd)
{
	int		i;
	char	*line;

	i = 0;
	game->map = malloc(sizeof(char *) * (game->map_x + 1));
	if (!game->map)
		perror("Memory allocation error");
	while (i < game->map_x)
	{
		line = get_next_line(fd);
		game->map[i] = ft_strdup(line);
		free(line);
		i++;
	}
	game->map[i] = NULL;
}

int read_map(t_game *game, char *av)
{
    int fd;
    char *temp;

    fd = open(av, O_RDONLY);
    error_open(fd);
    game->map_x = ft_countlines(fd);
    close(fd);
    fd = open(av, O_RDONLY);
    error_open(fd);
    temp = get_next_line(fd);
    if(temp[0] == '\n')
        perror("Error");
    game->map_y = ft_strlen(temp) - 1;
    close(fd);
    fd = open(av, O_RDONLY);
    error_open(fd);
    ft_fill_map(game, fd);
    close(fd);
    return(0);
}
