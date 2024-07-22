/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:17:37 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/22 16:51:52 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calc_perp_wall_dist(t_map *map, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - map->player->x_pos + (1 - ray->step_x)
				/ 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - map->player->y_pos + (1 - ray->step_y)
				/ 2) / ray->ray_dir_y;
}

void	calc_wall_specs(t_ray *ray, int *draw_start, int *draw_end,
		t_player *player)
{
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	*draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (*draw_end >= HEIGHT)
		*draw_end = HEIGHT - 1;
	calc_wall_x(ray, player);
}

void	calc_wall_x(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->wall_x = player->y_pos + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = player->x_pos + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)TEXTURE_WIDTH);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = TEXTURE_WIDTH - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = TEXTURE_WIDTH - ray->tex_x - 1;
	determine_texture(ray);
}

void	determine_texture(t_ray *ray)
{
	if (ray->side == 0)
	{
        if (ray->ray_dir_x > 0)
            ray->tex_num = 2;
        else
            ray->tex_num = 3;
	}
	else
	{
        if (ray->ray_dir_y < 0)
            ray->tex_num = 0;
        else
            ray->tex_num = 1;
	}
}
