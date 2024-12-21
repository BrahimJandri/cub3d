/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <reddamss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:32:12 by reddamss          #+#    #+#             */
/*   Updated: 2024/12/17 10:49:02 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_map(char *av, t_game *data)
{
	int		fd;
	int		lines;
	char	*line;

	fd = open(av, O_RDONLY);
	line = get_next_line(fd);
	if (line == NULL)
		exit_mssg("Unvalid !");
	data->map_x = ft_strlen(line);
	free(line);
	close(fd);
	fd = open(av, O_RDONLY);
	lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	data->map_y = lines;
	close(fd);
}

void	allocate_map(char *av, t_game *data)
{
	int		fd;
	int		i;
	char	*tmp;

	data->map = malloc(sizeof(char *) * (data->map_y + 1));
	if (!data->map)
		return ;
	fd = open(av, O_RDONLY);
	i = 0;
	tmp = get_next_line(fd);
	while (tmp)
	{
		data->map[i++] = ft_strdup(tmp);
		free(tmp);
		tmp = get_next_line(fd);
	}
	data->map[data->map_y] = NULL;
	close(fd);
}


void	exit_mssg(char *str)
{
	ft_putstr("Error:\n");
	ft_putstr(str);
	exit(1);
}