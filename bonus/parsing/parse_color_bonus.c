/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 09:12:30 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/28 15:59:32 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d_bonus.h"

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

void	validate_color_parts_count(char **parts)
{
	int	count;

	count = 0;
	while (parts[count])
		count++;
	if (count != 3)
	{
		ft_free_split(parts);
		error_msg("Error\nInvalid color format\n");
	}
}

void	validate_and_parse_color_values(char **parts, int *colors)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!ft_isspace(parts[i]))
		{
			ft_free_split(parts);
			error_msg("Error\nInvalid color format\n");
		}
		colors[i] = ft_atoi(parts[i]);
		if (colors[i] < 0 || colors[i] > 255)
		{
			ft_free_split(parts);
			error_msg("Error\nColor values must be in the range 0-255\n");
		}
		i++;
	}
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

	validate_color_format(str);
	parts = split_and_trim_color_parts(str);
	validate_color_parts_count(parts);
	validate_and_parse_color_values(parts, colors);
	ft_free_split(parts);
	color = convert_to_color(colors);
	game->config_count++;
	return (color);
}
