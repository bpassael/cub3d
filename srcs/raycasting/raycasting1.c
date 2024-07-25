/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:17:27 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/22 16:50:46 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	raycast(t_map *map, t_session *session)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(map, &ray, x);
		perform_dda(map, &ray);
		calc_perp_wall_dist(map, &ray);
		calc_wall_specs(&ray, &ray.draw_start, &ray.draw_end, map->player);
		draw_vertical_line(session, &ray, x);
		x++;
	}
}

void	init_ray(t_map *map, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = map->player->dir_x + map->player->plane_x * ray->camera_x;
	ray->ray_dir_y = map->player->dir_y + map->player->plane_y * ray->camera_x;
	ray->map_x = (int)map->player->x_pos;
	ray->map_y = (int)map->player->y_pos;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
	init_ray_step(map, ray);
}

void	init_ray_step(t_map *map, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (map->player->x_pos - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - map->player->x_pos)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (map->player->y_pos - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - map->player->y_pos)
			* ray->delta_dist_y;
	}
}

void	perform_dda(t_map *map, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
	calc_perp_wall_dist(map, ray);
}
