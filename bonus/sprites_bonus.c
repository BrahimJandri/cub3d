/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:48:24 by rachid            #+#    #+#             */
/*   Updated: 2025/02/08 10:05:05 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"

void	init_sprites(t_game *data)
{
	int			i;
	char		*number;
	t_texture	*gun;

	gun = malloc(sizeof(t_texture) * FRAMES);
	if (!gun)
		error_msg("gun failed\n");
	i = 0;
	while (i < FRAMES)
	{
		gun[i].path = ft_strdup("./Textures/braha/");
		number = ft_itoa(i);
		gun[i].path = ft_strjjoin(gun[i].path, number);
		gun[i].path = ft_strjjoin(gun[i].path, ".xpm");
		free(number);
		i++;
	}
	data->gun = gun;
}

void	load_gun_frames(t_game *data)
{
	int	i;

	i = 0;
	while (i < FRAMES)
	{
		data->gun[i].img = mlx_xpm_file_to_image(data->mlx, data->gun[i].path,
				&data->gun[i].tex_width, &data->gun[i].tex_height);
		if (!data->gun[i].img)
		{
			while (i >= 0)
			{
				if (data->gun[i].img)
					mlx_destroy_image(data->mlx, data->gun[i].img);
				i--;
			}
			return (destroy_path(data), escape_free(data), free_all(data),
				error_msg("images failed\n"), exit(1));
		}
		data->gun[i].addrs = mlx_get_data_addr(data->gun[i].img,
				&data->gun[i].bpp, &data->gun[i].size_line,
				&data->gun[i].endian);
		if (!data->gun[i].addrs)
		{
			return (error_msg("image address failed\n"), exit(1));
		}
		i++;
	}
	destroy_path(data);
}

void	render_gun(t_game *data)
{
	if (data->player->jab)
	{
		data->player->frames++;
		if (data->player->frames >= FRAMES)
		{
			data->player->frames = 0;
			data->player->jab = 0;
		}
		put_gun(data, data->player->frames);
	}
}

void	put_gun(t_game *data, int frame)
{
	double	x;
	double	y;
	int		i;
	int		j;
	int		color;

	i = 0;
	x = (S_WIDTH - data->gun[frame].tex_width) / 2;
	y = (S_HEIGHT - data->gun[frame].tex_height);
	while (i < data->gun[frame].tex_height)
	{
		j = 0;
		while (j < data->gun[frame].tex_width)
		{
			color = *(unsigned int *)(data->gun[frame].addrs + (i
						* data->gun[frame].size_line + j * (data->gun[frame].bpp
							/ 8)));
			if ((unsigned int)color != 0xFF000000)
			{
				my_mlx_pixel_put(data, j + x, i + y, color);
			}
			j++;
		}
		i++;
	}
}
