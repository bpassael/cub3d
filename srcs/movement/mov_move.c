/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:31:02 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/22 13:31:03 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void	move_player_forward(t_map *map, t_player *player)
{
	double	new_x_pos;
	double	new_y_pos;

	new_x_pos = player->x_pos + player->dir_x * MOVE_STEP;
	new_y_pos = player->y_pos + player->dir_y * MOVE_STEP;
	if (is_move_valid(map, new_x_pos, new_y_pos))
	{
		player->x_pos = new_x_pos;
		player->y_pos = new_y_pos;
	}
}

void	move_player_backward(t_map *map, t_player *player)
{
	double	new_x_pos;
	double	new_y_pos;

	new_x_pos = player->x_pos - player->dir_x * MOVE_STEP;
	new_y_pos = player->y_pos - player->dir_y * MOVE_STEP;
	if (is_move_valid(map, new_x_pos, new_y_pos))
	{
		player->x_pos = new_x_pos;
		player->y_pos = new_y_pos;
	}
}

void	move_player_left(t_map *map, t_player *player)
{
	double	new_x_pos;
	double	new_y_pos;

	new_x_pos = player->x_pos + player->dir_y * MOVE_STEP;
	new_y_pos = player->y_pos - player->dir_x * MOVE_STEP;
	if (is_move_valid(map, new_x_pos, new_y_pos))
	{
		player->x_pos = new_x_pos;
		player->y_pos = new_y_pos;
	}
}

void	move_player_right(t_map *map, t_player *player)
{
	double	new_x_pos;
	double	new_y_pos;

	new_x_pos = player->x_pos - player->dir_y * MOVE_STEP;
	new_y_pos = player->y_pos + player->dir_x * MOVE_STEP;
	if (is_move_valid(map, new_x_pos, new_y_pos))
	{
		player->x_pos = new_x_pos;
		player->y_pos = new_y_pos;
	}
}

