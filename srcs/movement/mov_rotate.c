/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:30:18 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/22 13:30:29 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_player_right(t_player *player)
{
	double	old_x;
	double	old_y;

	old_x = player->dir_x;
	old_y = player->dir_y;
	player->dir_x = old_x * cos(ROTAT_STEP) - old_y * sin(ROTAT_STEP);
	player->dir_y = old_x * sin(ROTAT_STEP) + old_y * cos(ROTAT_STEP);
	old_x = player->plane_x;
	old_y = player->plane_y;
	player->plane_x = old_x * cos(ROTAT_STEP) - old_y * sin(ROTAT_STEP);
	player->plane_y = old_x * sin(ROTAT_STEP) + old_y * cos(ROTAT_STEP);
}

void	rotate_player_left(t_player *player)
{
	double	old_x;
	double	old_y;

	old_x = player->dir_x;
	old_y = player->dir_y;
	player->dir_x = old_x * cos(-ROTAT_STEP) - old_y * sin(-ROTAT_STEP);
	player->dir_y = old_x * sin(-ROTAT_STEP) + old_y * cos(-ROTAT_STEP);
	old_x = player->plane_x;
	old_y = player->plane_y;
	player->plane_x = old_x * cos(-ROTAT_STEP) - old_y * sin(-ROTAT_STEP);
	player->plane_y = old_x * sin(-ROTAT_STEP) + old_y * cos(-ROTAT_STEP);
}
