/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:15:45 by rachid            #+#    #+#             */
/*   Updated: 2025/02/07 06:36:04 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"

// array: 0 = so, 1 = no, 2 = we, 3 = ea;
t_texture *upload_texture(t_game *data, int i)
{
    t_texture *tex;

    tex = malloc(sizeof(t_texture));
    if (!tex)
        return NULL;
    if (i == 0)
        tex->img = mlx_xpm_file_to_image(data->mlx, data->so_texture, &tex->tex_width, &tex->tex_height);
    else if (i == 1)
        tex->img = mlx_xpm_file_to_image(data->mlx, data->no_texture, &tex->tex_width, &tex->tex_height);
    else if (i == 2)
        tex->img = mlx_xpm_file_to_image(data->mlx, data->we_texture, &tex->tex_width, &tex->tex_height);
    else if (i == 3)
        tex->img = mlx_xpm_file_to_image(data->mlx, data->ea_texture, &tex->tex_width, &tex->tex_height);
    if (!tex->img)
    {
        return(free(tex), NULL);
    }
    tex->addrs = mlx_get_data_addr(tex->img, &tex->bpp, &tex->size_line, &tex->endian);
    if (!tex->addrs)
    {
        mlx_destroy_image(data->mlx, tex->img);
        return(free(tex), NULL);        
    }
    return (tex);
}

void get_textures(t_game *data)
{
    int i;

    i = 0;
    while (i < 4)
    {
        data->texture[i] = upload_texture(data, i);
        if(!data->texture[i])
        {
            while(i >= 0)
            {
                if(data->texture[i])
                {
                    if(data->texture[i]->img)
                        mlx_destroy_image(data->mlx, data->texture[i]->img);
                    free(data->texture[i]);
                }
                i--;
            }
            return(wall_tex_free(data), error_msg("textures failed to allocate\n"), exit(1));
        }
        i++;
    }
    return;
}

void set_direction(t_game *data)
{
    if (data->player->character == 'N')
        data->player->rotationAngle = ((PI * 3) / 2);
    else if (data->player->character == 'S')
        data->player->rotationAngle = (PI / 2);
    else if (data->player->character == 'E')
        data->player->rotationAngle = 0;
    else if (data->player->character == 'W')
        data->player->rotationAngle = PI;
}

int get_plyr_pos(t_game *data)
{
    int x;
    int y;

    y = 0;
    while (y < data->map_height) // is small than the height
    {
        x = 0;
        while (x < data->map_width) // is small than the width
        {
            if (ft_strchr("NSEW", data->map[y][x]))
            {
                data->player->character = data->map[y][x];
                data->player->x = x * TILE + (TILE / 2);
                data->player->y = y * TILE + (TILE / 2);
                data->map[y][x] = '0';
            }
            x++;
        }
        y++;
    }
    return (-1);
}