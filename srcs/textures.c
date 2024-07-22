/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:09:29 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/22 10:31:24 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#include <unistd.h>
#include <limits.h>

void load_textures(mlx_t *mlx, t_map *map)
{
    // Load PNG textures
    map->textures.north.texture = mlx_load_png(map->no_texture_path);
    map->textures.south.texture = mlx_load_png(map->so_texture_path);
    map->textures.west.texture = mlx_load_png(map->we_texture_path);
    map->textures.east.texture = mlx_load_png(map->ea_texture_path);

    if (!map->textures.north.texture || !map->textures.south.texture || 
        !map->textures.west.texture || !map->textures.east.texture)
    {
        ft_error("Failed to load one or more texture files");
        exit(1);
    }

    // Convert textures to images
    map->textures.north.image = mlx_texture_to_image(mlx, map->textures.north.texture);
    map->textures.south.image = mlx_texture_to_image(mlx, map->textures.south.texture);
    map->textures.west.image = mlx_texture_to_image(mlx, map->textures.west.texture);
    map->textures.east.image = mlx_texture_to_image(mlx, map->textures.east.texture);

    if (!map->textures.north.image || !map->textures.south.image || 
        !map->textures.west.image || !map->textures.east.image)
    {
        ft_error("Failed to create texture images");
        exit(1);
    }

    printf("All textures loaded successfully\n");
}

void draw_textured_wall(t_session *session, int x, int drawStart, int drawEnd, t_ray *ray)
{
    t_texture *texture;
    switch(ray->texNum)
    {
        case 0: texture = &session->map->textures.north; break;
        case 1: texture = &session->map->textures.south; break;
        case 2: texture = &session->map->textures.east; break;
        case 3: texture = &session->map->textures.west; break;
        default: texture = &session->map->textures.north; // Fallback
    }

    int texHeight = texture->texture->height;
    int texWidth = texture->texture->width;

    double step = 1.0 * texHeight / ray->lineHeight;
    double texPos = (drawStart - HEIGHT / 2 + ray->lineHeight / 2) * step;

    for (int y = drawStart; y < drawEnd; y++)
    {
        int texY = (int)texPos & (texHeight - 1);
        texPos += step;

        uint8_t *pixel = &texture->texture->pixels[(texY * texWidth + ray->texX) * texture->texture->bytes_per_pixel];
        uint32_t color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];

        mlx_put_pixel(session->mlx_window, x, y, color);
    }
}
