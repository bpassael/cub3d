/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:29:51 by bperez-a          #+#    #+#             */
/*   Updated: 2024/07/23 16:05:34 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_hook(void *param)
{
	t_session	*session;

	session = (t_session *)param;
	if (mlx_is_key_down(session->mlx, MLX_KEY_W))
	{
		move_player_forward(session->map, session->map->player);
		raycast(session->map, session);
	}
	if (mlx_is_key_down(session->mlx, MLX_KEY_S))
	{
		move_player_backward(session->map, session->map->player);
		raycast(session->map, session);
	}
	if (mlx_is_key_down(session->mlx, MLX_KEY_A))
	{
		move_player_left(session->map, session->map->player);
		raycast(session->map, session);
	}
	if (mlx_is_key_down(session->mlx, MLX_KEY_D))
	{
		move_player_right(session->map, session->map->player);
		raycast(session->map, session);
	}
	if (mlx_is_key_down(session->mlx, MLX_KEY_LEFT))
	{
		rotate_player_left(session->map->player);
		raycast(session->map, session);
	}
	if (mlx_is_key_down(session->mlx, MLX_KEY_RIGHT))
	{
		rotate_player_right(session->map->player);
		raycast(session->map, session);
	}
	if (mlx_is_key_down(session->mlx, MLX_KEY_ESCAPE))
	{
		free_session(session);
		exit(0);
	}
}
