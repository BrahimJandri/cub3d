/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 09:12:30 by bjandri           #+#    #+#             */
/*   Updated: 2025/02/08 12:57:13 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

static char	**split_and_trim_color_parts(char *str)
{
	char	*trimmed_str;
	char	**parts;

	trimmed_str = ft_strtrim(str, " \t\n");
	if (!trimmed_str)
		error_msg("Error\nMemory allocation failed while trimming\n");
	parts = ft_split(trimmed_str, ',');
	free(trimmed_str);
	if (!parts)
		error_msg("Error\nMemory allocation failed while splitting\n");
	return (parts);
}

int	validate_color_parts_count(char **parts, t_game *game)
{
	int	count;

	(void)game;
	count = 0;
	while (parts[count])
		count++;
	if (count != 3)
	{
		ft_free_split(parts);
		return (-1);
	}
	return (0);
}

int	validate_and_parse_color_values(char **parts, int *colors, t_game *game)
{
	int	i;

	(void)game;
	i = 0;
	while (i < 3)
	{
		if (!ft_isspace(parts[i]) || !ft_isalldigit(parts[i]))
		{
			ft_free_split(parts);
			return (-1);
		}
		colors[i] = ft_atoi(parts[i]);
		if (colors[i] < 0 || colors[i] > 255)
		{
			ft_free_split(parts);
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	convert_to_color(int *colors)
{
	return ((colors[0] << 16) | (colors[1] << 8) | colors[2]);
}

int	parse_color(char *str, t_game *game)
{
	char	**parts;
	int		colors[3];
	int		color;

	if (validate_color_format(str, game))
		return (-1);
	parts = split_and_trim_color_parts(str);
	if (validate_color_parts_count(parts, game))
		return (-1);
	if (validate_and_parse_color_values(parts, colors, game))
		return (-1);
	ft_free_split(parts);
	color = convert_to_color(colors);
	game->config_count++;
	return (color);
}
