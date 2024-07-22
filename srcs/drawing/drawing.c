/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:46:18 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/22 13:46:27 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_vertical_line(t_session *session, t_ray *ray, int x)
{
    draw_textured_wall(session, x, ray->drawStart, ray->drawEnd, ray);
    draw_ceiling(session, x, ray->drawStart);
    draw_floor(session, x, ray->drawEnd);
}


void draw_ceiling(t_session *session, int x, int drawStart)
{
    int y;
    uint32_t ceiling_color;

    ceiling_color = create_rgb(session->map->ceiling_color_r,
                               session->map->ceiling_color_g,
                               session->map->ceiling_color_b);
    y = 0;
    while (y < drawStart)
    {
        mlx_put_pixel(session->mlx_window, x, y, ceiling_color);
        y++;
    }
}

void draw_floor(t_session *session, int x, int drawEnd)
{
    int y;
    uint32_t floor_color;

    floor_color = create_rgb(session->map->floor_color_r,
                             session->map->floor_color_g,
                             session->map->floor_color_b);
    y = drawEnd;
    while (y < HEIGHT)
    {
        mlx_put_pixel(session->mlx_window, x, y, floor_color);
        y++;
    }
}


uint32_t	create_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	return ((r << 24) | (g << 16) | (b << 8) | 255);
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
