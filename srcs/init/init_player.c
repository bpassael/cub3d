/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:24:14 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/24 08:39:30 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_player_position(t_map *map, t_player *player_data)
{
	player_data->x_pos = map->player_x + 0.5;
	player_data->y_pos = map->player_y + 0.5;
	player_data->move_step = MOVE_STEP;
	player_data->rotat_step = ROTAT_STEP;
	player_data->map_x = (int)map->player_x;
	player_data->map_y = (int)map->player_y;
}

void	init_player_direction(t_map *map, t_player *player_data)
{
	player_data->dir_x = 0;
	player_data->dir_y = 0;
	if (map->player_dir == 'N')
	{
		player_data->angle_deg = 90;
		player_data->dir_y = -1;
	}
	else if (map->player_dir == 'S')
	{
		player_data->angle_deg = 270;
		player_data->dir_y = 1;
	}
	else if (map->player_dir == 'E')
	{
		player_data->angle_deg = 0;
		player_data->dir_x = 1;
	}
	else if (map->player_dir == 'W')
	{
		player_data->angle_deg = 180;
		player_data->dir_x = -1;
	}
	player_data->angle_rad = player_data->angle_deg * (PI / 180);
}

void	init_player_plane(t_player *player_data)
{
	player_data->plane_x = -player_data->dir_y * 0.66;
	player_data->plane_y = player_data->dir_x * 0.66;
}

void	init_player_in_map(t_map *map)
{
	t_player	*player_data;

	player_data = (t_player *)malloc(sizeof(t_player));
	if (player_data == NULL)
	{
		ft_error("Malloc failed");
		return ;
	}
	init_player_position(map, player_data);
	init_player_direction(map, player_data);
	init_player_plane(player_data);
	map->player = player_data;
}
