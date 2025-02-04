/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:00:36 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/29 11:55:57 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d_bonus.h"

int	count_sep(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == ',')
			i++;
		str++;
	}
	return (i);
}

int	ft_isspace(char *str)
{
	while (*str)
	{
		if (*str == ' ' || *str == '\t')
			return (0);
		str++;
	}
	return (1);
}

char	*free_get(char *line, int fd)
{
	free(line);
	line = get_next_line(fd);
	return (line);
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
			line = free_get(line, fd);
		else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ",
				2) == 0)
			line = free_get(line, fd);
		else
			break ;
	}
	return (line);
}

void	validate_color_format(char *str, t_game *game)
{
	char	*trimmed_str;

	trimmed_str = ft_strtrim(str, " \t\n");
	if (!trimmed_str)
		error_msg("Error\nMemory allocation failed while trimming\n");
	if (count_sep(trimmed_str) != 2)
	{
		free(trimmed_str);
		third_free(game, "Error\nInvalid color format\n");
	}
	free(trimmed_str);
}
