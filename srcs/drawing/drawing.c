/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:46:18 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/22 16:52:26 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_vertical_line(t_session *session, t_ray *ray, int x)
{
	draw_textured_wall(session, x, ray->draw_start, ray->draw_end, ray);
	draw_ceiling(session, x, ray->draw_start);
	draw_floor(session, x, ray->draw_end);
}

void	draw_ceiling(t_session *session, int x, int draw_start)
{
	int			y;
	uint32_t	ceiling_color;

	ceiling_color = create_rgb(session->map->ceiling_color_r,
			session->map->ceiling_color_g, session->map->ceiling_color_b);
	y = 0;
	while (y < draw_start)
	{
		mlx_put_pixel(session->mlx_window, x, y, ceiling_color);
		y++;
	}
}

void	draw_floor(t_session *session, int x, int draw_end)
{
	int			y;
	uint32_t	floor_color;

	floor_color = create_rgb(session->map->floor_color_r,
			session->map->floor_color_g, session->map->floor_color_b);
	y = draw_end;
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

void	draw_textured_wall(t_session *session, int x, int draw_start,
		int draw_end, t_ray *ray)
{
	t_texture	*texture;
	int			tex_height;
	int			tex_width;
	double		step;
	double		tex_pos;
	int			texY;
	uint8_t		*pixel;
	uint32_t	color;

	if (ray->tex_num == 0)
		texture = &session->map->textures.north;
	else if (ray->tex_num == 1)
		texture = &session->map->textures.south;
	else if (ray->tex_num == 2)
		texture = &session->map->textures.east;
	else
		texture = &session->map->textures.west;
	tex_height = texture->texture->height;
	tex_width = texture->texture->width;
	step = 1.0 * tex_height / ray->line_height;
	tex_pos = (draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
	for (int y = draw_start; y < draw_end; y++)
	{
		texY = (int)tex_pos & (tex_height - 1);
		tex_pos += step;
		pixel = &texture->texture->pixels[(texY * tex_width + ray->tex_x)
			* texture->texture->bytes_per_pixel];
		color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
		mlx_put_pixel(session->mlx_window, x, y, color);
	}
}
