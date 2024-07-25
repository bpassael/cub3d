/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:46:18 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/24 08:34:11 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	draw_vertical_line(t_session *session, t_ray *ray, int x)
{
	draw_textured_wall(session, x, ray);
	draw_ceiling(session, x, ray->draw_start);
	draw_floor(session, x, ray->draw_end);
}
