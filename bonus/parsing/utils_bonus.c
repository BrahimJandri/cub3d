/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:00:36 by bjandri           #+#    #+#             */
/*   Updated: 2025/02/06 21:48:18 by bjandri          ###   ########.fr       */
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

int	ft_check(char *trimmed_line)
{
	return (ft_strncmp(trimmed_line, "NO ", 3) == 0 || ft_strncmp(trimmed_line,
			"SO ", 3) == 0 || ft_strncmp(trimmed_line, "WE ", 3) == 0
		|| ft_strncmp(trimmed_line, "EA ", 3) == 0 || ft_strncmp(trimmed_line,
			"F ", 2) == 0 || ft_strncmp(trimmed_line, "C ", 2) == 0);
}

char	*skip_texture_colors(int fd, char *line)
{
	char	*trimmed_line;

	while (line)
	{
		trimmed_line = ft_strtrim(line, " \t");
		if (!trimmed_line)
			return (NULL);
		if (*trimmed_line == '\n')
		{
			free(trimmed_line);
			line = free_get(line, fd);
			continue ;
		}
		if (ft_check(trimmed_line))
		{
			free(trimmed_line);
			line = free_get(line, fd);
		}
		else
		{
			free(trimmed_line);
			break ;
		}
	}
	return (line);
}

int	validate_color_format(char *str, t_game *game)
{
	char	*trimmed_str;

	(void)game;
	trimmed_str = ft_strtrim(str, " \t\n");
	if (!trimmed_str)
		error_msg("Error\nMemory allocation failed while trimming\n");
	if (count_sep(trimmed_str) != 2)
	{
		free(trimmed_str);
		return (-1);
	}
	free(trimmed_str);
	return (0);
}
