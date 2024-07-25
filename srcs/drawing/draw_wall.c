/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 08:33:03 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/24 08:33:07 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

uint32_t	get_texture_color(mlx_texture_t *texture, int tex_x, int tex_y)
{
	uint8_t	*pixel;
	int		index;

	index = (tex_y * texture->width + tex_x) * texture->bytes_per_pixel;
	pixel = &texture->pixels[index];
	return ((pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3]);
}

t_texture	*select_texture(t_session *session, t_ray *ray)
{
	if (ray->tex_num == 0)
		return (&session->map->textures.north);
	else if (ray->tex_num == 1)
		return (&session->map->textures.south);
	else if (ray->tex_num == 2)
		return (&session->map->textures.east);
	else
		return (&session->map->textures.west);
}

void	init_tex_info(t_tex_info *tex_info, t_texture *texture, t_ray *ray)
{
	tex_info->texture = texture->texture;
	tex_info->height = texture->texture->height;
	tex_info->width = texture->texture->width;
	tex_info->step = 1.0 * tex_info->height / ray->line_height;
	tex_info->pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* tex_info->step;
}

void	draw_wall_slice(t_session *session, int x, t_ray *ray,
		t_tex_info *tex_info)
{
	int			y;
	int			tex_y;
	uint32_t	color;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_info->pos & (tex_info->height - 1);
		tex_info->pos += tex_info->step;
		color = get_texture_color(tex_info->texture, ray->tex_x, tex_y);
		mlx_put_pixel(session->mlx_window, x, y, color);
		y++;
	}
}

void	draw_textured_wall(t_session *session, int x, t_ray *ray)
{
	t_texture	*texture;
	t_tex_info	tex_info;

	texture = select_texture(session, ray);
	if (!texture || !texture->texture)
	{
		ft_error("Texture not properly loaded");
		return ;
	}
	init_tex_info(&tex_info, texture, ray);
	draw_wall_slice(session, x, ray, &tex_info);
}
