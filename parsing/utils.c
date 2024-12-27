/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:00:36 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/27 09:56:02 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

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
}

char	*parse_texture(char *line, char **texture, t_game *game)
{
	char	*trimmed_line;
	char	**split_line;

	trimmed_line = ft_strtrim(line, " \t\n");
	split_line = ft_split(trimmed_line, ' ');
	if (split_line && ft_arraylen(split_line) >= 2)
	{
		*texture = ft_strdup(split_line[1]);
		game->config_count++;
	}
	else
		error_msg("Error\nInvalid texture line format.");
	ft_free_split(split_line);
	free(trimmed_line);
	return (*texture);
}

void	validate_color_format(char *str)
{
	char	*trimmed_str;

	trimmed_str = ft_strtrim(str, " \t\n");
	if (!trimmed_str)
		error_msg("Error\nMemory allocation failed while trimming\n");
	if (count_sep(trimmed_str) != 2)
	{
		free(trimmed_str);
		error_msg("Error\nInvalid color format\n");
	}
	free(trimmed_str);
}
